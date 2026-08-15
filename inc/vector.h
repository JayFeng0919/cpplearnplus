#pragma once

class Array {
public:
    Array(int size = 10);
    Array(const Array &other);
    ~Array();
    Array &operator=(const Array &other);

    void push_back(int val);
    void pop_back();
    void insert(int pos, int val);
    void erase(int pos);
    int find(int val) const;
    void show() const;

private:
    void expand(int size);

private:
    int* mpArr;
    int mCap;
    int mCur;
};

void testvector();
