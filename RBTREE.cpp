#include "RBTREE.h"

void RBTree::destroy(Node* node) {
	if (!node)
		return;
	destroy(node->left_);
	destroy(node->right_);
	delete node;
	node = nullptr;
}

void RBTree::leftRotate(Node* x) {
	Node* y = x->right_;
	x->right_ = y->left_;
	if (y->left_)
		y->left_->parent_ = x;
	y->parent_ = x->parent_;
	if (!x->parent_)
		root_ = y;
	else if (x == x->parent_->left_)
		x->parent_->left_ = y;
	else
		x->parent_->right_ = y;
	y->left_ = x;
	x->parent_ = y;
}

void RBTree::rightRotate(Node* x) {
	Node* y = x->left_;
	x->left_ = y->right_;
	if (y->right_)
		y->right_->parent_ = x;
	y->parent_ = x->parent_;
	if (!x->parent_)
		root_ = y;
	else if (x == x->parent_->right_)
		x->parent_->right_ = y;
	else
		x->parent_->left_ = y;
	y->right_ = x;
	x->parent_ = y;
}

void RBTree::insertFixup(Node* node) {
	while (node->parent_ && node->parent_->color_ == RED) {
		if (node->parent_ == node->parent_->parent_->left_) {
			Node* uncle = node->parent_->parent_->right_;
			if (uncle && uncle->color_ == RED) {
				node->parent_->color_ = BLACK;
				uncle->color_ = BLACK;
				node->parent_->parent_->color_ = RED;
				node = node->parent_->parent_;
			}
			else {
				if (node == node->parent_->right_) {
					node = node->parent_;
					leftRotate(node);
				}
				node->parent_->color_ = BLACK;
				node->parent_->parent_->color_ = RED;
				rightRotate(node->parent_->parent_);
			}
		}
		else {
			Node* uncle = node->parent_->parent_->left_;
			if (uncle && uncle->color_ == RED) {
				node->parent_->color_ = BLACK;
				uncle->color_ = BLACK;
				node->parent_->parent_->color_ = RED;
				node = node->parent_->parent_;
			}
			else {
				if (node == node->parent_->left_) {
					node = node->parent_;
					rightRotate(node);
				}
				node->parent_->color_ = BLACK;
				node->parent_->parent_->color_ = RED;
				leftRotate(node->parent_->parent_);
			}
		}
	}
	root_->color_ = BLACK;
}

void RBTree::removeFixup(Node* node, Node* parent, bool isLeft) {
	while (node != root_ && (!node || node->color_ == BLACK)) {
		if (isLeft) {
			Node* sibling = parent->right_;
			if (sibling->color_ == RED) {
				sibling->color_ = BLACK;
				parent->color_ = RED;
				leftRotate(parent);
				sibling = parent->right_;
			}
			if ((!sibling->left_ || sibling->left_->color_ == BLACK) &&
				(!sibling->right_ || sibling->right_->color_ == BLACK)) {
				sibling->color_ = RED;
				node = parent;
				parent = node->parent_;
				isLeft = (node == parent->left_);
			}
			else {
				if (!sibling->right_ || sibling->right_->color_ == BLACK) {
					if (sibling->left_)
						sibling->left_->color_ = BLACK;
					sibling->color_ = RED;
					rightRotate(sibling);
					sibling = parent->right_;
				}
				sibling->color_ = parent->color_;
				parent->color_ = BLACK;
				if (sibling->right_)
					sibling->right_->color_ = BLACK;
				leftRotate(parent);
				node = root_;
			}
		}
		else {
			Node* sibling = parent->left_;
			if (sibling->color_ == RED) {
				sibling->color_ = BLACK;
				parent->color_ = RED;
				rightRotate(parent);
				sibling = parent->left_;
			}
			if ((!sibling->right_ || sibling->right_->color_ == BLACK) &&
				(!sibling->left_ || sibling->left_->color_ == BLACK)) {
				sibling->color_ = RED;
				node = parent;
				parent = node->parent_;
				isLeft = (node == parent->left_);
			}
			else {
				if (!sibling->left_ || sibling->left_->color_ == BLACK) {
					if (sibling->right_)
						sibling->right_->color_ = BLACK;
					sibling->color_ = RED;
					leftRotate(sibling);
					sibling = parent->left_;
				}
				sibling->color_ = parent->color_;
				parent->color_ = BLACK;
				if (sibling->left_)
					sibling->left_->color_ = BLACK;
				rightRotate(parent);
				node = root_;
			}
		}
	}
	if (node)
		node->color_ = BLACK;
}

void RBTree::insert(const int& val) {
	Node* node = new Node(val);
	root_ = insert(root_, node);
	insertFixup(node);
}

RBTree::Node* RBTree::insert(Node* root, Node* node) {
	if (!root) {
		root = node;
		root->parent_ = nullptr;
		return root;
	}
	Node* current = root;
	Node* parent = nullptr;
	while (current) {
		parent = current;
		if (node->data_ < current->data_)
			current = current->left_;
		else
			current = current->right_;
	}
	node->parent_ = parent;
	if (node->data_ < parent->data_)
		parent->left_ = node;
	else
		parent->right_ = node;
	return root;
}

void RBTree::remove(const int& val) {
	root_ = remove(root_, val);
}

RBTree::Node* RBTree::remove(Node* root, const int& val) {
	Node* node = root;
	while (node && node->data_ != val) {
		if (val < node->data_)
			node = node->left_;
		else
			node = node->right_;
	}
	if (!node)
		return root;

	Node* y = node;
	Node* x;
	Color y_original_color = y->color_;
	if (!node->left_) {
		x = node->right_;
		transplant(node, node->right_);
	}
	else if (!node->right_) {
		x = node->left_;
		transplant(node, node->left_);
	}
	else {
		y = minimum(node->right_);
		y_original_color = y->color_;
		x = y->right_;
		if (y->parent_ == node) {
			if (x)
				x->parent_ = y;
		}
		else {
			transplant(y, y->right_);
			y->right_ = node->right_;
			y->right_->parent_ = y;
		}
		transplant(node, y);
		y->left_ = node->left_;
		y->left_->parent_ = y;
		y->color_ = node->color_;
	}
	delete node;
	if (y_original_color == BLACK)
		removeFixup(x, y->parent_, y == y->parent_->left_);
	return root;
}

RBTree::Node* RBTree::minimum(Node* node) {
	while (node->left_)
		node = node->left_;
	return node;
}

void RBTree::transplant(Node* u, Node* v) {
	if (!u->parent_)
		root_ = v;
	else if (u == u->parent_->left_)
		u->parent_->left_ = v;
	else
		u->parent_->right_ = v;
	if (v)
		v->parent_ = u->parent_;
}

void testRBTree() {
	RBTree rbt;
	for (int i = 1; i <= 10; i++) {
		rbt.insert(i);
	}
	rbt.remove(9);
	rbt.remove(10);
	rbt.remove(6);
}

