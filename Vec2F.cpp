#include "Vec2F.h"

void Vec2F::operator+=(const Vec2F& v) {
	x += v.x;
	y += v.y;
}

void Vec2F::operator-=(const Vec2F& v) {
	x -= v.x;
	y -= v.y;
}

Vec2F operator+(const Vec2F& a, const Vec2F& b) {
	return { a.x + b.x, a.y + b.y };
}

Vec2F operator-(const Vec2F& a, const Vec2F& b) {
	return { a.x - b.x, a.y - b.y };
}

Vec2F operator*(const Vec2F& a, float f) {
	return { a.x * f, a.y * f };
}

Vec2F operator-(const Vec2F& v)
{
	return Vec2F{ -v.x, -v.y };
}

float dot(const Vec2F& a, const Vec2F& b) {
	return a.x * b.x + a.y * b.y;
}

float normSqr(const Vec2F& a) {
	return dot(a, a);
}