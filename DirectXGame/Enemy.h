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

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	// AABBを取得
	AABB GetAABB();


private:
	// ワールド変換データ
	WorldTransform worldTransform_;

	// モデル
	Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t enemyTextureHandle_ = 0u;

	ViewProjection* viewProjection_ = nullptr;

	//歩行のスピード
	static inline const float kWalkSpeed = 0.03f;

	//速度
	Vector3 velocity_ = {};

	//アニメーション
	//最初の角度
	static inline const float kWalkMotionAngleStart = -45.0f;
	//最後の角度
	static inline const float kWalkMotionAngleEnd = 90.0f;
	//アニメーションの時間
	static inline const float kWalkMotionTime = 5.0f;
	//経過時間
	float walkTimer = 0.0f;

	// キャラクターの当たり判定サイズ
	static inline const float kWidth = 2.0f;
	static inline const float kHeight = 2.0f;

	static inline const float kBlank = 1.0f;
};