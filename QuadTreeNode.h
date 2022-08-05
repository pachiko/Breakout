#pragma once

#include <list>
#include <memory>
#include "Brick.h"
#include "ball.h"

class QuadTreeNode {
	Box b;
	std::unique_ptr<QuadTreeNode> children[4]; // NE, NW, SW, SE
	std::list<Brick> bricks; // In-case some bricks overlap more than 1 child
	friend class QuadTree;


	void build(std::list<Brick>& bricks);

	bool passBricks(const Box& b1, std::list<Brick>& v1, std::list<Brick>& v2, std::list<Brick>::iterator& it);

	void initChildren();

	bool childless();

	bool collDet(const std::shared_ptr<Ball>& ball);

	void visualize();

	void draw();
};