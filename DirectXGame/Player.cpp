#define NOMINMAX
#include "Player.h"
#include <Input.h>
#include <algorithm>
#include <cassert>
#include <numbers>
#define _USE_MATH_DEFINES
#include <math.h>

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
	worldTransform_.translation_ += velocity_;

	// 着地フラグ
	bool landing = false;
	// 地面と当たり判定
	if (velocity_.y < 0) {
		if (worldTransform_.translation_.y <= 1.0f) {
			landing = true;
		}
	}
	// 接地判定
	if (onGround_) {
		// ジャンプ開始
		if (velocity_.y > 0.0f) {
			onGround_ = false;
		}
	} else {
		// 着地
		if (landing) {
			// めりこみ排斥
			worldTransform_.translation_.y = 2.0f;
			velocity_.x *= (1.0f - kAttenuationLanding);
			velocity_.y = 0.0f;
			onGround_ = true;
		}
	}

	// 行列計算
	worldTransform_.UpdateMatrix();
}

void Player::Draw() {
	// 3Dモデルの描画
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);
}

const WorldTransform& Player::GetWorldTransform() { return worldTransform_; }
