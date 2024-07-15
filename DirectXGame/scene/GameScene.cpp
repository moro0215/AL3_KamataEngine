#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "function.h"

// AABBとAABBの当たり判定
bool ISCollisinAABBAABB(const AABB& aabb1, const AABB& aabb2) {
	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) && // x軸
	    (aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) && // y軸
	    (aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)) { // z軸
		return true;
	}
	return false;
}

void WorldTransform::UpdateMatrix() {
	// スケール、回転、平行移動を合成して行列を計算する
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);
	// 定数バッファーに転送
	TransferMatrix();
}

void GameScene::GenerateBlocks() {
	// 要素数
	uint32_t kNumBlockHorizontal = mapChipField_->GetNumBlockHorizontal();
	uint32_t kNumBlockVertical = mapChipField_->GetNumBlockVertical();
	
	//// ブロック１個分の横幅
	//const float kBlockWidth = mapChipField_->GetBlockWidth();
	//const float kBlockHeight = mapChipField_->GetBlockHeight();

	// 要素数を変更
	worldTransformBlocks_.resize(kNumBlockHorizontal);

	// 列数の設定(縦)
	worldTransformBlocks_.resize(kNumBlockVertical);
	for (uint32_t i = 0; i < kNumBlockVertical; ++i) {
		// 横のブロック数
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);
	}


	for (uint32_t i = 0; i < kNumBlockVertical; ++i) {
		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = (Vector3)mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}
}

void GameScene::CheckAllCollisions() {
	#pragma region
	//判定対象1と2の座標
	AABB aabb1, aabb2;
	//自キャラの座標
	aabb1 = player_->GetAABB();
	//自キャラと敵すべての当たり判定
	for (Enemy* enemy : enemies_) {
		//敵の座標
		aabb2 = enemy->GetAABB();
		//AABB同士の交差判定
		if (ISCollisinAABBAABB(aabb1, aabb2)) {
			//自キャラの衝突時コールバックを呼び出す
			player_->OnCollision(enemy);
			//敵の衝突時コールバックを呼び出す
			enemy->OnCollision(player_);
		}
	}
	#pragma endregion
}


GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete blockModel_;

	for (Enemy* newEnemy : enemies_) {
		delete newEnemy;
	}

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();

	delete debugCamera_;
	delete skydome_;
	delete modelSkydome_;
	delete mapChipField_;
	delete cameraController_;

	delete deathParticles_;
	delete particleModel_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	mapChipField_ = new MapChipField;
	mapChipField_->LoadMapChipCsv("Resources/blocks.csv");

	// テクスチャの読み込み
	textureHandle_ = TextureManager::Load("player.png");
	enemyTextureHandle_ = TextureManager::Load("enemy.png");
	ParticleTextureHandle_ = TextureManager::Load("white1x1.png");

	// 3Dモデルの生成
	model_ = Model::Create();
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// 座標をマップチップ番号で指定
	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(1, 18);
	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	player_->Initialize(model_, textureHandle_, &viewProjection_,playerPosition);

	player_->SetMapChipField(mapChipField_);

	// 座標をマップチップ番号で指定
	//Vector3 enemyPosition = mapChipField_->GetMapChipPositionByIndex(20, 18);
	// 敵キャラの生成
	//enemy_ = new Enemy();
	for (int32_t i = 0; i < 3; ++i) {
		Enemy* newEnemy = new Enemy();
		// 座標をマップチップ番号で指定
		Vector3 enemyPosition = mapChipField_->GetMapChipPositionByIndex(20, 18 - i);
		// 敵キャラの初期化
		newEnemy->Initialize(model_, enemyTextureHandle_, &viewProjection_, enemyPosition);

		enemies_.push_back(newEnemy);
	}
	// 敵キャラの初期化
	//enemy_->Initialize(model_, enemyTextureHandle_, &viewProjection_, enemyPosition);

	// ブロックの3Dモデルデータ生成
	blockModel_ = Model::Create();
	blockTextureHandle_ = TextureManager::Load("cube/cube.jpg");

	// ブロックの生成
	GenerateBlocks();

	// 天球の生成
	skydome_ = new Skydome();
	// 天球の3Dモデルの生成
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	// 天球の初期化
	skydome_->Initialize(modelSkydome_, &viewProjection_);

	//デバックカメラの生成
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);
	debugCamera_->SetFarZ(3000);

	
	//追従カメラ
	cameraController_ = new CameraController();
	cameraController_->Initialize(&viewProjection_);
	cameraController_->SetTarget(player_);
	cameraController_->Reset();

	CameraController::Rect movableArea_ = {25.0f, 180.0f, 0.0f, 100.0f};
	cameraController_->SetMovableArea(movableArea_);

	//デスパーティクル
	deathParticles_ = new DeathParticles;

	particleModel_ = Model::Create();

	deathParticles_->Initialize(particleModel_, &viewProjection_, playerPosition, ParticleTextureHandle_);
}

void GameScene::Update() {
	// 自キャラの更新
	player_->Update();

	/// 敵キャラの更新
	for (Enemy* newEnemy : enemies_) {
		newEnemy->Update();
	}
	// ブロックの更新
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock) {
				continue;
			}
			worldTransformBlock->matWorld_ = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);
			// 定数バッファーに転送
			worldTransformBlock->TransferMatrix();
		}
	}
	
	// 天球の更新
	skydome_->Update();

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_SPACE)) {
		if (isDebugCameraActive_) {
			isDebugCameraActive_ = false;
		} else {
			isDebugCameraActive_ = true;
		}
	}
#endif // _DEBUG
	//カメラの処理
	if (isDebugCameraActive_) {
		// デバックカメラの更新
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		//ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
	//ビュープロジェクション行列の更新と転送	
		viewProjection_.UpdateMatrix();
	}

	
	if (cameraController_) {
		// 追従カメラの更新
		cameraController_->Update();
		viewProjection_.matView = cameraController_->GetViewProjection().matView;
		viewProjection_.matProjection = cameraController_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		// ビュープロジェクション行列の更新と転送
		viewProjection_.UpdateMatrix();
	}

	//すべての当たり判定を行う
	CheckAllCollisions();

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// 

	// 自キャラの描画
	player_->Draw();

	// 敵キャラの描画
	for (Enemy* newEnemy : enemies_) {
		newEnemy->Draw();
	}
	// ブロックの描画
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock) {
				continue;
			}
			blockModel_->Draw(*worldTransformBlock, viewProjection_);
		}
	}

	// 天球の描画
	skydome_->Draw();
	
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

