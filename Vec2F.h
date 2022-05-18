#pragma once

struct Vec2F {
	float x;
	float y;

	void operator+=(const Vec2F& v);
	void operator-=(const Vec2F& v);
};

Vec2F operator+(const Vec2F& a, const Vec2F& b); 

Vec2F operator-(const Vec2F& a, const Vec2F& b);

Vec2F operator*(const Vec2F& a, float f);

Vec2F operator-(const Vec2F& v);

float dot(const Vec2F& a, const Vec2F& b);

float normSqr(const Vec2F& a);