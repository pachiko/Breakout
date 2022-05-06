#pragma once

#include <algorithm>
#include "Vec2.h"
#include "ball.h"

class Platform {
public:
	Box b;
	Ball* attachedBall;

	Platform(uint32_t width, uint32_t height) {
		b = Box(SCREEN_WIDTH / 2 - width, SCREEN_HEIGHT * 3 / 4 - height, width, height);
		attachedBall = nullptr;
	}

	void draw() {
		b.draw(greenCol);
	}

	void update(int minX, int maxX, int x) {
		int hw = b.w()/2;

		int cx = std::clamp(x, minX + hw, maxX - hw);
		b.setCenterX(cx);
		if (attachedBall != nullptr) {
			attachedBall->b.setCenterX(cx);
		}
	}

	void attachBall(Ball* ball) {
		if (ball != nullptr) {
			attachedBall = ball;
			float h = (b.h() + attachedBall->b.h() + 1)/2; // 1 -> evil epsilon
			Vec2F newCenter = b.getCenter() - Vec2F{ 0, h };
			attachedBall->b.setCenter(newCenter);
			attachedBall->vel = {};
		}
	}

	void detachBall() {
		if (attachedBall != nullptr) {
			attachedBall->start();
			attachedBall = nullptr;
		}
	}
};