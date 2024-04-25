#include "Player.h"
#include <cassert>

// コンストラクタ
Player::Player(){};

// デストラクタ
Player::~Player(){};

void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection) {
	// NULLポインタチェック
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	textureHandle_ = textureHandle;
	viewProjection_ = viewProjection;
}

void Player::Update() {
	//行列を定数バッファーに転送
	worldTransform_.TransferMatrix();

}

void Player::Draw() {
	//3Dモデルの描画
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);

}