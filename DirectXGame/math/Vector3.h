#pragma once

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {
	float x;
	float y;
	float z;
};

class myVector3 {
public:
	inline myVector3& operator+=(const myVector3& rhs) {
		mValue.x += rhs.mValue.x;
		mValue.y += rhs.mValue.y;
		mValue.z += rhs.mValue.z;
		return *this;
	}

	Vector3 mValue;
};