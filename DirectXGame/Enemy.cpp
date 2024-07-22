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
	enemyModel_ = model;
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
	enemyModel_->Draw(worldTransform_, *viewProjection_, enemyTextureHandle_);
}

Vector3 Enemy::GetWorldPosition() {
	// ワールド座標を取得
	Vector3 worldPos;
	// ワールド座標の平行移動成分を取得
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

AABB Enemy::GetAABB() {
	Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;
}

void Enemy::OnCollision(const Player* player) { 
	(void)player;
 }
