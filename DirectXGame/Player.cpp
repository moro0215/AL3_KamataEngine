#include "Player.h"
#include <cassert>

// コンストラクタ
Player::Player(){};

// デストラクタ
Player::~Player(){};

void Player::Initialize(Model* model, uint32_t textureHandle) {
	// NULLポインタチェック
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	textureHandle_ = textureHandle;
}

void Player::Update() {

}

void Player::Draw() {

}