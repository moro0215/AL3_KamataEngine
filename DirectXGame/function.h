#pragma once
#include <assert.h>
#define _USE_MATH_DEFINES
#include "math.h"
#include <cmath>

struct matrix4x4 {
	float m[4][4];
};
struct vector3 {
	float x;
	float y;
	float z;
};

// 行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 r;
	r = {
	    r.m[0][0] = m1.m[0][0] + m2.m[0][0], r.m[0][1] = m1.m[0][1] + m2.m[0][1], r.m[0][2] = m1.m[0][2] + m2.m[0][2], r.m[0][3] = m1.m[0][3] + m2.m[0][3],
	    r.m[1][0] = m1.m[1][0] + m2.m[1][0], r.m[1][1] = m1.m[1][1] + m2.m[1][1], r.m[1][2] = m1.m[1][2] + m2.m[1][2], r.m[1][3] = m1.m[1][3] + m2.m[1][3],
	    r.m[2][0] = m1.m[2][0] + m2.m[2][0], r.m[2][1] = m1.m[2][1] + m2.m[2][1], r.m[2][2] = m1.m[2][2] + m2.m[2][2], r.m[2][3] = m1.m[2][3] + m2.m[2][3],
	    r.m[3][0] = m1.m[3][0] + m2.m[3][0], r.m[3][1] = m1.m[3][1] + m2.m[3][1], r.m[3][2] = m1.m[3][2] + m2.m[3][2], r.m[3][3] = m1.m[3][3] + m2.m[3][3],
	};
	return r;
};
// 行列の減法
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 r;
	r = {
	    r.m[0][0] = m1.m[0][0] - m2.m[0][0], r.m[0][1] = m1.m[0][1] - m2.m[0][1], r.m[0][2] = m1.m[0][2] - m2.m[0][2], r.m[0][3] = m1.m[0][3] - m2.m[0][3],
	    r.m[1][0] = m1.m[1][0] - m2.m[1][0], r.m[1][1] = m1.m[1][1] - m2.m[1][1], r.m[1][2] = m1.m[1][2] - m2.m[1][2], r.m[1][3] = m1.m[1][3] - m2.m[1][3],
	    r.m[2][0] = m1.m[2][0] - m2.m[2][0], r.m[2][1] = m1.m[2][1] - m2.m[2][1], r.m[2][2] = m1.m[2][2] - m2.m[2][2], r.m[2][3] = m1.m[2][3] - m2.m[2][3],
	    r.m[3][0] = m1.m[3][0] - m2.m[3][0], r.m[3][1] = m1.m[3][1] - m2.m[3][1], r.m[3][2] = m1.m[3][2] - m2.m[3][2], r.m[3][3] = m1.m[3][3] - m2.m[3][3],
	};
	return r;
};
// 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 r;
	r = {
	    r.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0],
	    r.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1],
	    r.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2],
	    r.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3],
	    r.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0],
	    r.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1],
	    r.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2],
	    r.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3],
	    r.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0],
	    r.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1],
	    r.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2],
	    r.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3],
	    r.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0],
	    r.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1],
	    r.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2],
	    r.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3],
	};
	return r;
};
// 逆行列
Matrix4x4 Inverse(const Matrix4x4& m) {
	float inverse =
	    m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1] -
	    m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2] - m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1] -
	    m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2] + m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2] +
	    m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2] - m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1] -
	    m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0] -
	    m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0] + m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];

	Matrix4x4 r;
	r = {
	    r.m[0][0] = (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[1][2] * m.m[2][1] * m.m[3][3] -
	                 m.m[1][1] * m.m[2][3] * m.m[3][2]) /
	                inverse,
	    r.m[0][1] = (-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[2][1] * m.m[3][2] + m.m[0][3] * m.m[2][2] * m.m[3][1] +
	                 m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]) /
	                inverse,
	    r.m[0][2] = (m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[3][2] - m.m[0][3] * m.m[1][2] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[3][3] -
	                 m.m[0][1] * m.m[1][3] * m.m[3][2]) /
	                inverse,
	    r.m[0][3] = (-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] - m.m[0][3] * m.m[1][1] * m.m[2][2] + m.m[0][3] * m.m[1][2] * m.m[2][1] +
	                 m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]) /
	                inverse,
	    r.m[1][0] = (-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[1][3] * m.m[2][0] * m.m[3][2] + m.m[1][3] * m.m[2][2] * m.m[3][0] +
	                 m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]) /
	                inverse,
	    r.m[1][1] = (m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] + m.m[0][3] * m.m[2][0] * m.m[3][2] - m.m[0][3] * m.m[2][2] * m.m[3][0] - m.m[0][2] * m.m[2][0] * m.m[3][3] -
	                 m.m[0][0] * m.m[2][3] * m.m[3][2]) /
	                inverse,
	    r.m[1][2] = (-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] - m.m[0][3] * m.m[1][0] * m.m[3][2] + m.m[0][3] * m.m[1][2] * m.m[3][0] +
	                 m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]) /
	                inverse,
	    r.m[1][3] = (m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] + m.m[0][3] * m.m[1][0] * m.m[2][2] - m.m[0][3] * m.m[1][2] * m.m[2][0] - m.m[0][2] * m.m[1][0] * m.m[2][3] -
	                 m.m[0][0] * m.m[1][3] * m.m[2][2]) /
	                inverse,
	    r.m[2][0] = (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[1][3] * m.m[2][0] * m.m[3][1] - m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[1][1] * m.m[2][0] * m.m[3][3] -
	                 m.m[1][0] * m.m[2][3] * m.m[3][1]) /
	                inverse,
	    r.m[2][1] = (-m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] - m.m[0][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[2][1] * m.m[3][0] +
	                 m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]) /
	                inverse,
	    r.m[2][2] = (m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] + m.m[0][3] * m.m[1][0] * m.m[3][1] - m.m[0][3] * m.m[1][1] * m.m[3][0] - m.m[0][1] * m.m[1][0] * m.m[3][3] -
	                 m.m[0][0] * m.m[1][3] * m.m[3][1]) /
	                inverse,
	    r.m[2][3] = (-m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] - m.m[0][3] * m.m[1][0] * m.m[2][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] +
	                 m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]) /
	                inverse,
	    r.m[3][0] = (-m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] - m.m[1][2] * m.m[2][0] * m.m[3][1] + m.m[1][2] * m.m[2][1] * m.m[3][0] +
	                 m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]) /
	                inverse,
	    r.m[3][1] = (m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] + m.m[0][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[2][1] * m.m[3][0] - m.m[0][1] * m.m[2][0] * m.m[3][2] -
	                 m.m[0][0] * m.m[2][2] * m.m[3][1]) /
	                inverse,
	    r.m[3][2] = (-m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] - m.m[0][2] * m.m[1][0] * m.m[3][1] + m.m[0][2] * m.m[1][1] * m.m[3][0] +
	                 m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]) /
	                inverse,
	    r.m[3][3] = (m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] + m.m[0][2] * m.m[1][0] * m.m[2][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] - m.m[0][1] * m.m[1][0] * m.m[2][2] -
	                 m.m[0][0] * m.m[1][2] * m.m[2][1]) /
	                inverse,
	};
	return r;
};
// 転置行列
Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 r;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			r.m[i][j] = m.m[j][i];
		}
	}
	return r;
};
// 単位行列の作成
Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 r;
	r = {
	    1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	};
	return r;
};

