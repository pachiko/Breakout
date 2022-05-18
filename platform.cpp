#include "platform.h"
#include "color.h"
#include "Engine.h"

Platform::Platform(uint32_t width, uint32_t height) {
	b = Box(SCREEN_WIDTH / 2 - width, SCREEN_HEIGHT * 3 / 4 - height, width, height);
}

void Platform::draw() {
	b.draw(greenCol);
}

void Platform::update(int minX, int maxX, int x) {
	int hw = b.w() / 2;

	int cx = std::clamp(x, minX + hw, maxX - hw);
	b.setCenterX(cx);
	if (attachedBall) {
		attachedBall->b.setCenterX(cx);
	}
}

void Platform::attachBall(const std::shared_ptr<Ball>& ball) {
	if (ball) {
		attachedBall = ball;
		float h = (b.h() + attachedBall->b.h() + 1) / 2; // 1 -> evil epsilon
		Vec2F newCenter = b.getCenter() - Vec2F{ 0, h };
		attachedBall->b.setCenter(newCenter);
		attachedBall->vel = {};
	}
}

void Platform::detachBall() {
	if (attachedBall) {
		attachedBall->start();
		attachedBall = nullptr;
	}
}