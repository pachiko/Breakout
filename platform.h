#pragma once

#include <algorithm>
#include <memory>
#include "box.h"
#include "ball.h"

class Platform {
public:
	Box b;
	std::shared_ptr<Ball> attachedBall;

	Platform(uint32_t width, uint32_t height);

	void draw();

	void update(int minX, int maxX, int x);

	void attachBall(const std::shared_ptr<Ball>& ball);

	void detachBall();
};