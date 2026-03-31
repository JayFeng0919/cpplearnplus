#include<iostream>
#include"stack.h"

SeqStack::SeqStack(int size)
	:mtop(0)
	, mcap(size)
{
	mpStack = new int[mcap];
}

SeqStack::~SeqStack() {
	delete[]mpStack;
	mpStack = nullptr;
}

void SeqStack::push(int val) {
	if (mtop == mcap)
		expand(2 * mcap);
	mpStack[mtop++] = val;
}

void SeqStack::pop() {
	if (mtop == 0)
		return;
	mtop--;
}

int SeqStack::top() const {
	if (mtop == 0)
		throw "stack is empty";
	return mpStack[mtop - 1];
}

bool SeqStack::empty() const {
	return mtop == 0;
}

int SeqStack::size() const {
	return mtop;
}

void SeqStack::expand(int size) {
	int* p = new int[size];
	memcpy(p, mpStack, sizeof(int) * mtop);
	delete[]mpStack;
	mpStack = p;
	mcap = size;
}

LinkStack::LinkStack():size_(0) {
	head_ = new Node();
}

LinkStack::~LinkStack() {
	Node* p = head_;
	while (p) {
		head_ = head_->next_;
		delete p;
		p = head_;
	}
}

void LinkStack::push(int val) {               // O(1)
	Node* node = new Node(val);
	node->next_ = head_->next_;
	head_->next_ = node;
	size_++;
}

void LinkStack::pop() {
	if (!head_->next_) {               // O(1)
		return;
	}
	Node* p = head_->next_;
	head_->next_ = p->next_;
	delete p;
	p = nullptr;
	size_--;
}

int LinkStack::top() const {
	if (!head_->next_) {
		throw "stack is empty!";
	}
	return head_->next_->data_;
}

bool LinkStack::empty() const {
	return head_->next_ == nullptr;
}

int LinkStack::size() const {
	return size_;
}

void testSeqStack() {
	int arr[] = { 1,2,3,4,5 };
	SeqStack s;
	for (int val : arr) {
		s.push(val);
	}
	std::cout << s.empty() << std::endl;
	std::cout << s.top() << std::endl;
	s.pop();
	std::cout << s.top() << std::endl;
	std::cout << s.size() << std::endl;
}
void testLinkStack() {
	LinkStack s;
	int arr[] = { 1,2,3,4,5,6 };
	for (int val : arr) {
		s.push(val);
	}
	std::cout << s.size() << std::endl;
	while (!s.empty()) {
		std::cout << s.top() << " ";
		s.pop();
	}
	std::cout << std::endl;
}