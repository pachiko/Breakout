#pragma once

#include <vector>
#include "Brick.h"
#include "color.h"

class QuadTreeNode {
	Box b;
	QuadTreeNode* children[4] = {}; // NE, NW, SW, SE
	std::vector<Brick> bricks; // In-case some bricks overlap more than 1 child
	friend class QuadTree;


	~QuadTreeNode() {
		for (int i = 0; i < 4; i++) {
			delete children[i];
		}
	}


	void build(std::vector<Brick>& bricks) {
		if (bricks.size() > 1) {
			initChildren();
			std::vector<Brick> childrenBricks[4];

			float hw = b.w() / 2.f;
			float hh = b.h() / 2.f;

			// Pass bricks into children
			for (auto it = bricks.begin(); it != bricks.end(); ) {
				if (it->b.w() > hw || it->b.h() > hh) { // Too big
					it++;
					continue;
				}
				
				bool passed = false;
				for (int i = 0; i < 4; i++) {
					passed = passBricks(children[i]->b, bricks, childrenBricks[i], it);
					if (passed) break;
				}

				if (passed) continue;
				it++;
			}

			// Recursive build if child's bricks are not empty
			for (int i = 0; i < 4; i++) {
				if (!childrenBricks[i].empty()) {
					children[i]->build(childrenBricks[i]);
				} else {
					delete children[i];
					children[i] = nullptr;
				}
			}
		}
		
		// Whatever not taken by children, see if this node can surround it
		// If so, take it yourself; else, pass to parent
		for (auto it = bricks.begin(); it != bricks.end(); ) {
			if (passBricks(b, bricks, this->bricks, it)) continue;
			it++;
		}
	}


	bool passBricks(const Box& b1, std::vector<Brick>& v1, std::vector<Brick>& v2, std::vector<Brick>::iterator& it) {
		if (b1.surrounds(it->b)) {
			v2.insert(v2.end(), std::make_move_iterator(it), std::make_move_iterator(it + 1));
			v1.erase(it, it + 1);
			it = v1.begin();
			return true;
		}
		return false;
	}


	void initChildren() {
		for (int i = 0; i < 4; i++) {
			children[i] = new QuadTreeNode;
		}

		float hw = b.w() / 2.f;
		float hh = b.h() / 2.f;

		Box ne{ b.p0.x + hw, b.p0.y, hw, hh };
		Box nw{ b.p0.x, b.p0.y, hw, hh };
		Box sw{ b.p0.x, b.p0.y + hh, hw, hh };
		Box se{ b.p0.x + hw, b.p0.y + hh, hw, hh };

		children[0]->b = ne;
		children[1]->b = nw;
		children[2]->b = sw;
		children[3]->b = se;
	}


	bool childless() {
		for (int i = 0; i < 4; i++) if (children[i]) return false;
		return true;
	}


	bool collDet(Ball& ball) {
		if (!b.intersects(ball.b)) return false;

		for (int i = 0; i < 4; i++) {
			if (children[i]) {
				if (children[i]->collDet(ball)) {
					if (children[i]->bricks.empty() && children[i]->childless()) {
						delete children[i];
						children[i] = nullptr;
					}
					return true;
				}
			}
		}

		for (auto it = bricks.begin(); it != bricks.end(); it++) {
			if (ball.collide(it->b, true, false)) {
				bricks.erase(it, it + 1);
				return true;
			}
		}
		
		return false;
	}


	void visualize() {
		b.drawWire(pinkCol);

		for (int i = 0; i < 4; i++) {
			if (children[i]) {
				children[i]->visualize();
			}
		}
	}


	void draw() {
		for (auto& brick : bricks) {
			brick.draw();
		}

		for (int i = 0; i < 4; i++) {
			if (children[i]) {
				children[i]->draw();
			}
		}
	}
};