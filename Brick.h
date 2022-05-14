#pragma once

#include "Box.h"

class Brick {
public:
	Box b;

	Brick(uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
		b = Box(x, y, w, h);
	}

	void draw() {
		b.draw(blueCol);
	}
};