#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

struct AABB {
	Vector3 min; // 最小点
	Vector3 max; // 最大点
};

// AABBとAABBの当たり判定
bool ISCollisinAABBAABB(const AABB& aabb1, const AABB& aabb2) {
	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) && // x軸
	    (aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) && // y軸
	    (aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)) { // z軸
		return true;
	}
	return false;
}
class Player;

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

	//衝突応答
	void OnCollision(const Player* player);


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