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

			std::vector<Brick> ne;
			std::vector<Brick> nw;
			std::vector<Brick> sw;
			std::vector<Brick> se;

			float hw = b.w() / 2.f;
			float hh = b.h() / 2.f;

			for (auto it = bricks.begin(); it != bricks.end(); ) {
				if (it->b.w() > hw || it->b.h() > hh) {
					it++;
					continue;
				}

				if (children[0]->b.surrounds(it->b)) {
					ne.insert(ne.end(), std::make_move_iterator(it), std::make_move_iterator(it + 1));
					bricks.erase(it, it + 1);
					it = bricks.begin();
					continue;
				}
				else if (children[1]->b.surrounds(it->b)) {
					nw.insert(nw.end(), std::make_move_iterator(it), std::make_move_iterator(it + 1));
					bricks.erase(it, it + 1);
					it = bricks.begin();
					continue;
				}
				else if (children[2]->b.surrounds(it->b)) {
					sw.insert(sw.end(), std::make_move_iterator(it), std::make_move_iterator(it + 1));
					bricks.erase(it, it + 1);
					it = bricks.begin();
					continue;
				}
				else if (children[3]->b.surrounds(it->b)) {
					se.insert(se.end(), std::make_move_iterator(it), std::make_move_iterator(it + 1));
					bricks.erase(it, it + 1);
					it = bricks.begin();
					continue;
				}

				it++;
			}

			if (!ne.empty()) children[0]->build(ne);
			else {
				delete children[0];
				children[0] = nullptr;
			}
			if (!nw.empty()) children[1]->build(nw);
			else {
				delete children[1];
				children[1] = nullptr;
			}
			if (!sw.empty()) children[2]->build(sw);
			else {
				delete children[2];
				children[2] = nullptr;
			}
			if (!se.empty()) children[3]->build(se);
			else {
				delete children[3];
				children[3] = nullptr;
			}
		}

		
		// Whatever not taken by children, see if this node can surround it
		// If so, take it yourself; else, pass to parent
		for (auto it = bricks.begin(); it != bricks.end(); ) {
			if (b.surrounds(it->b)) {
				this->bricks.insert(this->bricks.end(), std::make_move_iterator(it), std::make_move_iterator(it + 1));
				bricks.erase(it, it + 1);
				it = bricks.begin();
				continue;
			}
			it++;
		}
	}

	void initChildren() {
		children[0] = new QuadTreeNode;
		children[1] = new QuadTreeNode;
		children[2] = new QuadTreeNode;
		children[3] = new QuadTreeNode;

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