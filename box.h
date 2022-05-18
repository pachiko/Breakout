#pragma once

#include <tuple>
#include <algorithm>
#include "Vec2F.h"

enum DIRECTION {
	UP, RIGHT, DOWN, LEFT
};

class Box {
	public:
		Vec2F p0; // bottom left
		Vec2F p1; // top right

		Box();

		Box(const Vec2F& p0, const Vec2F& p1);

		Box(float x, float y, float w, float h);

		float w() const;

		float h() const;

		float getCenterX() const;

		void setCenterX(float cx);

		float getCenterY() const;

		void setCenterY(float cy);

		Vec2F getCenter() const;

		void setCenter(Vec2F& c);

		void move(const Vec2F& v);

		void draw(uint32_t col);

		void drawWire(uint32_t col);

		void grow(float r);

		bool contains(const Vec2F& v) const;

		bool surrounds(const Box& other) const;

		void include(const Box& other);

		bool intersects(const Box& b);

		std::tuple<bool, DIRECTION, Vec2F> intersect(const Box& b);
};