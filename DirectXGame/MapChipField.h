#pragma once
#include <vector>
#include <string>
#include "Vector3.h"

enum class MapChipType {
	kBlank, // 空白
	kBlock, // ブロック
};

struct MapChipData {
	std::vector<std::vector<MapChipType>> data;
};

class MapChipField {
private:
	//1ブロックのサイズ
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;
	//ブロックの個数
	static inline const int kNumBlockVertical = 20;
	static inline const int kNumBlockHorizontal = 100;

	MapChipData mapChipData_;

public:
	void ResetMapChipData();

	void LoadMapChipCsv(const std::string& filePath);

	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);

	Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

	
};

