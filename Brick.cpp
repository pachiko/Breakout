#include "Brick.h"
#include "color.h"


Brick::Brick(uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
	b = Box(x, y, w, h);
}

void Brick::draw() {
	b.draw(blueCol);
}