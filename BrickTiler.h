#pragma once

#include <vector>
#include "Brick.h"


static constexpr uint32_t brickH{ 20 };
static constexpr uint32_t brickW{ 80 };
static constexpr uint32_t spacing{ 5 };
static constexpr uint32_t offset{ 40 };

class BrickTiler {
public:
	static std::vector<Brick> tileBricks(const Box& b);
};