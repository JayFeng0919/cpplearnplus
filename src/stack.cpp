#include<iostream>
#include"stack.h"

SeqStack::SeqStack(int size)
    : mtop(0)
    , mcap(size)
{
    mpStack = new int[mcap];
}

SeqStack::SeqStack(const SeqStack& other)
    : mcap(other.mcap)
    , mtop(other.mtop)
{
    mpStack = new int[other.mcap];
    memcpy(mpStack, other.mpStack, sizeof(int) * other.mtop);
}

SeqStack::~SeqStack() {
    delete[] mpStack;
    mpStack = nullptr;
}

SeqStack& SeqStack::operator=(const SeqStack &other) {
    if (this == &other)
        return *this;
    delete[] mpStack;
    mcap = other.mcap;
    mtop = other.mtop;
    mpStack = new int[mcap];
    memcpy(mpStack, other.mpStack, sizeof(int) * other.mtop);
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
    delete[] mpStack;
    mpStack = p;
    mcap = size;
}



LinkStack::LinkStack():size_(0) {
    dummy_ = new Node();
}

LinkStack::LinkStack(const LinkStack& other) {
    dummy_ = new Node();
    Node *cur = dummy_;
    Node *p = other.dummy_->next_;
    while (p) {
        cur->next_ = new Node(p->data_);
        p = p->next_;
        cur = cur->next_;
    }
}

LinkStack::~LinkStack() {
    Node* p = dummy_;
    while (p) {
        dummy_ = dummy_->next_;
        delete p;
        p = dummy_;
    }
}

LinkStack& LinkStack::operator= (const LinkStack& other) {
    if (this == &other)
        return *this;

    Node *p = dummy_;
    while (p) {
        dummy_ = dummy_->next_;
        delete p;
        p = dummy_;
    }

    dummy_ = new Node();
    Node *cur = dummy_;
    p = other.dummy_->next_;
    while (p) {
        cur->next_ = new Node(p->data_);
        p = p->next_;
        cur = cur->next_;
    }
    return *this;
}

void LinkStack::push(int val) {               // O(1)
    Node* node = new Node(val);
    node->next_ = dummy_->next_;
    dummy_->next_ = node;
    size_++;
}

void LinkStack::pop() {
    if (!dummy_->next_) {               // O(1)
        return;
    }
    Node* p = dummy_->next_;
    dummy_->next_ = p->next_;
    delete p;
    p = nullptr;
    size_--;
}

int LinkStack::top() const {
    if (!dummy_->next_) {
        throw "stack is empty!";
    }
    return dummy_->next_->data_;
}

bool LinkStack::empty() const {
    return dummy_->next_ == nullptr;
}

int LinkStack::size() const {
    return size_;
}

void testSeqStack() {
    int arr[] = {1, 2, 3, 4, 5};
    SeqStack s;
    for (int val : arr) {
        s.push(val);
    }
    std::cout << s.empty() << '\n';
    std::cout << s.top() << '\n';
    s.pop();
    std::cout << s.top() << '\n';
    std::cout << s.size() << '\n';
}

void testLinkStack() {
    LinkStack s;
    int arr[] = {1, 2, 3, 4, 5, 6};
    for (int val : arr) {
        s.push(val);
    }
    std::cout << s.size() << '\n';
    while (!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << '\n';
}
