#include "TitleScene.h"
#include <Input.h>
#include <algorithm>
#include <cassert>
#include <numbers>
#define _USE_MATH_DEFINES
#include <math.h>

void TitleScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();

	worldTransform_.Initialize();
	viewProjection_.Initialize();
	// 3Dモデルの生成
	titleModel_ = Model::CreateFromOBJ("title", true);
}

void TitleScene::Update() { 
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		finished_ = true;
	}
}

void TitleScene::Draw() {
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Model::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	titleModel_->Draw(worldTransform_, viewProjection_);

	// スプライト描画後処理
	Model::PostDraw();
}

