#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

class SkipList {
public:
    SkipList();
    ~SkipList();

public:
    bool find(int data) const;
    void insert(int data);
    void remove(int data);
    void show() const;

private:
    int getLevel() const;

private:
    struct Node {
        Node(int data)
            : data_(data)
            , next_(nullptr)
            , down_(nullptr)
        {}
        virtual ~Node() = default;

        int data_;
        Node* next_;
        Node* down_;
    };

    struct DummyNode : public Node {
        DummyNode(int level)
            : Node(INT_MIN)
            , level_(level)
        {}

        int level_;
    };

private:
    DummyNode* dummy_;
};

void testSkipList();