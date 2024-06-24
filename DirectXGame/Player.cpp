#define NOMINMAX
#include "Player.h"
#include <Input.h>
#include <algorithm>
#include <cassert>
#include <numbers>
#define _USE_MATH_DEFINES
#include <math.h>
#include "MapChipField.h"

float easeOutSine(float x) { return sinf((x * (float)M_PI) / 2); }

// コンストラクタ
Player::Player(){};

// デストラクタ
Player::~Player(){};

void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position) {
	// NULLポインタチェック
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = (Vector3)position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> * 5.0f / 2.0f;
	textureHandle_ = textureHandle;
	viewProjection_ = viewProjection;
}

void Player::Update() {
	// 行列を定数バッファーに転送
	worldTransform_.UpdateMatrix();
	turnFirstRotationY_ = worldTransform_.rotation_.y;

	// 旋回制御
	if (turnTimer_ > 0.0f) {
		turnTimer_ -= (1.0f / 60.0f);
		// イージング
		float timeRotation = (1.0f-turnTimer_) / kTimeTurn;
		float easing = easeOutSine(timeRotation);

		// 左右の自キャラ角度テーブル
		float destinationRotationYTable[] = {std::numbers::pi_v<float> * 5.0f / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f};
		// 状況に応じた角度の取得
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
		// 自キャラの角度を設定
		worldTransform_.rotation_.y = turnFirstRotationY_ + (destinationRotationY-turnFirstRotationY_)*easing;
	}

	// 衝突情報を初期化
	CollisionMapInfo collisionMapInfo;
	// 移動量に速度の値をコピー
	collisionMapInfo.move = velocity_;
	// マップ衝突チェック
	MapCollision(collisionMapInfo);

	// 接地状態
	if (onGround_) {

		// 移動入力
		if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {
			// 左右加速
			Vector3 acceleration = {};
			if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
				// 左移動中の右入力
				if (velocity_.x < 0.0f) {
					// 速度と逆方向に入力中は急ブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x += kAcceleration;
				// 右向きに
				if (lrDirection_ != LRDirection::kRight) {
					lrDirection_ = LRDirection::kRight;
					// 旋回開始時の角度の記録
					turnFirstRotationY_ = std::numbers::pi_v<float> * 5.0f / 2.0f;
					// 旋回タイマーに時間を記録
					turnTimer_ = 1.0f;
				}
			} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
				// 右移動中の右入力
				if (velocity_.x > 0.0f) {
					// 速度と逆方向に入力中は急ブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x -= kAcceleration;
				// 左向きに
				if (lrDirection_ != LRDirection::kLeft) {
					lrDirection_ = LRDirection::kLeft;
					// 旋回開始時の角度の記録
					turnFirstRotationY_ = std::numbers::pi_v<float> * 3.0f / 2.0f;
					// 旋回タイマーに時間を記録
					turnTimer_ = 1.0f;
				}
			}

			// 加速減速
			velocity_ += acceleration;
			// 速度制限
			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);

		} else {
			// 移動減衰
			velocity_.x *= (1.0f - kAttenuation);
		}
		// ジャンプ
		if (Input::GetInstance()->PushKey(DIK_UP)) {
			Vector3 jumpAcceleration{0.0f, kJumpAcceleration, 0.0f};
			velocity_ += jumpAcceleration;
		}
	} else {
		// 落下速度
		Vector3 gravityAcceleration{0.0f, -kGravityAcceleration, 0};
		velocity_ += gravityAcceleration;
		// 落下速度制限
		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);
	}
	// 移動
	worldTransform_.translation_ += collisionMapInfo.move;

	// 着地フラグ
	//bool landing = false;
	// 地面と当たり判定
	if (collisionMapInfo.landing) {
		//着地状態に切り替える
		onGround_ = true;
		//着地時のx速度を減衰
		velocity_.x *= (1.0f - kAttenuationLanding);
		//y速度を0にする
		velocity_.y = 0.0f;
	}
	// 接地判定
	if (onGround_) {
		// ジャンプ開始
		if (velocity_.y > 0.0f) {
			onGround_ = false;
		}
	} else {
		//落下判定
		// 移後後の4つの角の座標
		std::array<Vector3, static_cast<uint32_t>(Corner::kNumCorner)> positionNew;
		for (uint32_t i = 0; i < positionNew.size(); ++i) {
			positionNew[i] = CornerPosition(worldTransform_.translation_ + collisionMapInfo.move, static_cast<Corner>(i));
		}
		MapChipType mapChipType;
		//真下の当たり判定
		bool hit = false;
		// 左下の当たり判定
		IndexSet indexSet;
		//Corner::kLeftBottom + Vector3(0, -1.0f, 0);
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[static_cast<uint32_t>(Corner::kLeftBottom)]);
		mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
		if (mapChipType == MapChipType::kBlock) {
			hit = true;
		}
		// 右下の当たり判定
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[static_cast<uint32_t>(Corner::kRightBottom)]);
		mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
		if (mapChipType == MapChipType::kBlock) {
			hit = true;
		}
		//落下開始
		if (!hit) {
			//空中状態に切り替わる
			onGround_ = false;
		}

		// 着地
		//if (landing) {
		//	// めりこみ排斥
		//	worldTransform_.translation_.y = 2.0f;
		//	velocity_.x *= (1.0f - kAttenuationLanding);
		//	velocity_.y = 0.0f;
		//	onGround_ = true;
		//}
	}
	// 行列計算
	worldTransform_.UpdateMatrix();
}

