#pragma once

#include "box.h"

class Wall {
    public:
        Box b;

        Wall(uint32_t start, uint32_t thickness, bool isVertical);
	    
        void draw();
};