#pragma once
#include "ViewProjection.h"

class Player;
class CameraController {
public:

		struct Rect {
		float left = 0.0f;
		float right = 1.0f;
		float bottom = 0.0f;
		float top = 1.0f;
	};

	CameraController();
	~CameraController();

	void Initialize(ViewProjection* viewProjection);

	void Update();

	void SetTarget(Player* target);

	void Reset();

	const ViewProjection& GetViewProjection() { return *viewProjection_; };

	void SetMovableArea(Rect& area);

private:
	//ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;

	Player* target_ = nullptr;

	Vector3 targetOffset_ = {0, 0, -50.0f};

	//カメラ移動範囲
	Rect movableArea_ = {0, 100, 0, 100};

	//カメラの目標座標
	Vector3 goalCoordinate_ = {200, 100, 0};
	//座標補間割合
	static inline const float kInterpolationRate = 0.8f;

};