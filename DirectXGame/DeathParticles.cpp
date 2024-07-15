#include "DeathParticles.h"
#include <algorithm>
#include <cassert>
#include <numbers>
#define _USE_MATH_DEFINES
#include <math.h>
#include <function.h>

DeathParticles::DeathParticles() {}

DeathParticles::~DeathParticles() {}

void DeathParticles::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position, uint32_t textureHandle) {
	for (auto& worldTransform : worldTransforms_) {
		worldTransform.Initialize();
		worldTransform.translation_ = position;
	}
	
	// NULLポインタチェック
	assert(model);
	particleModel_ = model;
	viewProjection_ = viewProjection;
	ParticleTextureHandle_ = textureHandle;
}

void DeathParticles::Update() {
	for (auto& WorldTransform : worldTransforms_) {
		// スケール、回転、平行移動を合成して行列を計算する
		WorldTransform.matWorld_ = MakeAffineMatrix(WorldTransform.scale_, WorldTransform.rotation_, WorldTransform.translation_);
		// 定数バッファーに転送
		WorldTransform.TransferMatrix();
	}
}

void DeathParticles::Draw() {
	for (auto& WorldTransform : worldTransforms_) {
		particleModel_->Draw(WorldTransform, *viewProjection_, ParticleTextureHandle_);
	}
