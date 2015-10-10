#include "mercury-math.h"
#pragma once

mat4 Mul(mat4 a, mat4 b) {
	mat4 result;
	result.e[0] = a.e[0] * b.e[0] + a.e[4] * b.e[1] + a.e[8]  * b.e[2] + a.e[12] * b.e[3];
	result.e[1] = a.e[1] * b.e[0] + a.e[5] * b.e[1] + a.e[9]  * b.e[2] + a.e[13] * b.e[3];
	result.e[2] = a.e[2] * b.e[0] + a.e[6] * b.e[1] + a.e[10] * b.e[2] + a.e[14] * b.e[3];
	result.e[3] = a.e[3] * b.e[0] + a.e[7] * b.e[1] + a.e[11] * b.e[2] + a.e[15] * b.e[3];

	result.e[4] = a.e[0] * b.e[4] + a.e[4] * b.e[5] + a.e[8]  * b.e[6] + a.e[12] * b.e[7];
	result.e[5] = a.e[1] * b.e[4] + a.e[5] * b.e[5] + a.e[9]  * b.e[6] + a.e[13] * b.e[7];
	result.e[6] = a.e[2] * b.e[4] + a.e[6] * b.e[5] + a.e[10] * b.e[6] + a.e[14] * b.e[7];
	result.e[7] = a.e[3] * b.e[4] + a.e[7] * b.e[5] + a.e[11] * b.e[6] + a.e[15] * b.e[7];

	result.e[8]  = a.e[0] * b.e[8] + a.e[4] * b.e[9] + a.e[8]  * b.e[10] + a.e[12] * b.e[11];
	result.e[9]  = a.e[1] * b.e[8] + a.e[5] * b.e[9] + a.e[9]  * b.e[10] + a.e[13] * b.e[11];
	result.e[10] = a.e[2] * b.e[8] + a.e[6] * b.e[9] + a.e[10] * b.e[10] + a.e[14] * b.e[11];
	result.e[11] = a.e[3] * b.e[8] + a.e[7] * b.e[9] + a.e[11] * b.e[10] + a.e[15] * b.e[11];

	result.e[12] = a.e[0] * b.e[12] + a.e[4] * b.e[13] + a.e[8]  * b.e[14] + a.e[12] * b.e[15];
	result.e[13] = a.e[1] * b.e[12] + a.e[5] * b.e[13] + a.e[9]  * b.e[14] + a.e[13] * b.e[15];
	result.e[14] = a.e[2] * b.e[12] + a.e[6] * b.e[13] + a.e[10] * b.e[14] + a.e[14] * b.e[15];
	result.e[15] = a.e[3] * b.e[12] + a.e[7] * b.e[13] + a.e[11] * b.e[14] + a.e[15] * b.e[15];

	return result;
}

float4 Mul(mat4 a, float4 b) {
	float4 result;
	
	result.x = a.e[0] * b.x + a.e[4] * b.y + a.e[8]  * b.z + a.e[12] * b.w;
	result.y = a.e[1] * b.x + a.e[5] * b.y + a.e[9]  * b.z + a.e[13] * b.w;
	result.z = a.e[2] * b.x + a.e[6] * b.y + a.e[10] * b.z + a.e[14] * b.w;
	result.w = a.e[3] * b.x + a.e[7] * b.y + a.e[11] * b.z + a.e[15] * b.w;

	return result;
}

float3 Cross(float3 x, float3 y) {
	return float3 {
			x.y * y.z - y.y * x.z,
			x.z * y.x - y.z * x.x,
			x.x * y.y - y.x * x.y };
}

float3 QMul(float4 a, float3 v) {
	float3 uv = Cross(a.xyz, v);
	float3 uuv = Cross(a.xyz, uv);
	return v + ((uv * a.w) + uuv) * 2.0f;
}

const float3 kXAxis { 1.0f, 0.0f, 0.0f };
const float3 kYAxis { 0.0f, 1.0f, 0.0f };
const float3 kZAxis { 0.0f, 0.0f, 1.0f };
const float3 kNegXAxis { -1.0f, 0.0f, 0.0f };
const float3 kNegYAxis { 0.0f, -1.0f, 0.0f };
const float3 kNegZAxis { 0.0f, 0.0f, -1.0f };
const float2 kZero2f { 0.0f, 0.0f };
const float3 kZero3f { 0.0f, 0.0f, 0.0f };
const float4 kZero4f { 0.0f, 0.0f, 0.0f, 0.0f };
const float kDeg2Rad = 0.01745329251994329576923690768489f;
const float kRad2Deg = 57.295779513082320876798154814105f;
const float kPi = 3.14159265358979323846264338327950288f;

