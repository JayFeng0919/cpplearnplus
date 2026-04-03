#include "BSTREE.h"

BSTREE::BSTREE():root_(nullptr){}

BSTREE::~BSTREE() { destroy(root_); }

int BSTREE::high() {
	return high(root_);
}

int BSTREE::high(Node* node) {
	if (!node)
		return 0;
	int left = high(node->left_);
	int right = high(node->right_);
	return left > right ? left + 1 : right + 1;
}

int BSTREE::number() {
	return number(root_);
}

int BSTREE::number(Node* node) {
	if (!node)
		return 0;
	int left = number(node->left_);
	int right = number(node->right_);
	return left + right + 1;
}

void BSTREE::n_insert(const int& val) {
	if (!root_) {
		root_ = new Node(val);
		return;
	}
	Node* parent = nullptr;
	Node* cur = root_;
	while (cur) {
		if (val < cur->data_) {
			parent = cur;
			cur = cur->left_;
		}
		else if (val > cur->data_) {
			parent = cur;
			cur = cur->right_;
		}
		else {
			return;
		}
	}
	if (val < parent->data_) {
		parent->left_ = new Node(val);
	}
	else {
		parent->right_ = new Node(val);
	}
}

void BSTREE::n_remove(const int& val) {
	if (!root_)
		return;
	Node* parent = nullptr;
	Node* cur = root_;
	while (cur) {
		if (val < cur->data_) {
			parent = cur;
			cur = cur->left_;
		}
		else if (val > cur->data_) {
			parent = cur;
			cur = cur->right_;
		}
		else {
			break;
		}
	}
	if (!cur)
		return;
	if (cur->left_ && cur->right_) {
		Node* pre_parent = cur;
		Node* pre = cur->left_;
		while (pre->right_) {
			pre_parent = pre;
			pre = pre->right_;
		}
		cur->data_ = pre->data_;
		parent = pre_parent;
		cur = pre;
	}

	Node* child = cur->left_;
	if (!child) {
		child = cur->right_;
	}
	if (!parent) {
		root_ = child;
	}
	else {
		if (parent->left_ == cur) {
			parent->left_ = child;
		}
		else {
			parent->right_ = child;
		}
	}

	delete cur;
}

bool BSTREE::n_query(const int& val) {
	if (!root_)
		return false;
	Node* cur = root_;
	while (cur) {
		if (val < cur->data_) {
			cur = cur->left_;
		}
		else if (val > cur->data_) {
			cur = cur->right_;
		}
		else {
			return true;
		}
	}
	return false;
}

void BSTREE::preorder() {
	preorder(root_);
	std::cout << std::endl;
}

void BSTREE::preorder(Node* node) {
	if (!node)
		return;
	std::cout << node->data_ << " ";
	preorder(node->left_);
	preorder(node->right_);
}

void BSTREE::inorder() {
	inorder(root_);
	std::cout << std::endl;
}

void BSTREE::inorder(Node* node) {
	if (!node)
		return;
	preorder(node->left_);
	std::cout << node->data_ << " ";
	preorder(node->right_);
}

void BSTREE::postorder() {
	postorder(root_);
	std::cout << std::endl;
}

void BSTREE::postorder(Node* node) {
	if (!node)
		return;
	preorder(node->left_);
	preorder(node->right_);
	std::cout << node->data_ << " ";
}

void BSTREE::insert(const int& val) {
	root_ = insert(root_, val);
}

BSTREE::Node* BSTREE::insert(Node* node, const int& val) {
	if (!node) {
		return new Node(val);
	}
	if (val < node->data_) {
		node->left_ = insert(node->left_, val);
	}
	else if (val > node->data_) {
		node->right_ = insert(node->right_, val);
	}
	else {
		return node;
	}
	return node;
}

void BSTREE::remove(const int& val) {
	root_ = remove(root_, val);
}

