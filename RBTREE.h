#include<iostream>

enum Color { RED, BLACK };

// root是黑色  nullptr是黑色  红不连续  从任一节点到其每个叶子节点的所有路径都包含相同数目的黑色节点
class RBTree {
public:
	RBTree() : root_(nullptr) {}
	~RBTree() { destroy(root_); }

	void insert(const int& val);
	void remove(const int& val);

private:
	struct Node {
		Node(int data)
			: data_(data)
			, left_(nullptr)
			, right_(nullptr)
			, parent_(nullptr)
			, color_(RED)
		{}
		int data_;
		Node* left_;
		Node* right_;
		Node* parent_;
		Color color_;
	};

	void destroy(Node* node);
	void leftRotate(Node* x);
	void rightRotate(Node* x);
	void insertFixup(Node* node);
	void removeFixup(Node* node, Node* parent, bool isLeft);

	Node* insert(Node* root, Node* node);
	Node* remove(Node* root, const int& val);
	Node* minimum(Node* node);
	void transplant(Node* u, Node* v);

	Node* root_;
};

void testRBTree();