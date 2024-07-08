#include "Enemy.h"
#include <algorithm>
#include <cassert>
#include <numbers>
#define _USE_MATH_DEFINES
#include <math.h>
#include "MapChipField.h"

Enemy::Enemy() {}

Enemy::~Enemy() {}

void Enemy::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position) {
	// NULLポインタチェック
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = (Vector3)position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> * 3.0f / 2.0f;
	enemyTextureHandle_ = textureHandle;
	viewProjection_ = viewProjection;

	//速度の設定
	velocity_ = {-kWalkSpeed, 0, 0};

	walkTimer = 0.0f;
}

void Enemy::Update() {
	//移動
	worldTransform_.translation_ += velocity_;
	//タイマーを加算
	walkTimer += 1.0f / 60.0f;
	//回転アニメーション
	float param = std::sin(walkTimer);
	float radian = kWalkMotionAngleStart + kWalkMotionAngleEnd * (param + 1.0f) / 2.0f;
	worldTransform_.rotation_.x = std::numbers::pi_v<float> / 180.0f * (radian);
	// 行列を定数バッファーに転送
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw() {
	// 3Dモデルの描画
	model_->Draw(worldTransform_, *viewProjection_, enemyTextureHandle_);
}
