#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "function.h"

GameScene::GameScene() {}

GameScene::~GameScene(){
	delete model_;
	delete player_;
	delete blockModel_;

	for (WorldTransform* worldTransformBlock : worldTransformBlocks_) {
		delete worldTransformBlock;
	}
	worldTransformBlocks_.clear();
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//テクスチャの読み込み
	textureHandle_ = TextureManager::Load("uvChecker.png");
	//3Dモデルの生成
	model_ = Model::Create();
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
	//自キャラの生成
	player_ = new Player();
	//自キャラの初期化
	player_->Initialize(model_, textureHandle_, &viewProjection_);

	//ブロックの3Dモデルデータ生成
	blockModel_ = Model::Create();
	blockTextureHandle_ = TextureManager::Load("cube/cube.jpg");
	//要素数
	const uint32_t kNumblockHorizontal = 20;
	//ブロック１個分の横幅
	const float kBlockWidth = 2.0f;
	//要素数を変更
	worldTransformBlocks_.resize(kNumblockHorizontal);
	//キューブの生成
	for (uint32_t i = 0; i < kNumblockHorizontal; ++i) {
		worldTransformBlocks_[i] = new WorldTransform();
		worldTransformBlocks_[i]->Initialize();
		worldTransformBlocks_[i]->translation_.x = kBlockWidth * i;
		worldTransformBlocks_[i]->translation_.y = 0.0f;
	}

}

void GameScene::Update() {
	//自キャラの更新
	player_->Update();
	//ブロックの更新
	for (WorldTransform* worldTransformBlock : worldTransformBlocks_) {
	
		worldTransformBlock->matWorld_ = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);
		//定数バッファーに転送
		worldTransformBlock->TransferMatrix();
	}
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
	//自キャラの描画
	player_->Draw();

	//ブロックの描画
	for (WorldTransform* worldTransformBlock : worldTransformBlocks_) {
		blockModel_->Draw(*worldTransformBlock, viewProjection_);
	}

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
