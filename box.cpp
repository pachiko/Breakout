#include "box.h"
#include "Engine.h"

Box::Box() {
	p0 = { FLT_MAX, FLT_MAX };
	p1 = { -FLT_MAX, -FLT_MAX };
}

Box::Box(const Vec2F& p0, const Vec2F& p1) {
	this->p0 = p0;
	this->p1 = p1;
}

Box::Box(float x, float y, float w, float h) {
	p0 = { x, y };
	p1 = { x + w - 1, y + h - 1 };
}

float Box::w() const { return p1.x - p0.x; }

float Box::h() const { return p1.y - p0.y; }

float Box::getCenterX() const {
	return p0.x + w() / 2;
}

void Box::setCenterX(float cx) {
	float ww = w();
	p0.x = cx - ww / 2;
	p1.x = cx + ww / 2;
}

float Box::getCenterY() const {
	return p0.y + h() / 2;
}

void Box::setCenterY(float cy) {
	float hh = h();
	p0.y = cy - hh / 2;
	p1.y = cy + hh / 2;
}

Vec2F Box::getCenter() const {
	return { getCenterX(), getCenterY() };
}

void Box::setCenter(Vec2F& c) {
	setCenterX(c.x);
	setCenterY(c.y);
}

void Box::move(const Vec2F& v) {
	p0 += v;
	p1 += v;
}

void Box::draw(uint32_t col) {
	for (int i = p0.y; i <= p1.y; i++) {
		for (int j = p0.x; j <= p1.x; j++) {
			buffer[i][j] = col;
		}
	}
}

void Box::drawWire(uint32_t col) {
	for (int j = p0.x; j <= p1.x; j++) {
		buffer[static_cast<int>(p0.y)][j] = col;
		buffer[static_cast<int>(p1.y)][j] = col;
	}
	for (int i = p0.y; i <= p1.y; i++) {
		buffer[i][static_cast<int>(p0.x)] = col;
		buffer[i][static_cast<int>(p1.x)] = col;
	}
}

void Box::grow(float r) {
	p0 -= {r, r};
	p1 += {r, r};
}

bool Box::contains(const Vec2F& v) const {
	return v.x <= p1.x && v.x >= p0.x && v.y <= p1.y && v.y >= p0.y;
}

bool Box::surrounds(const Box& other) const {
	return contains(other.p0) && contains(other.p1);
}

void Box::include(const Box& other) {
	if (p0.x > other.p0.x) p0.x = other.p0.x;
	if (p0.y > other.p0.y) p0.y = other.p0.y;
	if (p1.x < other.p1.x) p1.x = other.p1.x;
	if (p1.y < other.p1.y) p1.y = other.p1.y;
}

bool Box::intersects(const Box& b) {
	bool xInt = b.p0.x < p1.x&& p0.x < b.p1.x;
	bool yInt = b.p0.y < p1.y&& p0.y < b.p1.y;
	return xInt && yInt;
}

std::tuple<bool, DIRECTION, Vec2F> Box::intersect(const Box& b) {
	bool intersect = intersects(b);
	DIRECTION dir;
	Vec2F diff{};

	if (intersect) {
		Vec2F c{ getCenter() };
		Vec2F otherC{ b.getCenter() };
		Vec2F dc{ c - otherC };

		float halfW = b.w() / 2;
		float halfH = b.h() / 2;
		Vec2F nearest{ std::clamp(dc.x, -halfW, halfW), std::clamp(dc.y, -halfH, halfH) };
		diff = nearest - dc;

		static Vec2F directions[] = { {0.f, 1.f}, {1.f, 0.f}, {0.f, -1.f}, {-1.f, 0.f} };
		float maxDP = -1.f;
		for (int i = 0; i < 4; i++) {
			float dp = dot(diff, directions[i]);
			if (dp > maxDP) {
				dir = static_cast<DIRECTION>(i);
				maxDP = dp;
			}
		}
	}

	return std::make_tuple(intersect, dir, diff);
}