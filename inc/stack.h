#pragma once

class SeqStack {
public:
	SeqStack(int size = 10);
	~SeqStack();
public:
	void push(int val);
	void pop();
	int top() const;
	bool empty() const;
	int size() const;
private:
	void expand(int size);
private:
	int* mpStack;
	int mtop;
	int mcap;
};

class LinkStack {
public:
	LinkStack();
	~LinkStack();
	void push(int val);
	void pop();
	int top() const;
	bool empty() const;
	int size() const;
private:
	struct Node {
		Node(int data = 0)
			:data_(data)
			, next_(nullptr)
		{}
		int data_;
		Node* next_;
	};

	Node* head_;
	int size_;
};

void testSeqStack();
void testLinkStack();

// LeetCode  20  150  232