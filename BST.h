#pragma once
#include<iostream>
#include<functional>
#include<vector>
#include<stack>
#include<queue>
#include<cmath>
#include<algorithm>

template<typename T, typename Compare = std::less<T>>
class BSTree {
public:
	BSTree(Compare comp = Compare());
	~BSTree();
	void n_insert(const T& val);      // 插入
	void insert(const T& val);
	void n_remove(const T& val);      // 删除
	void remove(const T& val);
	bool n_query(const T& val);       // 查询
	bool query(const T& val);
	void preorder_traversal();        // 前序遍历
	void n_preorder_traversal();
	void inorder_traversal();         // 中序遍历
	void n_inorder_traversal();
	void postorder_traversal();       // 后序遍历
	void n_postorder_traversal();
	void levelorder_traversal();      // 层序遍历
	void n_levelorder_traversal();
	int high();                       // 层数
	int number();                     // 节点个数
	void findValues(std::vector<T>& vec, int i, int j);     // 求区间元素值
	bool isBSTree();                                        // 判断BST树（对普通二叉树）
	bool isChild(BSTree<T, Compare>& child);                // 判断子树
	T getLCA(const T& val1, const T& val2);                // 最近公共祖先节点
	void mirror_reversal();                                // 镜像反转
	bool mirror();                                         // 镜像对称（对普通二叉树）
	void rebuild(T pre[], int i, int j, T in[], int m, int n);     // 前序中序重建二叉树
	bool isBalance();                                      // 判断平衡二叉树
	T getKval(int k);                                      // 中序倒数第K个节点(第K大)

private:
	struct Node {
		Node(T data = T())
			:data_(data)
			, left_(nullptr)
			, right_(nullptr)
		{}
		T data_;
		Node* left_;
		Node* right_;
	};

	Node* insert(Node* node, const T& val);
	Node* remove(Node* node, const T& val);
	Node* query(Node* node, const T& val);
	void preorder_traversal(Node* node);
	void inorder_traversal(Node* node);
	void postorder_traversal(Node* node);
	void levelorder_traversal(Node* node, int i);
	int high(Node* node);
	int number(Node* node);
	void findValues(Node* node, std::vector<T>& vec, int i, int j);
	bool isBSTree(Node* node, Node*& pre);
	bool isChild(Node* father, Node* child);
	Node* getLCA(Node* node, const T& val1, const T& val2);
	void mirror_reversal(Node* node);
	bool mirror(Node* node1, Node* node2);
	Node* reBuild(T pre[], int i, int j, T in[], int m, int n);
	int isBalance(Node* node, int l, bool& flag);
	Node* getKval(Node* node, int k, int& i);
	void destroy(Node* node);

	Node* root_;
	Compare comp_;
};


void testBST1();
void testBST2();