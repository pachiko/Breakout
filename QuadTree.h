#pragma once

#include "QuadTreeNode.h"

class QuadTree {
	QuadTreeNode* root;

public:
	QuadTree(std::vector<Brick>& bricks) {
		root = new QuadTreeNode;
		for (auto& brick : bricks) {
			root->b.include(brick.b);
		}
		root->b.grow(1.f);
		root->build(bricks);
	}


	~QuadTree() {
		delete root;
	}


	bool collDet(Ball& ball) {
		return root->collDet(ball);
	}


	void visualize() {
		root->visualize();
	}


	void draw() {
		root->draw();
	}
};