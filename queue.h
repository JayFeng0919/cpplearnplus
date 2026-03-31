#pragma once

class CircleQueue {
public:
	CircleQueue(int size = 10);
	~CircleQueue();
public:
	void push(int val);
	void pop();
	int front() const;
	int back() const;
	bool empty() const;
	int size() const;
private:
	void expand(int size);
private:
	int* pQue_;
	int cap_;
	int front_;
	int rear_;
};

class LinkQueue {
public:
	LinkQueue();
	~LinkQueue();
public:
	void push(int val);
	void pop();
	int front() const;
	int back() const;
	bool empty() const;
	int size() const;
private:
	struct Node {
		Node(int data = 0)
			:data_(data)
			, next_(nullptr)
			, prev_(nullptr)
		{}
		int data_;
		Node* next_;
		Node* prev_;
	};

	Node* head_;
	int size_;
};

void testCircleQueue();
void testLinkQueue();

// LeetCode  232