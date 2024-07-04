#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

class Enemy {
public:
	Enemy();
	~Enemy();

	void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	void Draw();

	void SetMapChipField(MapChipField* mapChipField);

private:
	// ワールド変換データ
	WorldTransform worldTransform_;

	// モデル
	Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	ViewProjection* viewProjection_ = nullptr;

};