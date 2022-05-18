#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include "Vec2F.h"
#include "box.h"


class Ball {
	public:
		Box b;
		Vec2F vel;

		Ball(uint32_t sz);

		void draw();

		void start();

		bool update(float dt);

		bool collide(const Box& otherB, bool varyVelX, bool alwaysUp);
};