mat4 Perspective(float fovy, float aspect, float zNear, float zFar) {
	mat4 result;
	
	float tanHalfFovy = (float) tan(fovy / 2.0f);
	result.v[0] = { 1.0f / (aspect * tanHalfFovy), 0.0f, 0.0f, 0.0f };
	result.v[1] = { 0.0f, 1.0f / (tanHalfFovy), 0.0f, 0.0f };
	result.v[2] = { 0.0f, 0.0f, -(zFar + zNear) / (zFar - zNear), -1.0f };
	result.v[3] = { 0.0f, 0.0f, -(2.0f * zFar * zNear) / (zFar - zNear), 0.0f };

	return result;
}

mat4 Translation(const float3 &translation) {
	mat4 result;

	result.v[0] = { 1.0f, 0.0f, 0.0f, 0.0f };
	result.v[1] = { 0.0f, 1.0f, 0.0f, 0.0f };
	result.v[2] = { 0.0f, 0.0f, 1.0f, 0.0f };
	result.v[3] = { translation, 1.0f };

	return result;
}

float3 Forward(float3 position, float4 rotation) {
	return QMul(rotation, kNegZAxis);
}

float3 Right(float3 position, float4 rotation) {
	return QMul(rotation, kXAxis);
}

float3 Up(float3 position, float4 rotation) {
	return QMul(rotation, kYAxis);
}

float4 Euler(float3 eulerAngle) {
	float3 c = Cos(eulerAngle * 0.5f);
	float3 s = Sin(eulerAngle * 0.5f);
	return float4 {
		s.x * c.y * c.z - c.x * s.y * s.z, // x
		c.x * s.y * c.z + s.x * c.y * s.z, // y
		c.x * c.y * s.z - s.x * s.y * c.z, // z
		c.x * c.y * c.z + s.x * s.y * s.z, // w
	};
}

float3 Normalize(float3 v) {
	float3 v2 = v * v;
	float invLength = 1.0f / sqrt(v2.x + v2.y + v2.z);
	return float3 {
		v.x * invLength,
		v.y * invLength,
		v.z * invLength
	};
}

float3 Cos(float3 v) {
	return float3 {
		cos(v.x),
		cos(v.y),
		cos(v.z),
	};
}

float3 Sin(float3 v) {
	return float3 {
		sin(v.x),
		sin(v.y),
		sin(v.z),
	};
}

mat4 Transpose(mat4 m) {
	mat4 result;
	result.e[0] = m.e[0];
	result.e[1] = m.e[4];
	result.e[2] = m.e[8];
	result.e[3] = m.e[12];
	result.e[4] = m.e[1];
	result.e[5] = m.e[5];
	result.e[6] = m.e[9];
	result.e[7] = m.e[13];
	result.e[8] = m.e[2];
	result.e[9] = m.e[6];
	result.e[10] = m.e[10];
	result.e[11] = m.e[14];
	result.e[12] = m.e[3];
	result.e[13] = m.e[7];
	result.e[14] = m.e[11];
	result.e[15] = m.e[15];
	return result;
}

mat4 MatrixFromQuat(float4 q) {
	mat4 result;
	float qxx(q.x * q.x);
	float qyy(q.y * q.y);
	float qzz(q.z * q.z);
	float qxz(q.x * q.z);
	float qxy(q.x * q.y);
	float qyz(q.y * q.z);
	float qwx(q.w * q.x);
	float qwy(q.w * q.y);
	float qwz(q.w * q.z);

	result.e[0] = 1 - 2 * (qyy +  qzz);
	result.e[1] = 2 * (qxy + qwz);
	result.e[2] = 2 * (qxz - qwy);
	result.e[3] = 0.0f;

	result.e[4] = 2 * (qxy - qwz);
	result.e[5] = 1 - 2 * (qxx +  qzz);
	result.e[6] = 2 * (qyz + qwx);
	result.e[7] = 0.0f;

	result.e[8] = 2 * (qxz + qwy);
	result.e[9] = 2 * (qyz - qwx);
	result.e[10] = 1 - 2 * (qxx +  qyy);
	result.e[11] = 0.0f;

	result.e[12] = 0.0f;
	result.e[13] = 0.0f;
	result.e[14] = 0.0f;
	result.e[15] = 1.0f;

	return result;
}
