#pragma once
#include "Vector3.h"
#include <string>
#include <vector>

enum class MapChipType {
	kBlank, // 空白
	kBlock, // ブロック
};

struct MapChipData {
	std::vector<std::vector<MapChipType>> data;
};
struct IndexSet {
	uint32_t xIndex;
	uint32_t yIndex;
};

class MapChipField {
public:
	// 範囲矩形
	struct Rect {
		float left;
		float right;
		float bottom;
		float top;
	};
	void ResetMapChipData();

	void LoadMapChipCsv(const std::string& filePath);

	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);

	Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

	const int GetNumBlockHorizontal();
	const int GetNumBlockVertical();

	// マップチップ番号を計算
	IndexSet GetMapChipIndexSetByPosition(const Vector3& position);

	Rect GetRectByIndex(uint32_t xIndex, uint32_t yIndex);

private:
	// 1ブロックのサイズ
	static inline const float kBlockWidth = 2.0f;
	static inline const float kBlockHeight = 2.0f;
	// ブロックの個数
	static inline const int kNumBlockVertical = 20;
	static inline const int kNumBlockHorizontal = 100;

	MapChipData mapChipData_;
};