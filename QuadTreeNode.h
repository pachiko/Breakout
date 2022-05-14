#pragma once

#include "Brick.h"

class QuadTreeNode {
	QuadTreeNode* children[4]; // NE, NW, SW, SE
	Brick* bricks[2]; // at most 2 bricks


};