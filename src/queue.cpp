#include<iostream>
#include"queue.h"

CircleQueue::CircleQueue(int size)
    : cap_(size)
    , front_(0)
    , rear_(0)
{
    pQue_ = new int[cap_];
}

CircleQueue::CircleQueue(const CircleQueue& other)
    : cap_(other.cap_)
    , front_(other.front_)
    , rear_(other.rear_)
{
    pQue_ = new int[cap_];
    for (int i = 0; i < size(); i++) {
        pQue_[(front_ + i) % cap_] = other.pQue_[(other.front_ + i) % other.cap_];
    }
}

CircleQueue::CircleQueue(CircleQueue &&other) noexcept
    : pQue_(other.pQue_)
    , cap_(other.cap_)
    , front_(other.front_)
    , rear_(other.rear_)
{
    other.pQue_ = nullptr;
    other.cap_ = 0;
    other.front_ = 0;
    other.rear_ = 0;
}

CircleQueue::~CircleQueue() {
    delete[] pQue_;
    pQue_ = nullptr;
}

CircleQueue& CircleQueue::operator=(const CircleQueue& other) {
    if (this != &other) {
        delete[] pQue_;
        cap_ = other.cap_;
        front_ = other.front_;
        rear_ = other.rear_;
        pQue_ = new int[cap_];
        for (int i = 0; i < size(); i++) {
            pQue_[(front_ + i) % cap_] = other.pQue_[(other.front_ + i) % other.cap_];
        }
    }
    return *this;
}

CircleQueue &CircleQueue::operator=(CircleQueue &&other) noexcept
{
    if (this == &other)
        return *this;
    delete[] pQue_;
    pQue_ = other.pQue_;
    cap_ = other.cap_;
    front_ = other.front_;
    rear_ = other.rear_;
    other.pQue_ = nullptr;
    other.cap_ = 0;
    other.front_ = 0;
    other.rear_ = 0;
    return *this;
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
    delete[] pQue_;
    pQue_ = p;
    cap_ = size;
    front_ = 0;
    rear_ = i;
}



LinkQueue::LinkQueue() :size_(0) {
    dummy_ = new Node();
    dummy_->next_ = dummy_;
    dummy_->prev_ = dummy_;
}

LinkQueue::LinkQueue(const LinkQueue &other)
    : size_(other.size_)
{
    dummy_ = new Node();
    dummy_->next_ = dummy_;
    dummy_->prev_ = dummy_;
    Node *p = other.dummy_->next_;
    while (p != other.dummy_) {
        push(p->data_);
        p = p->next_;
    }
}

LinkQueue::LinkQueue(LinkQueue &&other) noexcept
    : dummy_(other.dummy_)
    , size_(other.size_)
{
    other.dummy_ = nullptr;
    other.size_ = 0;
}

LinkQueue::~LinkQueue() {
    Node* p = dummy_->next_;
    while (p != dummy_) {
        Node* temp = p;
        p = p->next_;
        delete temp;
    }
    delete dummy_;
    dummy_ = nullptr;
}

LinkQueue& LinkQueue::operator=(const LinkQueue &other) {
    if (this != &other) {
        Node* p = dummy_->next_;
        while (p != dummy_) {
            Node* temp = p;
            p = p->next_;
            delete temp;
        }
        size_ = other.size_;
        dummy_->next_ = dummy_;
        dummy_->prev_ = dummy_;
        p = other.dummy_->next_;
        while (p != other.dummy_) {
            push(p->data_);
            p = p->next_;
        }
    }
    return *this;
}

LinkQueue &LinkQueue::operator=(LinkQueue &&other) noexcept
{
    if (this == &other)
        return *this;
    Node *p = dummy_->next_;
    while (p != dummy_) {
        Node *temp = p;
        p = p->next_;
        delete temp;
    }
    delete dummy_;
    dummy_ = other.dummy_;
    size_ = other.size_;
    other.dummy_ = nullptr;
    other.size_ = 0;
    return *this;
}

void LinkQueue::push(int val) {
    Node* node = new Node(val);
    node->next_ = dummy_;
    node->prev_ = dummy_->prev_;
    dummy_->prev_->next_ = node;
    dummy_->prev_ = node;
    size_++;
}

void LinkQueue::pop() {
    if (dummy_->next_ == dummy_)
        return;
    Node* p = dummy_->next_;
    p->next_->prev_ = dummy_;
    dummy_->next_ = p->next_;
    delete p;
    p = nullptr;
    size_--;
}

int LinkQueue::front() const {
    if (dummy_->next_ == dummy_)
        throw "queue is empty!";
    return dummy_->next_->data_;
}

int LinkQueue::back() const {
    if (dummy_->next_ == dummy_)
        throw "queue is empty!";
    return dummy_->prev_->data_;
}

bool LinkQueue::empty() const {
    return dummy_->next_ == dummy_;
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
