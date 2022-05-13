#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

struct Vector2 {
public:
	Vector2() {};
	Vector2(float x_, float y_) {
		x = x_;
		y = y_;
	}

	float Length() {
		return sqrt(x * x + y * y);
	}

	Vector2 operator+(Vector2 b) { return Vector2(x + b.x, y + b.y); }
	Vector2 operator-(Vector2 b) { return Vector2(x - b.x, y - b.y); }
	Vector2 operator-() { return Vector2(-x, -y); }
	Vector2 operator*(float d) { return Vector2(x * d, y * d); }
	Vector2 operator/(float d) { return Vector2(x / d, y / d); }

	friend std::ostream& operator<<(std::ostream& os, const Vector2& v) {
		return os << "Vector2(" << v.x << ", " << v.y << ")";
	}

	float x; float y;
};

struct Vector3
{
public:
	Vector3() {};
	Vector3(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	};

	float Length() {
		return sqrt(x * x + y * y + z * z);
	}

	float Angle(Vector3 pos) {
		typedef float (*Vector3_Angle_t)(Vector3 a, Vector3 b);
		return Function<Vector3_Angle_t>("UnityEngine.CoreModule", "UnityEngine", "Vector3", "Angle", 2)(*this, pos);
	}

	Vector2 DeltaAngle(Vector3 target) {
		float dx = target.x - x;
		float dy = target.z - z;

		float distance = sqrt(dx * dx + dy * dy);
		float dz = target.y - y;

		float yaw = 360 - (atan2(dy, dx) * 180 / M_PI) + 90;

		float pitch = 360 - atan2(dz, distance) * 180 / M_PI;

		if (pitch >= 360) {
			pitch -= 360;
		}

		if (yaw >= 360) {
			yaw -= 360;
		}

		return Vector2(pitch, yaw);
	}

	Vector3 Normalize() {
		float len = Length();

		return Vector3(x / len, y / len, z / len);
	}

	Vector3 operator+(Vector3 b) { return Vector3(x + b.x, y + b.y, z + b.z); }
	Vector3 operator-(Vector3 b) { return Vector3(x - b.x, y - b.y, z - b.z); }
	Vector3 operator-() { return Vector3(-x, -y, -z); }
	Vector3 operator*(float d) { return Vector3(x * d, y * d, z * d); }
	Vector3 operator/(float d) { return Vector3(x / d, y / d, z / d); }

	friend std::ostream& operator<<(std::ostream& os, const Vector3& v) {
		return os << "Vector3(" << v.x << ", " << v.y << ", " << v.z << ")";
	}

	float x, y, z;
};