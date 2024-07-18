#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include <array>

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

};