// 加算
Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 v3;
	v3 = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
	return v3;
};
// 減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 v3;
	v3 = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
	return v3;
};
// スカラー倍
Vector3 Multiply(float scalar, const Vector3& v) {
	Vector3 v3;
	v3 = {scalar * v.x, scalar * v.y, scalar * v.z};
	return v3;
};
// 内積
float Dot(const Vector3& v1, const Vector3& v2) {
	float r;
	r = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return r;
};
// 長さ（ノルム）
float Length(const Vector3& v) {
	float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	return length;
};
// 正規化
Vector3 Normalize(const Vector3& v) {
	float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	Vector3 r;
	r = {v.x / length, v.y / length, v.z / length};
	return r;
};

// x軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 R = {
	    R.m[0][0] = 1,
	    R.m[0][1] = 0,
	    R.m[0][2] = 0,
	    R.m[0][3] = 0,
	    R.m[1][0] = 0,
	    R.m[1][1] = std::cos(radian),
	    R.m[1][2] = std::sin(radian),
	    R.m[1][3] = 0,
	    R.m[2][0] = 0,
	    R.m[2][1] = -std::sin(radian),
	    R.m[2][2] = std::cos(radian),
	    R.m[2][3] = 0,
	    R.m[3][0] = 0,
	    R.m[3][1] = 0,
	    R.m[3][2] = 0,
	    R.m[3][3] = 1,
	};
	return R;
};

