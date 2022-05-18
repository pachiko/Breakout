#pragma once

#include <vector>
#include <memory>
#include "Brick.h"
#include "ball.h"

class QuadTreeNode {
	Box b;
	std::unique_ptr<QuadTreeNode> children[4]; // NE, NW, SW, SE
	std::vector<Brick> bricks; // In-case some bricks overlap more than 1 child
	friend class QuadTree;


	void build(std::vector<Brick>& bricks);

	bool passBricks(const Box& b1, std::vector<Brick>& v1, std::vector<Brick>& v2, std::vector<Brick>::iterator& it);

	void initChildren();

	bool childless();

	bool collDet(const std::shared_ptr<Ball>& ball);

	void visualize();

	void draw();
};