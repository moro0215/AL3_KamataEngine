#include "Player.h"
#include <cassert>
#include <numbers>
#include <Input.h>
#include <algorithm>

// コンストラクタ
Player::Player(){};

// デストラクタ
Player::~Player(){};

void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection,const Vector3& position) {
	// NULLポインタチェック
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = (myVector3)position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
	textureHandle_ = textureHandle;
	viewProjection_ = viewProjection;
}

void Player::Update() {
	//行列を定数バッファーに転送
	worldTransform_.UpdateMatrix();

	//左右の自キャラ角度テーブル
	float destinationRotationYTable[] = {std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f};
	//状況に応じた角度の取得
	float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
	//自キャラの角度を設定
	worldTransform_.rotation_.y = destinationRotationY;

	//移動入力
	if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {
		//左右加速
		myVector3 acceleration = {};
		if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
			//左移動中の右入力
			if (velocity_.mValue.x < 0.0f) {
				//速度と逆方向に入力中は急ブレーキ
				velocity_.mValue.x *= (1.0f - kAttenuation);
			}
			acceleration.mValue.x += kAcceleration;
			// 右向きに
			if (lrDirection_ != LRDirection::kRight) {
				lrDirection_ = LRDirection::kRight;
			}
		} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
			// 右移動中の右入力
			if (velocity_.mValue.x > 0.0f) {
				// 速度と逆方向に入力中は急ブレーキ
				velocity_.mValue.x *= (1.0f - kAttenuation);
			}
			acceleration.mValue.x -= kAcceleration;
			//左向きに
			if (lrDirection_ != LRDirection::kLeft) {
				lrDirection_ = LRDirection::kLeft;
			}
		}
		//加速減速
		velocity_ += acceleration;
		//速度制限
		velocity_.mValue.x = std::clamp(velocity_.mValue.x, -kLimitRunSpeed, kLimitRunSpeed);

	} else {
		//移動減衰
		velocity_.mValue.x *= (1.0f - kAttenuation);
	}
	//移動
	worldTransform_.translation_ += velocity_;
	//行列計算
	worldTransform_.UpdateMatrix();
}

void Player::Draw() {
	//3Dモデルの描画
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);

}