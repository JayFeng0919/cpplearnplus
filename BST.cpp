#include"BST.h"

template <typename T, typename Compare>
BSTree<T, Compare>::BSTree(Compare comp) :root_(nullptr), comp_(comp) {}

template <typename T, typename Compare>
BSTree<T, Compare>::~BSTree() { destroy(root_); }

template <typename T, typename Compare>
void BSTree<T, Compare>::n_insert(const T& val) {
	if (!root_) {
		root_ = new Node(val);
		return;
	}

	Node* parent = nullptr;
	Node* cur = root_;
	while (cur) {
		if (comp_(val, cur->data_)) {
			parent = cur;
			cur = cur->left_;
		}
		else if (comp_(cur->data_, val)) {
			parent = cur;
			cur = cur->right_;
		}
		else
			return;
	}

	if (comp_(val, parent->data_))
		parent->left_ = new Node(val);
	else
		parent->right_ = new Node(val);
}

template <typename T, typename Compare>
void BSTree<T, Compare>::insert(const T& val) {
	root_ = insert(root_, val);
}

template <typename T, typename Compare>
void BSTree<T, Compare>::n_remove(const T& val) {
	if (!root_) return;
	Node* parent = nullptr;
	Node* cur = root_;
	while (cur) {
		if (comp_(val, cur->data_)) {
			parent = cur;
			cur = cur->left_;
		}
		else if (comp_(cur->data_, val)) {
			parent = cur;
			cur = cur->right_;
		}
		else
			break;
	}

	if (!cur) return;    // 没找到待删节点
	if (cur->left_ && cur->right_) {     // 处理左右孩子不为空
		Node* pre_parent = cur;
		Node* pre = cur->left_;
		while (pre->right_) {
			pre_parent = pre;
			pre = pre->right_;
		}
		cur->data_ = pre->data_;
		cur = pre;
		parent = pre_parent;
	}

	// cur指向待删除节点，pre指向其父节点
	Node* child = cur->left_;
	if (!child)
		child = cur->right_;
	if (!parent)
		root_ = child;
	else {
		if (parent->left_ == cur)
			parent->left_ = child;
		else
			parent->right_ = child;
	}

	delete cur;
}

template <typename T, typename Compare>
void BSTree<T, Compare>::remove(const T& val) {
	root_ = remove(root_, val);
}

template<typename T,typename Compare>
bool BSTree<T, Compare>::n_query(const T& val) {
	Node* cur = root_;
	while (cur) {
		if (comp_(val, cur->data_))
			cur = cur->left_;
		else if (comp_(cur->data_, val))
			cur = cur->right_;
		else
			return true;
	}
	return false;
}

template<typename T, typename Compare>
bool BSTree<T, Compare>::query(const T& val) {
	return nullptr != query(root_, val);
}

template<typename T, typename Compare>
void BSTree<T, Compare>::preorder_traversal() {
	preorder_traversal(root_);
	std::cout << std::endl;
}

