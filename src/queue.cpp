#include<iostream>
#include"queue.h"

CircleQueue::CircleQueue(int size)
	:cap_(size)
	, front_(0)
	, rear_(0)
{
	pQue_ = new int[cap_];
}

CircleQueue::~CircleQueue() {
	delete[]pQue_;
	pQue_ = nullptr;
}

void CircleQueue::push(int val) {
	if ((rear_ + 1) % cap_ == front_) {
		expand(2 * cap_);
	}
	pQue_[rear_] = val;
	rear_ = (rear_ + 1) % cap_;
}

void CircleQueue::pop() {
	if (front_ == rear_)
		return;
	front_ = (front_ + 1) % cap_;
}

int CircleQueue::front() const {
	if (front_ == rear_)
		throw "queue is empty!";
	return pQue_[front_];
}

int CircleQueue::back() const {
	if (front_ == rear_)
		throw "queue is empty!";
	return pQue_[(rear_ - 1 + cap_) % cap_];
}

bool CircleQueue::empty() const {
	return front_ == rear_;
}

int CircleQueue::size() const {
	return (rear_ - front_ + cap_) % cap_;
}

void CircleQueue::expand(int size) {
	int* p = new int[size];
	int i = 0;
	int j = front_;
	for (; j != rear_ && i < size; i++, j = (j + 1) % cap_) {
		p[i] = pQue_[j];
	}
	delete[]pQue_;
	pQue_ = p;
	cap_ = size;
	front_ = 0;
	rear_ = i;
}

LinkQueue::LinkQueue() :size_(0) {
	head_ = new Node();
	head_->next_ = head_;
	head_->prev_ = head_;
}

LinkQueue::~LinkQueue() {
	Node* p = head_->next_;
	while (p != head_) {
		Node* temp = p;
		p = p->next_;
		delete temp;
	}
	delete head_;
	head_ = nullptr;
}

void LinkQueue::push(int val) {
	Node* node = new Node(val);
	node->next_ = head_;
	node->prev_ = head_->prev_;
	head_->prev_->next_ = node;
	head_->prev_ = node;
	size_++;
}

void LinkQueue::pop() {
	if (head_->next_ == head_)
		return;
	Node* p = head_->next_;
	p->next_->prev_ = head_;
	head_->next_ = p->next_;
	delete p;
	p = nullptr;
	size_--;
}

int LinkQueue::front() const {
	if (head_->next_ == head_)
		throw "queue is empty!";
	return head_->next_->data_;
}

int LinkQueue::back() const {
	if (head_->next_ == head_)
		throw "queue is empty!";
	return head_->prev_->data_;
}

bool LinkQueue::empty() const {
	return head_->next_ == head_;
}

int LinkQueue::size() const {
	return size_;
}

void testCircleQueue() {
	CircleQueue q;
	int arr[] = { 10,20,30,40,50,60,70,80 };
	for (int val : arr) {
		q.push(val);
	}
	std::cout << q.front() << std::endl;
	std::cout << q.back() << std::endl;
	q.push(100);
	q.push(200);
	q.push(300);
	std::cout << q.front() << std::endl;
	std::cout << q.back() << std::endl;
	while (!q.empty()) {
		std::cout << q.front() << " ";
		std::cout << q.back() << std::endl;
		q.pop();
	}
}

void testLinkQueue() {
	LinkQueue q;
	int arr[] = { 10,20,30,40,50,60,70,80 };
	for (int val : arr) {
		q.push(val);
	}
	std::cout << q.front() << std::endl;
	std::cout << q.back() << std::endl;
	q.push(100);
	q.push(200);
	q.push(300);
	std::cout << q.front() << std::endl;
	std::cout << q.back() << std::endl;
	while (!q.empty()) {
		std::cout << q.front() << " ";
		std::cout << q.back() << std::endl;
		q.pop();
	}
}