BSTREE::Node* BSTREE::remove(Node* node, const int& val) {
	if (!node) {
		return nullptr;
	}
	if (node->data_ == val) {
		if (node->left_ && node->right_) {
			Node* pre = node->left_;
			while (pre->right_) {
				pre = pre->right_;
			}
			node->data_ = pre->data_;
			node->left_ = remove(node->left_, pre->data_);
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
	else if (val < node->data_) {
		node->left_ = remove(node->left_, val);
	}
	else {
		node->right_ = remove(node->right_, val);
	}
	return node;
}

bool BSTREE::query(const int& val) {
	return query(root_, val);
}

bool BSTREE::query(Node* node, const int& val) {
	if (!node)
		return false;
	if (val < node->data_) {
		return query(node->left_, val);
	}
	else if (val > node->data_) {
		return query(node->right_, val);
	}
	else {
		return true;
	}
}

void BSTREE::n_preorder() {
	if (!root_)
		return;
	std::stack<Node*> s;
	s.emplace(root_);
	while (!s.empty()) {
		Node* top = s.top();
		s.pop();
		std::cout << top->data_ << " ";

		if (top->right_) {
			s.emplace(top->right_);
		}
		if (top->left_) {
			s.emplace(top->left_);
		}
	}
	std::cout << std::endl;
}

void BSTREE::n_inorder() {
	if (!root_)
		return;
	std::stack<Node*> s;
	Node* cur = root_;
	while (!s.empty() || cur) {
		if (cur) {
			s.emplace(cur);
			cur = cur->left_;
		}
		else {
			Node* top = s.top();
			s.pop();
			std::cout << top->data_ << " ";
			cur = top->right_;
		}
	}
	std::cout << std::endl;
}

void BSTREE::n_postorder() {
	if (!root_)
		return;
	std::stack<Node*> s1, s2;
	s1.emplace(root_);
	while (!s1.empty()) {
		Node* top = s1.top();
		s1.pop();
		s2.emplace(top);
		if (top->left_) {
			s1.emplace(top->left_);
		}
		if (top->right_) {
			s1.emplace(top->right_);
		}
	}
	while (!s2.empty()) {
		std::cout << s2.top()->data_ << " ";
		s2.pop();
	}
	std::cout << std::endl;
}

void BSTREE::levelorder() {
	int h = high();
	for (int i = 0; i < h; i++) {
		levelorder(root_, i);
	}
	std::cout << std::endl;
}

void BSTREE::levelorder(Node* node, int i) {
	if (!node)
		return;
	if (i == 0) {
		std::cout << node->data_ << " ";
		return;
	}
	levelorder(node->left_, i - 1);
	levelorder(node->right_, i - 1);
}

void BSTREE::n_levelorder() {
	if (!root_)
		return;
	std::queue<Node*> q;
	q.emplace(root_);
	while (!q.empty()) {
		Node* front = q.front();
		std::cout << front->data_ << " ";
		q.pop();
		if (front->left_) {
			q.emplace(front->left_);
		}
		if (front->right_) {
			q.emplace(front->right_);
		}
	}
	std::cout << std::endl;
}

void::BSTREE::destroy(Node* node) {
	if (!node)
		return;
	destroy(node->left_);
	destroy(node->right_);
	delete node;
	node = nullptr;
}

void BSTREE::findValues(std::vector<int>& vec, const int& i, const int& j) {
	findValues(root_, vec, i, j);
}

void BSTREE::findValues(Node* node, std::vector<int>& vec, const int& i, const int& j) {
	if (!node)
		return;
	if (i <= node->data_ && node->data_ <= j) {
		vec.emplace_back(node->data_);
		findValues(node->left_, vec, i, j);
		findValues(node->right_, vec, i, j);
	}
	else if (node->data_ < i) {
		findValues(node->right_, vec, i, j);
	}
	else {
		findValues(node->left_, vec, i, j);
	}
}

bool BSTREE::isBSTree() {
	return isBSTree(root_, LLONG_MIN, LLONG_MAX);
}

bool BSTREE::isBSTree(Node* node, long long lower, long long upper) {
	if (!node) {
		return true;
	}
	if (node->data_ <= lower || node->data_ >= upper) {
		return false;
	}
	return isBSTree(node->left_, lower, node->data_) && isBSTree(node->right_, node->data_, upper);
}

bool BSTREE::isChild(BSTREE& child) {
	if (!child.root_)
		return true;
	Node* cur = root_;
	while (cur) {
		if (cur->data_ == child.root_->data_) {
			break;
		}
		else if (cur->data_ < child.root_->data_) {
			cur = cur->right_;
		}
		else {
			cur = cur->left_;
		}
	}
	if (!cur)
		return false;
	return isChild(cur, child.root_);
}

bool BSTREE::isChild(Node* father, Node* child) {
	if (!father && !child)
		return true;
	if (!father)
		return false;
	if (!child)
		return true;
	if (father->data_ != child->data_) {
		return false;
	}
	return isChild(father->left_, child->left_) && isChild(father->right_, child->right_);
}

int BSTREE::getLCA(const int& val1, const int& val2) {
	if (!query(val1) || !query(val2))
		throw "not exist";
	if (val1 == val2) {
		return val1;
	}
	Node* node = getLCA(root_, val1, val2);
	return node->data_;
}

BSTREE::Node* BSTREE::getLCA(Node* node, const int& val1, const int& val2) {
	if (!node)
		return nullptr;
	if (node->data_ < val1 && node->data_ < val2) {
		return getLCA(node->right_, val1, val2);
	}
	else if (node->data_ > val1 && node->data_ > val2) {
		return getLCA(node->left_, val1, val2);
	}
	else {
		return node;
	}
}

void BSTREE::mirror_reversal() {
	mirror_reversal(root_);
}

void BSTREE::mirror_reversal(Node* node) {
	if (!node)
		return;
	Node* tmp = node->left_;
	node->left_ = node->right_;
	node->right_ = tmp;
	mirror_reversal(node->left_);
	mirror_reversal(node->right_);
}

bool BSTREE::mirror() {
	if (!root_)
		return true;
	return mirror(root_->left_,root_->right_);
}

bool BSTREE::mirror(Node* node1, Node* node2) {
	if (!node1 && !node2)
		return true;
	if (!node1)
		return false;
	if (!node2)
		return false;
	if (node1->data_ != node2->data_) {
		return false;
	}
	return mirror(node1->left_, node2->right_) && mirror(node1->right_, node2->left_);
}

void BSTREE::rebuild(int pre[], int i, int j, int in[], int m, int n) {
	root_ = reBuild(pre, i, j, in, m, n);
}

BSTREE::Node* BSTREE::reBuild(int pre[], int i, int j, int in[], int m, int n) {
	if (i > j || m > n)
		return nullptr;
	Node* node = new Node(pre[i]);
	for (int k = m; k <= n; k++) {
		if (pre[i] = in[k]) {
			node->left_ = reBuild(pre, i + 1, i + k - m, in, m, k - 1);
			node->right_ = reBuild(pre, i + k - m + 1, j, in, k + 1, n);
			return node;
		}
	}
	delete node;
	throw std::invalid_argument("前序和中序数组不匹配：根节点未在中序区间中找到");
}

bool BSTREE::isBalance() {
	int l = 0;
	bool flag = true;
	isBalance(root_, l, flag);
	return flag;
}

int BSTREE::isBalance(Node* node, int l, bool& flag) {
	if (!node)
		return l;
	int left = isBalance(node->left_, l + 1, flag);
	if (!flag) {
		return left;
	}
	int right = isBalance(node->right_, l + 1, flag);
	if (!flag) {
		return right;
	}

	if (abs(left - right) > 1) {
		flag = false;
	}
	return std::max(left, right);
}

int BSTREE::getKval(int k) {
	int i = 0;
	Node* node = getKval(root_, k, i);
	if (!node)
		throw "no Node";
	return node->data_;
}

BSTREE::Node* BSTREE::getKval(Node* node, int k, int& i) {
	if (!node)
		return nullptr;

	Node* right = getKval(node->right_, k, i);
	if (right) {
		return right;
	}
	i++;
	if (i == k) {
		return node;
	}
	return getKval(node->left_, k, i);
}
