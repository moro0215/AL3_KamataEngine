#include "Player.h"
#include <cassert>
#include <numbers>
#include <Input.h>

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

	//移動入力
	if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {
		//左右加速
		myVector3 acceleration = {};
		if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
			acceleration.mValue.x += kAcceleration;
		} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
			acceleration.mValue.x -= kAcceleration;
		}
		//加速減速
		velocity_ += acceleration;
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