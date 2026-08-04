#pragma once
#include<iostream>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>

class BSTREE
{
public:
	BSTREE();
	~BSTREE();

	int high();
	int number();

	void n_insert(const int& val);
	void insert(const int& val);

	void n_remove(const int& val);
	void remove(const int& val);

	bool n_query(const int& val);
	bool query(const int& val);

	void preorder();
	void n_preorder();

	void inorder();
	void n_inorder();

	void postorder();
	void n_postorder();

	void levelorder();
	void n_levelorder();

	void findValues(std::vector<int>& vec, const int& i, const int& j);
	bool isBSTree();
	bool isChild(BSTREE& child);
	int getLCA(const int& val1, const int& val2);
	void mirror_reversal();
	bool mirror();
	void rebuild(int pre[], int i, int j, int in[], int m, int n);
	bool isBalance();
	int getKval(int k);

private:
	struct Node {
		Node(int data)
			:data_(data)
			,left_(nullptr)
			,right_(nullptr)
		{}
		int data_;
		Node* left_;
		Node* right_;
	};

	void destroy(Node *node);
	int high(Node *node);
	int number(Node* node);
	Node* insert(Node* node, const int& val);
	Node* remove(Node* node, const int& val);
	bool query(Node* node, const int& val);
	void preorder(Node* node);
	void inorder(Node* node);
	void postorder(Node* node);
	void levelorder(Node* node, int i);
	void findValues(Node* node, std::vector<int>& vec, const int& i, const int& j);
	bool isBSTree(Node* node, long long lower, long long upper);
	bool isChild(Node* father, Node* child);
	Node* getLCA(Node* node, const int& val1, const int& val2);
	void mirror_reversal(Node* node);
	bool mirror(Node* node1, Node* node2);
	Node* reBuild(int pre[], int i, int j, int in[], int m, int n);
	int isBalance(Node* node, int l, bool& flag);
	Node* getKval(Node* node, int k, int& i);

	Node* root_;
};

