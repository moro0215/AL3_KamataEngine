#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"


class MapChipField;

class Player {

public:
	//マップとの当たり判定情報
	struct CollisionMapInfo {
		bool ceiling = false;//天井
		bool landing = false;//着地
		bool hitWall = false;//壁
		Vector3 move;//移動量
	};

	// 角
	enum class Corner {
		kRightBottom, // 右下
		kLeftBottom,  // 左下
		kRightTop,    // 右上
		kLeftTop,     // 右下

		kNumCorner // 要素数
	};

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

	const WorldTransform& GetWorldTransform();

	//速度入手
	const Vector3& GetVelocity() const { return velocity_; }

	void SetMapChipField(MapChipField* mapChipField);

	//マップ衝突判定
	void MapCollision(CollisionMapInfo& info);
	void MapCollisionTop(CollisionMapInfo& info);
	void MapCollisionBottom(CollisionMapInfo& info);
	void MapCollisionRight(CollisionMapInfo& info);
	void MapCollisionLeft(CollisionMapInfo& info);

	//角の座標計算
	Vector3 CornerPosition(const Vector3& center, Corner corner);

private:
	//ワールド変換データ
	WorldTransform worldTransform_;

	//モデル
	Model* model_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	ViewProjection* viewProjection_ = nullptr;

	//速度
	Vector3 velocity_ = {};
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

	// 着地時の速度減衰率
	static inline const float kAttenuationLanding = 0.5f;
	// 壁接触時の速度減衰率
	static inline const float kAttenuationWall = 0.5f;

	//マップチップによるフィールド
	MapChipField* mapChipField_ = nullptr;

	//キャラクターの当たり判定サイズ
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;

	static inline const float kBlank = 1.0f;

};
