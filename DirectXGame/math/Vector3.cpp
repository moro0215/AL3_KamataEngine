#include "Vector3.h"

Vector3& Vector3::operator+=(const Vector3& rhs) {
	// TODO: return ステートメントをここに挿入します
	
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vector3& operator+(const Vector3& mValue1, const Vector3& mValue2) {
	// TODO: return ステートメントをここに挿入します
	return Vector3 (mValue1) += mValue2;
}


