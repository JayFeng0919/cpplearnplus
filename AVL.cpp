#include "AVL.h"

void AVL::destroy(Node* node) {
	if (!node)
		return;
	destroy(node->left_);
	destroy(node->right_);
	delete node;
	node = nullptr;
}

int AVL::height(Node* node) {
	return node == nullptr ? 0 : node->height_;
}

AVL::Node* AVL::LL(Node* node) {
	Node* child = node->left_;
	node->left_ = child->right_;
	child->right_ = node;
	node->height_ = std::max(height(node->left_), height(node->right_)) + 1;
	child->height_ = std::max(height(child->left_), height(child->right_)) + 1;
	return child;
}

AVL::Node* AVL::RR(Node* node) {
	Node* child = node->right_;
	node->right_ = child->left_;
	child->left_ = node;
	node->height_ = std::max(height(node->left_), height(node->right_)) + 1;
	child->height_ = std::max(height(child->left_), height(child->right_)) + 1;
	return child;
}

AVL::Node* AVL::LR(Node* node) {
	node->left_ = RR(node->left_);
	return LL(node);
}

AVL::Node* AVL::RL(Node* node) {
	node->right_ = LL(node->right_);
	return RR(node);
}

void AVL::insert(const int& val) {
	root_ = insert(root_, val);
}

AVL::Node* AVL::insert(Node* node, const int& val) {
	if (!node)
		return new Node(val);

	if (val < node->data_) {
		node->left_ = insert(node->left_, val);
		if (height(node->left_) - height(node->right_) > 1) {
			if (height(node->left_->left_) >= height(node->left_->right_)) {
				node = LL(node);
			}
			else {
				node = LR(node);
			}
		}
	}
	else if (val > node->data_) {
		node->right_ = insert(node->right_, val);
		if (height(node->right_) - height(node->left_) > 1) {
			if (height(node->right_->right_) >= height(node->right_->left_)) {
				node = RR(node);
			}
			else {
				node = RL(node);
			}
		}
	}
	else{}         // 显式处理相等

	node->height_ = std::max(height(node->left_), height(node->right_)) + 1;

	return node;
}

void AVL::remove(const int& val) {
	root_ = remove(root_, val);
}

AVL::Node* AVL::remove(Node* node, const int& val) {
	if (!node)
		return nullptr;
	if (val < node->data_) {
		node->left_ = remove(node->left_, val);
		if (height(node->right_) - height(node->left_) > 1) {
			if (height(node->right_->right_) >= height(node->right_->left_)) {
				node = RR(node);
			}
			else {
				node = RL(node);
			}
		}
	}
	else if (val > node->data_) {
		node->right_ = remove(node->right_, val);
		if (height(node->left_) - height(node->right_) > 1) {
			if (height(node->left_->left_) >= height(node->left_->right_)) {
				node = LL(node);
			}
			else {
				node = LR(node);
			}
		}
	}
	else {
		if (node->left_ && node->right_) {
			if (height(node->left_) >= height(node->right_)) {
				Node* pre = node->left_;
				while (pre->right_) {
					pre = pre->right_;
				}
				node->data_ = pre->data_;
				node->left_ = remove(node->left_, pre->data_);
			}
			else {
				Node* suc = node->right_;
				while (suc->left_) {
					suc = suc->left_;
				}
				node->data_ = suc->data_;
				node->right_ = remove(node->right_, suc->data_);
			}
		}
		else {
			if (node->left_) {
				Node* left = node->left_;
				delete node;
				return left;
			}
			else if (node->right_) {
				Node* right = node->right_;
				delete node;
				return right;
			}
			else {
				delete node;
				return nullptr;
			}
		}
	}
	node->height_ = std::max(height(node->left_), height(node->right_)) + 1;
	return node;
}

void testAVL() {
	AVL avl;
	for (int i = 1; i <= 10; i++) {
		avl.insert(i);
	}
	avl.remove(9);
	avl.remove(10);
	avl.remove(6);
}