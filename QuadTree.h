#pragma once

#include <memory>
#include "QuadTreeNode.h"
#include "ball.h"

class QuadTree {
	std::unique_ptr<QuadTreeNode> root;

public:
	QuadTree(std::vector<Brick>& bricks);

	bool collDet(const std::shared_ptr<Ball>& ball);

	void visualize();

	void draw();
};