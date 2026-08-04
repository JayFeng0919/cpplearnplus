#include<iostream>
#include<stdlib.h>
#include<time.h>
#include"vector.h"

Array::Array(int size)
	:mCap(size)
	, mCur(0)
{
	mpArr = new int[mCap];
}

Array::~Array() {
	delete[]mpArr;
	mpArr = nullptr;
}

void Array::push_back(int val) {
	if (mCur == mCap)
		expand(2 * mCap);
	mpArr[mCur++] = val;
}

void Array::pop_back() {
	if (mCur == 0)
		return;
	mCur--;
}

void Array::insert(int pos, int val) {
	if (pos<0 || pos>mCur)
		return;
	if (mCur == mCap)
		expand(2 * mCap);
	for (int i = mCur - 1; i >= pos; --i)
		mpArr[i + 1] = mpArr[i];
	mpArr[pos] = val;
	mCur++;
}

void Array::erase(int pos) {
	if (pos < 0 || pos >= mCur)
		return;
	for (int i = pos; i < mCur - 1; ++i)
		mpArr[i] = mpArr[i + 1];
	mCur--;
}

int Array::find(int val) const {
	for (int i = 0; i < mCur; i++) {
		if (mpArr[i] == val)
			return i;
	}
	return -1;
}

void Array::show() const {
	for (int i = 0; i < mCur; i++) {
		std::cout << mpArr[i] << " ";
	}
	std::cout << std::endl;
}

void Array::expand(int size) {
	int* p = new int[size];
	memcpy(p, mpArr, sizeof(int) * mCap);
	delete[]mpArr;
	mpArr = p;
	mCap = size;
}

void testvector() {
	Array arr;
	srand(time(0));
	for (int i = 0; i < 10; i++) {
		arr.push_back(rand() % 100);
	}
	arr.show();
	arr.pop_back();
	arr.show();
	arr.insert(0, 100);
	arr.show();
	arr.insert(10, 200);
	arr.show();
	int pos = arr.find(100);
	if (pos != -1) {
		arr.erase(pos);
		arr.show();
	}
}
