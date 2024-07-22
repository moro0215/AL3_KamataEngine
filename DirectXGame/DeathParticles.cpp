#include "DeathParticles.h"
#include <algorithm>
#include <cassert>
#include <numbers>
#define _USE_MATH_DEFINES
#include <math.h>

// 座標変換
Vector3 transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];

	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
};

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
	objectColor_.Initialize();
	color_ = {1, 1, 1, 1};
}

void DeathParticles::Update() {
	//終了なら何もしない
	if(isFinished_) {
		return;
	}

	for (uint32_t i = 0; i < kNumParticles; ++i) {
		//基本となる速度ベクトル
		Vector3 velocity = {kSpeed, 0, 0};
		//回転角を計算
		float angle = kAngleUnit * i;
		//Z軸まわり回転行列
		Matrix4x4 matrixRotation = RotateZMatrix(angle);
		//基本ベクトルを回転させて速度ベクトルを得る
		velocity = transform(velocity, matrixRotation);
		//移動処理
		worldTransforms_[i].translation_ += velocity;
	}
	//カウンターを1フレーム分の秒数進める
	counter_ += 1.0f / 60.0f;
	transparency -= 1.0f / 120.0f;

	//存続時間の上限に達したら
	if (counter_ >= kDuration) {
		counter_ = kDuration;
		transparency = 1.0f;
		isFinished_ = true;
	}

	for (auto& worldTransform : worldTransforms_) {
		for (float i = 0; i < kNumParticles; i++) {
			float angle = 45 * i;
			// スケール、回転、平行移動を合成して行列を計算する
			worldTransform.matWorld_ = RotateZMatrix(angle);
			
		}
		// 定数バッファーに転送
		worldTransform.UpdateMatrix();
	}
	

	color_.w = std::clamp(transparency, 0.0f, 1.0f);
	//色変更オブジェクトに色の数値を設定
	objectColor_.SetColor(color_);
	//色変更オブジェクトをVRAMの転送
	objectColor_.TransferMatrix();
}

void DeathParticles::Draw() {
	// 終了なら何もしない
	if (isFinished_) {
		return;
	}

	for (auto& worldTransform : worldTransforms_) {
		particleModel_->Draw(worldTransform, *viewProjection_, &objectColor_);
	}
}