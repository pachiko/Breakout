#pragma once

#include <list>
#include "Brick.h"


static constexpr uint32_t brickH{ 20 };
static constexpr uint32_t brickW{ 80 };
static constexpr uint32_t spacing{ 5 };
static constexpr uint32_t offset{ 40 };

class BrickTiler {
public:
	static std::list<Brick> tileBricks(const Box& b);
};