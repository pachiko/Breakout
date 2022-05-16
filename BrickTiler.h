#pragma once

#include <vector>
#include "Brick.h"


static constexpr uint32_t brickH{ 20 };
static constexpr uint32_t brickW{ 80 };
static constexpr uint32_t spacing{ 5 };
static constexpr uint32_t offset{ 40 };

class BrickTiler {
public:
	static std::vector<Brick> tileBricks(const Box& b) {
		int rows = b.h() / brickH;
		int cols = b.w() / brickW;

		float y = b.p0.y;
		std::vector<Brick> res;
		for (int i = 0; i < rows; i++) {
			float x = (i % 2 == 1)? b.p0.x : b.p0.x + offset;
			for (int j = 0; j < cols; j++) {
				res.push_back(Brick(x, y, brickW, brickH));
				x += spacing + brickW;
				if (x > b.p1.x - brickW) break;
			}
			y += spacing + brickH;
		}
		return res;
	}
};