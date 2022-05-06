#pragma once

#include "color.h"
#include "box.h"

class Wall {
    public:
        Box b;

	    Wall(uint32_t start, uint32_t thickness, bool isVertical) {
            int y = isVertical ? 0 : start;
            int x = isVertical ? start : 0;
            b = Box(x, y, isVertical? thickness : SCREEN_WIDTH, isVertical? SCREEN_HEIGHT : thickness);
	    }

        void draw() {
            b.draw(redCol);
        }
};