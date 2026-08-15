#pragma once

class CircleQueue {
public:
    CircleQueue(int size = 10);
    CircleQueue(const CircleQueue &other);
    ~CircleQueue();
    CircleQueue &operator=(const CircleQueue &other);

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
    LinkQueue(const LinkQueue& other);
    ~LinkQueue();
    LinkQueue &operator=(const LinkQueue &other);

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

    Node* dummy_;
    int size_;
};

void testCircleQueue();
void testLinkQueue();

// LeetCode  232
