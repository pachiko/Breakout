#pragma once

#include "QuadTreeNode.h"

class QuadTree {
	std::unique_ptr<QuadTreeNode> root;

public:
	QuadTree(std::vector<Brick>& bricks) {
		root = std::make_unique<QuadTreeNode>();
		for (auto& brick : bricks) {
			root->b.include(brick.b);
		}
		root->b.grow(1.f);
		root->build(bricks);
	}


	bool collDet(const std::shared_ptr<Ball>& ball) {
		return root->collDet(ball);
	}


	void visualize() {
		root->visualize();
	}


	void draw() {
		root->draw();
	}
};