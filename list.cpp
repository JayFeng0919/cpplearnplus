#include<iostream>
#include<stdlib.h>
#include<time.h>
#include"list.h"

namespace singly {
	Clink::Clink() {
		dummy_ = new Node();
	}

	Clink::~Clink() {
		Node* p = dummy_;
		while (p) {
			dummy_ = dummy_->next_;
			delete p;
			p = dummy_;
		}
		dummy_ = nullptr;
	}

	void Clink::push_back(int val) {        // O(n)
		Node* p = dummy_;
		while (p->next_)
			p = p->next_;
		Node* node = new Node(val);
		p->next_ = node;
	}

	void Clink::push_front(int val) {     // O(1)
		Node* node = new Node(val);
		node->next_ = dummy_->next_;
		dummy_->next_ = node;
	}

	void Clink::remove(int val) {
		Node* p = dummy_->next_;
		Node* q = dummy_;

		while (p) {
			if (p->data_ != val) {
				q = p;
				p = p->next_;
			}
			else {
				q->next_ = p->next_;
				delete p;
				return;
			}
		}
	}

	void Clink::removeAll(int val) {
		Node* p = dummy_->next_;
		Node* q = dummy_;
		while (p) {
			if (p->data_ != val) {
				q = p;
				p = p->next_;
			}
			else {
				q->next_ = p->next_;
				delete p;
				p = q->next_;
			}
		}
	}

	bool Clink::find(int val) const {
		Node* p = dummy_->next_;
		while (p) {
			if (p->data_ != val)
				p = p->next_;
			else
				return true;
		}
		return false;
	}

	void Clink::show() const {
		Node* p = dummy_->next_;
		while (p) {
			std::cout << p->data_ << " ";
			p = p->next_;
		}
		std::cout << std::endl;
	}

	CircleLink::CircleLink() {
		head_ = new Node();
		tail_ = head_;
		head_->next_ = head_;
	}

	CircleLink::~CircleLink() {
		Node* p = head_->next_;
		while (p != head_) {
			head_->next_ = p->next_;
			delete p;
			p = head_->next_;
		}
		delete head_;
		head_ = nullptr;
		tail_ = nullptr;
	}

	void CircleLink::push_back(int val) {           // O(1)
		Node* node = new Node(val);
		node->next_ = head_;
		tail_->next_ = node;
		tail_ = node;
	}

	void CircleLink::push_front(int val) {
		Node* node = new Node(val);
		node->next_ = head_->next_;
		head_->next_ = node;
		if (head_ == tail_)
			tail_ = node;
	}

	void CircleLink::remove(int val) {
		Node* p = head_->next_;
		Node* q = head_;
		while (p != head_) {
			if (p->data_ == val) {
				q->next_ = p->next_;
				if (p == tail_)
					tail_ = q;
				delete p;
				p = nullptr;
				return;
			}
			p = p->next_;
			q = q->next_;
		}
	}

	bool CircleLink::find(int val) const {
		Node* p = head_->next_;
		while (p != head_) {
			if (p->data_ == val)
				return true;
			p = p->next_;
		}
		return false;
	}

	void CircleLink::show() const {
		Node* p = head_->next_;
		while (p != head_) {
			std::cout << p->data_ << " ";
			p = p->next_;
		}
		std::cout << std::endl;
	}

	void testClink() {
		Clink link;
		srand(time(0));
		for (int i = 0; i < 10; i++) {
			int val = rand() % 100;
			link.push_front(val);
			std::cout << val << " ";
		}
		std::cout << std::endl;
		link.push_back(200);
		link.show();
		link.remove(200);
		link.show();
		link.push_back(23);
		link.push_front(23);
		link.show();
		link.removeAll(23);
		link.show();
		ReverseLink(link);
		link.show();
	}

	void testCircleLink() {
		CircleLink clink;
		clink.push_back(10);
		clink.push_back(20);
		clink.push_back(30);
		clink.push_front(40);
		clink.push_back(30);
		clink.show();
		clink.remove(30);
		clink.show();
		std::cout << clink.find(50) << std::endl;
		std::cout << clink.find(20) << std::endl;
	}

	void ReverseLink(Clink& link) {
		Node* dummy = link.dummy_;
		Node* p = link.dummy_->next_;
		if (p == nullptr) {
			return;
		}

		dummy->next_ = nullptr;
		while (p) {
			Node* q = p->next_;
			p->next_ = dummy->next_;
			dummy->next_ = p;
			p = q;
		}
	}

	bool GetLastKNode(Clink& link, int k, int& val) {
		Node* dummy = link.dummy_;
		Node* p = dummy;
		Node* prev = dummy;
		if (k < 1) { return false; }
		for (int i = 0; i < k; ++i) {
			p = p->next_;
			if (p == nullptr) {
				return false;
			}
		}

		while (p) {
			p = p->next_;
			prev = prev->next_;
		}
		val = prev->data_;
		return true;
	}

	bool hasCircle(Clink& link, int& val) {
		Node* dummy = link.dummy_;
		Node* fast = dummy;
		Node* slow = dummy;
		while (fast && fast->next_) {
			fast = fast->next_->next_;
			slow = slow->next_;
			if (slow == fast) {
				fast = dummy;
				while (fast != slow) {
					fast = fast->next_;
					slow = slow->next_;
				}
				val = slow->data_;
				return true;
			}
		}
		return false;
	}

	bool IsLinkHasMerge(Clink& link1, Clink& link2, int& val) {
		if (link1.dummy_->next_ == nullptr || link2.dummy_->next_ == nullptr)
			return false;
		Node* p = link1.dummy_->next_;
		Node* q = link2.dummy_->next_;
		while (p != q) {
			p = p == nullptr ? link2.dummy_->next_ : p->next_;
			q = q == nullptr ? link1.dummy_->next_ : q->next_;
		}
		if (p) {
			val = p->data_;
			return true;
		}
		else
			return false;
	}
}

namespace doubly {
	DoubleLink::DoubleLink() {
		head_ = new Node();
	}

	DoubleLink::~DoubleLink() {
		Node* p = head_;
		while (p) {
			head_ = head_->next_;
			delete p;
			p = head_;
		}
	}

	void DoubleLink::push_back(int val) {
		Node* p = head_;
		Node* node = new Node(val);
		while (p->next_) {
			p = p->next_;
		}
		p->next_ = node;
		node->prev_ = p;
	}

	void DoubleLink::push_front(int val) {
		Node* node = new Node(val);
		if (head_->next_) {
			head_->next_->prev_ = node;
		}
		node->next_ = head_->next_;
		node->prev_ = head_;
		head_->next_ = node;
	}

	void DoubleLink::show() const {
		Node* p = head_->next_;
		while (p) {
			std::cout << p->data_ << " ";
			p = p->next_;
		}
		std::cout << std::endl;
	}

	void DoubleLink::remove(int val) {
		Node* p = head_->next_;
		while (p) {
			if (p->data_ == val) {
				p->prev_->next_ = p->next_;
				if (p->next_) {
					p->next_->prev_ = p->prev_;
				}
				delete p;
				p = nullptr;
				return;
			}
			p = p->next_;
		}
	}

	bool DoubleLink::find(int val) const {
		Node* p = head_->next_;
		while (p) {
			if (p->data_ == val)
				return true;
			p = p->next_;
		}
		return false;
	}

	void testDoubleLink() {
		DoubleLink dlink;
		dlink.push_back(20);
		dlink.push_back(30);
		dlink.push_back(40);
		dlink.push_front(10);
		dlink.show();
		dlink.remove(100);
		dlink.show();
		dlink.remove(20);
		dlink.show();
	}
}