#pragma once
#include<iostream>
#include<vector>

// 快速排序
class QuickSort{
private:
    int partition(std::vector<int> &vec, int l, int r);
public:
    void quickSort(std::vector<int> &vec);
    void quickSort(std::vector<int> &vec, int left, int right);
    void test();
};

// 快速选择求解top k问题
class QuickSelect {
private:
    int partition(std::vector<int>& vec, int l, int r);
public:
    int min_topk(std::vector<int>& vec, int k);
    int min_topk(std::vector<int>& vec, int k, int l, int r);
    int max_topk(std::vector<int>& vec, int k);
    int max_topk(std::vector<int>& vec, int k, int l, int r);
    void test_min_topk();
    void test_max_topk();
};

// 归并排序
class MergeSort {
private:
    void merge(std::vector<int>& vec, int l, int mid, int r);
public:
    void mergesort(std::vector<int>& vec);
    void mergesort(std::vector<int>& vec, int l, int r);
    void test();
};

// 合并K个有序链表  LeetCode 23
class MergeKSortedLists {
private:
    struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(nullptr) {}
    };
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2);
    ListNode *mergeKLists(std::vector<ListNode *> &lists, int l, int r);
    ListNode *mergeKLists(std::vector<ListNode *> &lists);
};
