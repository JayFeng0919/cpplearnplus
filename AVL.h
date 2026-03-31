#pragma once
#include<iostream>
#include<algorithm>

class AVL{
public:
	AVL():root_(nullptr){}
	~AVL() { destroy(root_); }

	void insert(const int& val);
	void remove(const int& val);

private:
	struct Node {
		Node(int data)
			:data_(data)
			,left_(nullptr)
			,right_(nullptr)
			,height_(1)
		{}
		int data_;
		Node* left_;
		Node* right_;
		int height_;
	};

	void destroy(Node* node);
	int height(Node* node);
	Node* LL(Node* node);
	Node* RR(Node* node);
	Node* LR(Node* node);
	Node* RL(Node* node);

	Node* insert(Node* node, const int& val);
	Node* remove(Node* node, const int& val);

	Node* root_;
};

void testAVL();