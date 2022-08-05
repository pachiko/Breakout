#include "BrickTiler.h"

std::list<Brick> BrickTiler::tileBricks(const Box& b) {
	int rows = b.h() / brickH;
	int cols = b.w() / brickW;

	float y = b.p0.y;
	std::list<Brick> res;
	for (int i = 0; i < rows; i++) {
		float x = (i % 2 == 1) ? b.p0.x : b.p0.x + offset;
		for (int j = 0; j < cols; j++) {
			res.insert(res.end(), Brick(x, y, brickW, brickH));
			x += spacing + brickW;
			if (x > b.p1.x - brickW) break;
		}
		y += spacing + brickH;
	}
	return res;
}