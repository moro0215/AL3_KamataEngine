#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include <array>
#include <numbers>



class DeathParticles {
public:
	DeathParticles();
	~DeathParticles();

	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position, uint32_t textureHandle);

	void Update();

	void Draw();

private:
	// モデル
	Model* particleModel_ = nullptr;

	ViewProjection* viewProjection_ = nullptr;

	// テクスチャハンドル
	uint32_t ParticleTextureHandle_ = 0u;

	//パーティクルの個数
	static inline const uint32_t kNumParticles = 8;
	std::array<WorldTransform, kNumParticles> worldTransforms_;

	//存続時間
	static inline const float kDuration = 2.0f;
	//移動の速さ
	static inline const float kSpeed = 0.1f;
	//分割した1個分の角度
	static inline const float kAngleUnit = 2*std::numbers::pi_v<float> / kNumParticles;
	//終了フラグ
	bool isFinished_ = false;
	//経過時間カウント
	float counter_ = 0.0f;
	//透明度の変数
	float transparency = 1.0f;

	//色変更オブジェクト
	ObjectColor objectColor_;
	//色の数値
	Vector4 color_;
};