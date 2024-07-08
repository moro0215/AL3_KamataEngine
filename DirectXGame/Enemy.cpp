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
}

void Enemy::Update() {
	// 行列を定数バッファーに転送
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw() {
	// 3Dモデルの描画
	model_->Draw(worldTransform_, *viewProjection_, enemyTextureHandle_);
}

//void Enemy::SetMapChipField(MapChipField* mapChipField) {}