void Player::Draw() {
	// 3Dモデルの描画
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);
}

const WorldTransform& Player::GetWorldTransform() { return worldTransform_; }

void Player::SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

void Player::MapCollision(CollisionMapInfo& info) { 
	MapCollisionTop(info);
	MapCollisionBottom(info);
	/*MapCollisionRight(info);
	MapCollisionLeft(info);*/
}

void Player::MapCollisionTop(CollisionMapInfo& info) {
	if (info.move.y <= 0) {
		return;
	}
	//移後後の4つの角の座標
	std::array<Vector3, static_cast<uint32_t>(Corner::kNumCorner)> positionNew;
	for (uint32_t i = 0; i < positionNew.size(); ++i) {
		positionNew[i] = CornerPosition(worldTransform_.translation_ + info.move, static_cast<Corner>(i));
	}
	MapChipType mapChipType;
	// 真上の当たり判定
	bool hit = false;

	// 左上点の当たり判定
	IndexSet indexSet;
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[static_cast<uint32_t>(Corner::kLeftTop)]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}
	// 右上点の当たり判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[static_cast<uint32_t>(Corner::kRightTop)]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}
	float moveY=info.move.y;
	//ブロックにヒット
	if (hit) {
		//めり込みを排除する方向に移動量を設定
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_+info.move);
		//めり込み先ブロックの範囲矩形
		MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		info.move.y = std::max(0.0f, moveY);
		//天井に当たったことを記録する	
		info.ceiling = true;
	}

	//天井に当たった？
	if (info.ceiling) {
		velocity_.y = 0;
	}

}
void Player::MapCollisionBottom(CollisionMapInfo& info) {
	//下降あり？
	if (info.move.y >= 0) {
		return;
	}
	// 移後後の4つの角の座標
	std::array<Vector3, static_cast<uint32_t>(Corner::kNumCorner)> positionNew;
	for (uint32_t i = 0; i < positionNew.size(); ++i) {
		positionNew[i] = CornerPosition(worldTransform_.translation_ + info.move, static_cast<Corner>(i));
	}
	MapChipType mapChipType;

	//真下の当たり判定
	bool hit = false;

	//左下の当たり判定
	IndexSet indexSet;
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[static_cast<uint32_t>(Corner::kLeftBottom)]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}
	//右下の当たり判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[static_cast<uint32_t>(Corner::kRightBottom)]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}

	float moveY = info.move.y;
	// ブロックにヒット
	if (hit) {
		// めり込みを排除する方向に移動量を設定
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_ - info.move);
		// めり込み先ブロックの範囲矩形
		MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		info.move.y = std::min(0.0f, moveY);
		// 床に当たったことを記録する
		info.landing = true;
	}
}
//void Player::MapCollisionRight(CollisionMapInfo& info) {}
//void Player::MapCollisionLeft(CollisionMapInfo& info) {}

Vector3 Player::CornerPosition(const Vector3& center, Corner corner) {

	Vector3 offsetTable[static_cast<uint32_t>(Corner::kNumCorner)] = {
	    {+kWidth / 2.0f, -kHeight / 2.0f, 0},
	    {-kWidth / 2.0f, -kHeight / 2.0f, 0},
	    {+kWidth / 2.0f, +kHeight / 2.0f, 0},
	    {-kWidth / 2.0f, +kHeight / 2.0f, 0},
	};
	return center + offsetTable[static_cast<uint32_t>(corner)];
}
