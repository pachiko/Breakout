#include "QuadTree.h"


QuadTree::QuadTree(std::list<Brick>& bricks) {
	root = std::make_unique<QuadTreeNode>();
	for (auto& brick : bricks) {
		root->b.include(brick.b);
	}
	root->b.grow(1.f);
	root->build(bricks);
}


bool QuadTree::collDet(const std::shared_ptr<Ball>& ball) {
	return root->collDet(ball);
}


void QuadTree::visualize() {
	root->visualize();
}


void QuadTree::draw() {
	root->draw();
}