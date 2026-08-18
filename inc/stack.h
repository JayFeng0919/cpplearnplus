#pragma once

class SeqStack {
public:
    SeqStack(int size = 10);
    SeqStack(const SeqStack &other);
    SeqStack(SeqStack &&other) noexcept;
    ~SeqStack();
    SeqStack &operator=(const SeqStack &other);
    SeqStack &operator=(SeqStack &&other) noexcept;

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
    LinkStack(const LinkStack &other);
    LinkStack(LinkStack &&other) noexcept;
    ~LinkStack();
    LinkStack &operator=(const LinkStack &other);
    LinkStack &operator=(LinkStack &&other) noexcept;

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

    Node* dummy_;
    int size_;
};

void testSeqStack();
void testLinkStack();

// LeetCode  20  150  232
