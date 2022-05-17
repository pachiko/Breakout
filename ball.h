#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include "Vec2F.h"


class Ball {
	public:
		Box b;
		Vec2F vel;


		Ball(uint32_t sz) {
			b = Box(0, 0, sz, sz);
			vel = Vec2F{};
		}


		void draw() {
			b.draw(whiteCol);
		}


		void start() {
			vel = { 0.f, -2.f };
		}


		bool update(float dt) {
			dt = std::max(dt, 0.1f);
			b.move(vel*dt);
			if (b.p1.y >= SCREEN_HEIGHT) {
				return true;
			}
			return false;
		}


		bool collide(const Box& otherB, bool varyVelX, bool alwaysUp) {
			auto res{ b.intersect(otherB) };

			if (std::get<0>(res)) {
				Vec2F diff{ std::get<2>(res) };
				DIRECTION dir{ std::get<1>(res) };

				Vec2F d{ b.w() / 2 - std::abs(diff.x), b.h() / 2 - std::abs(diff.y) };
				if (dir == RIGHT || dir == LEFT) {
					b.move({ dir == RIGHT ? -d.x : d.x, 0.f});

					vel.x = -vel.x;
				}
				else {
					b.move({ 0.f, dir == UP ? -d.y : d.y });
					vel.y = -vel.y;
				}

				if (varyVelX) {
					float ratio = (b.getCenterX() - otherB.getCenterX()) / (otherB.w() / 2); // [-1, 1]
					ratio = std::clamp(ratio, -0.7f, 0.7f); // Don't want tangentials
					float angle = M_PI_2*(1.0 - static_cast<double>(ratio)); // [0, PI]
					float norm = std::sqrt(normSqr(vel));
					vel.x = norm * std::cosf(angle);
					float speedY = norm * std::sinf(angle);

					if (alwaysUp) {
						vel.y = -speedY; // always go up for platform
					}
					else {
						vel.y = (vel.y < 0) ? -speedY : speedY; // can be up/down for bricks
					}
				}
			}

			return std::get<0>(res);
		}
};