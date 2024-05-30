#include "CameraController.h"
#include "Player.h"

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
