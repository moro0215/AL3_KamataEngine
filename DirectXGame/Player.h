#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

class Player {

public:
	//コンストラクタ
	Player();

	//デストラクタ
	~Player();

	//初期化処理
	void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position);

	//更新処理
	void Update();

	//描画処理
	void Draw();

private:
	//ワールド変換データ
	WorldTransform worldTransform_;

	//モデル
	Model* model_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	ViewProjection* viewProjection_ = nullptr;

	//速度
	myVector3 velocity_ = {};
	static inline const float kAcceleration = 0.01f;
	static inline const float kAttenuation = 0.05f;
	//速度制限
	static inline const float kLimitRunSpeed = 1.0f;

	//左右
	enum class LRDirection{
		kRight,
		kLeft,
	};
	LRDirection lrDirection_ = LRDirection::kRight;
	//旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;
	//旋回タイマー
	float turnTimer_ = 0.0f;
	//旋回時間（秒）
	static inline const float kTimeTurn = 1.0f;

	//接地状態フラグ
	bool onGround_ = true;
	//重力加速度
	static inline const float kGravityAcceleration = 0.02f;
	//最大落下速度
	static inline const float kLimitFallSpeed = 1.0f;
	//ジャンプ初速
	static inline const float kJumpAcceleration = 0.5f;

	static inline const float kAttenuationLanding = 0.5f;
};