// y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 R = {
	    R.m[0][0] = std::cos(radian), R.m[0][1] = 0, R.m[0][2] = -std::sin(radian), R.m[0][3] = 0, R.m[1][0] = 0, R.m[1][1] = 1, R.m[1][2] = 0, R.m[1][3] = 0,
	    R.m[2][0] = std::sin(radian), R.m[2][1] = 0, R.m[2][2] = std::cos(radian),  R.m[2][3] = 0, R.m[3][0] = 0, R.m[3][1] = 0, R.m[3][2] = 0, R.m[3][3] = 1,
	};
	return R;
};

// z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 R = {
	    R.m[0][0] = std::cos(radian),
	    R.m[0][1] = std::sin(radian),
	    R.m[0][2] = 0,
	    R.m[0][3] = 0,
	    R.m[1][0] = -std::sin(radian),
	    R.m[1][1] = std::cos(radian),
	    R.m[1][2] = 0,
	    R.m[1][3] = 0,
	    R.m[2][0] = 0,
	    R.m[2][1] = 0,
	    R.m[2][2] = 1,
	    R.m[2][3] = 0,
	    R.m[3][0] = 0,
	    R.m[3][1] = 0,
	    R.m[3][2] = 0,
	    R.m[3][3] = 1,
	};
	return R;
};

// xyz回転行列
Matrix4x4 MakeRotateXYZMatrix(const Vector3& rotate) {

	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);

	Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

	return rotateXYZMatrix;
};

// 平行移動行列
Matrix4x4 MakeTranslateMatrix(Vector3 translate) {
	Matrix4x4 T = {
	    T.m[0][0] = 1, T.m[0][1] = 0, T.m[0][2] = 0, T.m[0][3] = 0, T.m[1][0] = 0,           T.m[1][1] = 1,           T.m[1][2] = 0,           T.m[1][3] = 0,
	    T.m[2][0] = 0, T.m[2][1] = 0, T.m[2][2] = 1, T.m[2][3] = 0, T.m[3][0] = translate.x, T.m[3][1] = translate.y, T.m[3][2] = translate.z, T.m[3][3] = 1,
	};
	return T;
};

// 拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 S = {
	    S.m[0][0] = scale.x, S.m[0][1] = 0, S.m[0][2] = 0,       S.m[0][3] = 0, S.m[1][0] = 0, S.m[1][1] = scale.y, S.m[1][2] = 0, S.m[1][3] = 0,
	    S.m[2][0] = 0,       S.m[2][1] = 0, S.m[2][2] = scale.z, S.m[2][3] = 0, S.m[3][0] = 0, S.m[3][1] = 0,       S.m[3][2] = 0, S.m[3][3] = 1,
	};
	return S;
};

// 座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];

	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
};

// アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, Vector3 translate) {
	Matrix4x4 S = MakeScaleMatrix(scale);
	Matrix4x4 R = MakeRotateXYZMatrix(rotate);
	Matrix4x4 T = MakeTranslateMatrix(translate);

	Matrix4x4 SR = Multiply(S, R);
	Matrix4x4 result = Multiply(SR, T);
	return result;
};
