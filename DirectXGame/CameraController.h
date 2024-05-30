#pragma once
#include "ViewProjection.h"

class Player;
class CameraController {
public:

	CameraController();
	~CameraController();

	void Initialize(ViewProjection* viewProjection);

	void Update();

	void SetTarget(Player* target);

	void Reset();

private:
	//ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;

	Player* target_ = nullptr;

	myVector3 targetOffset_ = {0, 0, -15.0f};
};