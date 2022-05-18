#include "wall.h"
#include "Engine.h"
#include "color.h"

Wall::Wall(uint32_t start, uint32_t thickness, bool isVertical) {
    int y = isVertical ? 0 : start;
    int x = isVertical ? start : 0;
    b = Box(x, y, isVertical ? thickness : SCREEN_WIDTH, isVertical ? SCREEN_HEIGHT : thickness);
}

void Wall::draw() {
    b.draw(redCol);
}