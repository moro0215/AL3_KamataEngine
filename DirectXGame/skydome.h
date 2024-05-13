#pragma once
#include <Model.h>
#include <WorldTransform.h>

class Skydome {
public:
	// コンストラクタ
	Skydome();

	// デストラクタ
	~Skydome();

	// 初期化処理
	void Initialize();

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

private:
	//ワールド変換データ
	WorldTransform warldTransform_;
	//モデル
	Model* model_ = nullptr;

};