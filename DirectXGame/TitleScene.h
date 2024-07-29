#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "DirectXCommon.h"

class TitleScene {
public:
	void Initialize();
	
	void Update();
	
	void Draw();

	//デスフラグのgetter
	bool IsFinished() const { return finished_; }

	private:
	//終了フラグ
	bool finished_ = false;

	DirectXCommon* dxCommon_ = nullptr;

	// ワールド変換データ
	WorldTransform worldTransform_;

	// モデル
	Model* titleModel_ = nullptr;

	ViewProjection viewProjection_;


};
