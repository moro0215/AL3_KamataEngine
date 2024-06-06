#include "CameraController.h"
#include "Player.h"
#include "algorithm"

CameraController::CameraController() {}

CameraController::~CameraController() {}

void CameraController::Initialize(ViewProjection* viewProjection) { 

	viewProjection_ = viewProjection; 

}

void CameraController::Update() {
	//// 追跡対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	// 追跡対象とオフセットからカメラの座標を計算
	viewProjection_->translation_ = targetWorldTransform.translation_ + targetOffset_;
	
	//移動範囲制限
	float vx = viewProjection_->translation_.x;
	float vy = viewProjection_->translation_.y;
	viewProjection_->translation_.x = std::clamp(vx,movableArea_.left, movableArea_.right);
	viewProjection_->translation_.y = std::clamp(vy,movableArea_.bottom, movableArea_.top);

	//行列の更新
	viewProjection_->UpdateMatrix();
}

void CameraController::SetTarget(Player* target) { target_ = target; }

void CameraController::Reset() {
	////追跡対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	//追跡対象とオフセットからカメラの座標を計算
	viewProjection_->translation_ = targetWorldTransform.translation_ + targetOffset_;

}

void CameraController::SetMovableArea(Rect& area) { movableArea_ = area; };