#include "MyType.h"

VECTOR2::VECTOR2() {
	x = 0.0f;
	y = 0.0f;
}

VECTOR2::VECTOR2(float a, float b) {
	x = a;
	y = b;
}

VECTOR2 VECTOR2::operator+(VECTOR2 vec) {
	VECTOR2 vec2;
	vec2.x = this->x + vec.x;
	vec2.y = this->y + vec.y;

	return vec2;
}

VECTOR2 VECTOR2::operator+(I_VECTOR2 vec) {
	VECTOR2 vec2;
	vec2.x = this->x + (float)vec.u;
	vec2.y = this->y + (float)vec.v;

	return vec2;
}

VECTOR2 VECTOR2::operator-(VECTOR2 vec) {
	VECTOR2 vec2;
	vec2.x = this->x - vec.x;
	vec2.y = this->y - vec.y;

	return vec2;
}

VECTOR2 VECTOR2::operator*(float value) {
	VECTOR2 VEC;
	VEC.x = this->x * value;
	VEC.y = this->y * value;
	return VEC;
}

I_VECTOR2::I_VECTOR2() {
	u = 0;
	v = 0;
}
I_VECTOR2::I_VECTOR2(int a, int b) {
	u = a;
	v = b;
}
I_VECTOR2 I_VECTOR2::operator+(I_VECTOR2 vec) {
	I_VECTOR2 vec2;
	vec2.u = this->u + vec.u;
	vec2.v = this->v + vec.v;

	return vec2;
}

I_VECTOR2 I_VECTOR2::operator-(I_VECTOR2 vec) {
	I_VECTOR2 vec2;
	vec2.u = this->u - vec.u;
	vec2.v = this->v - vec.v;

	return vec2;
}