template<typename T, typename Compare>
void BSTree<T, Compare>::n_preorder_traversal() {
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

template<typename T, typename Compare>
void BSTree<T, Compare>::inorder_traversal() {
	inorder_traversal(root_);
	std::cout << std::endl;
}

template<typename T, typename Compare>
void BSTree<T, Compare>::n_inorder_traversal() {
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

template<typename T, typename Compare>
void BSTree<T, Compare>::postorder_traversal() {
	postorder_traversal(root_);
	std::cout << std::endl;
}

template<typename T, typename Compare>
void BSTree<T, Compare>::n_postorder_traversal() {
	if (!root_)
		return;

	std::stack<Node*> s1;
	std::stack<Node*> s2;
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

template<typename T, typename Compare>
void BSTree<T, Compare>::levelorder_traversal() {
	int h = high();
	for (int i = 0; i < h; i++) {
		levelorder_traversal(root_, i);
	}
	std::cout << std::endl;
}

template<typename T, typename Compare>
void BSTree<T, Compare>::n_levelorder_traversal() {
	if (!root_)
		return;

	std::queue<Node*> q;
	q.emplace(root_);
	while (!q.empty()) {
		Node* front = q.front();
		q.pop();
		std::cout << front->data_ << " ";
		if (front->left_) {
			q.emplace(front->left_);
		}
		if (front->right_) {
			q.emplace(front->right_);
		}
	}
	std::cout << std::endl;
}

template<typename T, typename Compare>
int BSTree<T, Compare>::high() {
	return high(root_);
}

template<typename T, typename Compare>
int BSTree<T, Compare>::number() {
	return number(root_);
}

template<typename T, typename Compare>
void BSTree<T, Compare>::findValues(std::vector<T>& vec, int i, int j) {
	findValues(root_, vec, i, j);
}

template<typename T, typename Compare>
bool BSTree<T, Compare>::isBSTree() {
	Node* pre = nullptr;
	return isBSTree(root_, pre);
}

template<typename T, typename Compare>
bool BSTree<T, Compare>::isChild(BSTree<T, Compare>& child) {
	if (child.root_ == nullptr) {
		return true;
	}

	Node* cur = root_;
	while (cur) {
		if (cur->data_ == child.root_->data_) {
			break;
		}
		else if (comp_(cur->data_, child.root_->data_)) {
			cur = cur->right_;
		}
		else {
			cur = cur->left_;
		}
	}
	if (!cur) {
		return false;
	}

	return isChild(cur, child.root_);
}

template<typename T, typename Compare>
T BSTree<T, Compare>::getLCA(const T& val1, const T& val2) {
	if (!query(val1) || !query(val2)) {
		throw "not exist";
	}
	if (val1 == val2) {
		return val1;
	}

	Node* node = getLCA(root_, val1, val2);
	if (!node) {
		throw "no LCA";
	}
	return node->data_;

}

template<typename T, typename Compare>
void BSTree<T, Compare>::mirror_reversal() {
	mirror_reversal(root_);
}

template<typename T, typename Compare>
bool BSTree<T, Compare>::mirror() {
	if (!root_)
		return true;
	return mirror(root_->left_, root_->right_);
}

template<typename T, typename Compare>
void BSTree<T, Compare>::rebuild(T pre[], int i, int j, T in[], int m, int n) {
	root_ = reBuild(pre, i, j, in, m, n);
}

template<typename T, typename Compare>
bool BSTree<T, Compare>::isBalance() {
	int l = 0;
	bool flag = true;
	isBalance(root_, l, flag);
	return flag;
}

template<typename T, typename Compare>
T BSTree<T, Compare>::getKval(int k) {
	int i = 0;
	Node* node = getKval(root_, k, i);
	if (!node)
		throw "no Node";
	return node->data_;
}

template<typename T, typename Compare>
typename BSTree<T, Compare>::Node* BSTree<T, Compare>::insert(Node* node, const T& val) {
	if (!node) {
		return new Node(val);
	}

	if (node->data_ == val) {
		return node;
	}
	else if (comp_(node->data_, val)) {
		node->right_ = insert(node->right_, val);
	}
	else {
		node->left_ = insert(node->left_, val);
	}
	return node;
}

template<typename T, typename Compare>
typename BSTree<T, Compare>::Node* BSTree<T, Compare>::remove(Node* node, const T& val) {
	if (!node)
		return nullptr;

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
	else if (comp_(node->data_, val))
		node->right_ = remove(node->right_, val);
	else
		node->left_ = remove(node->left_, val);

	return node;
}

template<typename T, typename Compare>
typename BSTree<T, Compare>::Node* BSTree<T, Compare>::query(Node* node, const T& val) {
	if (!node)
		return nullptr;
	if (node->data_ == val)
		return node;
	else if (comp_(node->data_, val))
		return query(node->right_, val);
	else
		return query(node->left_, val);
}

template<typename T,typename Compare>
void BSTree<T, Compare>::preorder_traversal(Node* node) {
	if (!node) return;

	std::cout << node->data_ << " ";
	preorder_traversal(node->left_);
	preorder_traversal(node->right_);
}

template<typename T, typename Compare>
void BSTree<T, Compare>::inorder_traversal(Node* node) {
	if (!node) return;

	inorder_traversal(node->left_);
	std::cout << node->data_ << " ";
	inorder_traversal(node->right_);
}

template<typename T, typename Compare>
void BSTree<T, Compare>::postorder_traversal(Node* node) {
	if (!node) return;

	postorder_traversal(node->left_);
	postorder_traversal(node->right_);
	std::cout << node->data_ << " ";
}

template<typename T, typename Compare>
void BSTree<T, Compare>::levelorder_traversal(Node* node, int i) {
	if (!node)
		return;
	if (i == 0) {
		std::cout << node->data_ << " ";
		return;
	}
	levelorder_traversal(node->left_, i - 1);
	levelorder_traversal(node->right_, i - 1);
}

template<typename T, typename Compare>
int BSTree<T, Compare>::high(Node* node) {
	if (!node)
		return 0;
	int left = high(node->left_);
	int right = high(node->right_);
	return left > right ? left + 1 : right + 1;
}

template<typename T, typename Compare>
int BSTree<T, Compare>::number(Node* node) {
	if (!node)
		return 0;
	return number(node->left_) + number(node->right_) + 1;
}

template<typename T, typename Compare>
void BSTree<T, Compare>::findValues(Node* node, std::vector<T>& vec, int i, int j) {
	if (node) {
		if (node->data_ > i) {
			findValues(node->left_, vec, i, j);
		}

		if (i <= node->data_ && node->data_ <= j) {
			vec.emplace_back(node->data_);
		}

		if (node->data_ < j) {
			findValues(node->right_, vec, i, j);
		}
	}
}

template<typename T, typename Compare>
bool BSTree<T, Compare>::isBSTree(Node* node, Node*& pre) {
	if (!node)
		return true;

	if (!isBSTree(node->left_, pre)) {
		return false;
	}

	if (pre) {
		if (!comp_(pre->data_, node->data_)) {
			return false;
		}
	}
	pre = node;

	return isBSTree(node->right_, pre);
}

template<typename T, typename Compare>
bool BSTree<T, Compare>::isChild(Node* father, Node* child) {
	if (!father && !child) {
		return true;
	}

	if (!father) {
		return false;
	}

	if (!child) {
		return true;
	}

	if (father->data_ != child->data_) {
		return false;
	}

	return isChild(father->left_, child->left_) && isChild(father->right_, child->right_);
}

template<typename T, typename Compare>
typename BSTree<T, Compare>::Node* BSTree<T, Compare>::getLCA(Node* node, const T& val1, const T& val2) {
	if (!node) {
		return nullptr;
	}

	if (comp_(node->data_, val1) && comp_(node->data_, val2)) {
		return getLCA(node->right_, val1, val2);
	}
	else if (comp_(val1, node->data_) && comp_(val2, node->data_)) {
		return getLCA(node->left_, val1, val2);
	}
	else {
		return node;
	}
}

template<typename T, typename Compare>
void BSTree<T, Compare>::mirror_reversal(Node* node) {
	if (!node)
		return;

	Node* tmp = node->left_;
	node->left_ = node->right_;
	node->right_ = tmp;

	mirror_reversal(node->left_);
	mirror_reversal(node->right_);
}

template<typename T, typename Compare>
bool BSTree<T, Compare>::mirror(Node* node1, Node* node2) {
	if (!node1 && !node2)
		return true;

	if (!node1 || !node2)
		return false;

	if (node1->data_ != node2->data_)
		return false;
	return mirror(node1->left_, node2->right_) && mirror(node1->right_, node2->left_);
}

template<typename T, typename Compare>
typename BSTree<T, Compare>::Node* BSTree<T, Compare>::reBuild(T pre[], int i, int j, T in[], int m, int n) {
	if (i > j || m > n) {
		return nullptr;
	}

	Node* node = new Node(pre[i]);
	for (int k = m; k <= n; k++) {
		if (pre[i] == in[k]) {
			node->left_ = reBuild(pre, i + 1, i + k - m, in, m, k - 1);
			node->right_ = reBuild(pre, i + k - m + 1, j, in, k + 1, n);
			return node;
		}
	}
	return node;
}

template<typename T, typename Compare>
int BSTree<T, Compare>::isBalance(Node* node, int l, bool& flag) {
	if (!node)
		return l;

	int left = isBalance(node->left_, l + 1, flag);
	if (!flag)
		return left;
	int right = isBalance(node->right_, l + 1, flag);
	if (!flag)
		return right;

	if (abs(left - right) > 1) {
		flag = false;
	}
	return std::max(left, right);
}

template<typename T, typename Compare>
typename BSTree<T, Compare>::Node* BSTree<T, Compare>::getKval(Node* node, int k, int& i) {
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

template<typename T, typename Compare>
void BSTree<T, Compare>::destroy(Node* node) {
	if (!node) return;
	destroy(node->left_);
	destroy(node->right_);
	delete node;
	node = nullptr;
}

void testBST1() {
	int arr[] = { 58,24,67,0,34,62,69,5,41,64,78 };
	BSTree<int> bst;
	for (int v : arr) {
		bst.n_insert(v);
	}

	bst.preorder_traversal();
	bst.inorder_traversal();
	bst.postorder_traversal();
	bst.levelorder_traversal();
	
	std::cout << bst.getKval(11) << std::endl;
}

void testBST2() {
	BSTree<int> bst;
	int pre[] = { 58,24,0,5,34,41,67,62,64,69,78 };
	int in[] = { 0,5,24,34,41,58,62,64,67,69,78 };
	bst.rebuild(pre, 0, 10, in, 0, 10);
	bst.preorder_traversal();
	bst.n_inorder_traversal();
}




//template<typename T, typename Compare>
//bool BSTree<T, Compare>::isBalance(Node* node) {
//	if (!node)
//		return true;
//
//	if (!isBalance(node->left_)) {
//		return false;
//	}
//	if (!isBalance(node->right_)) {
//		return false;
//	}
//
//	int left = high(node->left_);
//	int right = high(node->right_);
//	return abs(left - right) <= 1;
//}