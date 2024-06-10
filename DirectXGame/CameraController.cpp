#include "CameraController.h"
#include "Player.h"
#include "algorithm"

CameraController::CameraController() {}

CameraController::~CameraController() {}

Vector3 Lerp(const Vector3& a, const Vector3& b, float t) {

	Vector3 p = {0, 0, 0};

	float x = t * a.x + (1.0f - t) * b.x;
	float y = t * a.y + (1.0f - t) * b.y;
	float z = t * a.z + (1.0f - t) * b.z;

	p = {x, y, z};

	return p;
}

void CameraController::Initialize(ViewProjection* viewProjection) { 

	viewProjection_ = viewProjection; 

}

void CameraController::Update() {
	Vector3 targetVolocity = target_->GetVelocity();
	//// 追跡対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	// 追跡対象とオフセットと追従対象の速度からカメラの目標座標を計算
	goalCoordinate_ = targetWorldTransform.translation_ + targetOffset_ + targetVolocity * kVelocityBias;
	
	//座標補間によりゆったり追従
	viewProjection_->translation_ = Lerp(viewProjection_->translation_, goalCoordinate_, kInterpolationRate);

	float vx = viewProjection_->translation_.x;
	float vy = viewProjection_->translation_.y;
	
	// 移動範囲制限
	viewProjection_->translation_.x = std::clamp(vx, movableArea_.left, movableArea_.right);
	viewProjection_->translation_.y = std::clamp(vy, movableArea_.bottom, movableArea_.top);

	// 追従対象が画面外に出ないように補正
	viewProjection_->translation_.x = std::clamp(vx,margin_.left, margin_.right);
	viewProjection_->translation_.y = std::clamp(vy, margin_.bottom, margin_.top);
	
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
