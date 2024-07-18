#include "DeathParticles.h"
#include <algorithm>
#include <cassert>
#include <numbers>
#define _USE_MATH_DEFINES
#include <math.h>

// z軸回転行列
Matrix4x4 RotateZMatrix(float radian) {
	Matrix4x4 R = {
	    R.m[0][0] = std::cos(radian),
	    R.m[0][1] = std::sin(radian),
	    R.m[0][2] = 0,
	    R.m[0][3] = 0,
	    R.m[1][0] = -std::sin(radian),
	    R.m[1][1] = std::cos(radian),
	    R.m[1][2] = 0,
	    R.m[1][3] = 0,
	    R.m[2][0] = 0,
	    R.m[2][1] = 0,
	    R.m[2][2] = 1,
	    R.m[2][3] = 0,
	    R.m[3][0] = 0,
	    R.m[3][1] = 0,
	    R.m[3][2] = 0,
	    R.m[3][3] = 1,
	};
	return R;
};

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
	for (auto& worldTransform : worldTransforms_) {
		for (float i = 0; i < kNumParticles; i++) {
			float angle = 45 * i;
			// スケール、回転、平行移動を合成して行列を計算する
			worldTransform.matWorld_= RotateZMatrix(angle);
			
		}
		// 定数バッファーに転送
		worldTransform.UpdateMatrix();
	}
}

void DeathParticles::Draw() {
	for (auto& worldTransform : worldTransforms_) {
		particleModel_->Draw(worldTransform, *viewProjection_, ParticleTextureHandle_);
	}
}