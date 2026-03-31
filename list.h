#pragma once

namespace singly {
	struct Node {
		Node(int data = 0):data_(data),next_(nullptr){}
		int data_;
		Node* next_;
	};

	class Clink {
		friend void ReverseLink(Clink& link);
		friend bool GetLastKNode(Clink& link, int k, int& val);
		friend bool hasCircle(Clink& link, int& val);
		friend bool IsLinkHasMerge(Clink& link1, Clink& link2, int& val);
	public:
		Clink();
		~Clink();
		void push_back(int val);
		void push_front(int val);
		void remove(int val);
		void removeAll(int val);
		bool find(int val) const;
		void show() const;
	private:
		Node* dummy_;
	};

	class CircleLink {
	public:
		CircleLink();
		~CircleLink();
		void push_back(int val);
		void push_front(int val);
		void remove(int val);
		bool find(int val) const;
		void show() const;
	private:
		Node* head_;
		Node* tail_;
	};

	void testClink();
	void testCircleLink();
	void ReverseLink(Clink& link);
	bool GetLastKNode(Clink& link, int k, int& val);
	bool hasCircle(Clink& link, int& val);
	bool IsLinkHasMerge(Clink& link1, Clink& link2, int& val);
}

namespace doubly {
	struct Node {
		Node(int data = 0)
			: data_(data)
			, prev_(nullptr)
			, next_(nullptr)
		{}
		int data_;
		Node* prev_;
		Node* next_;
	};

	class DoubleLink {
	public:
		DoubleLink();
		~DoubleLink();
		void push_back(int val);
		void push_front(int val);
		void show() const;
		void remove(int val);
		bool find(int val) const;
	private:
		Node* head_;
	};

	void testDoubleLink();
}

// LeetCode 21 141 142  160  61  19