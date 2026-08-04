#pragma once
#include <iostream>
#include <vector>

class DSU_size {
private:
    std::vector<int> parent_;
    std::vector<int> size_;

public:
    explicit DSU_size(int maxNode); // 禁止隐式类型转换

    int find(int x);               // 查找根结点(路径压缩)
    bool unite(int x, int y);      // 合并集合
    bool isConnected(int x, int y);
    int getBlockSize(int x);
};

void testDSU_size();



class DSU_rank {
private:
    std::vector<int> parent_;
    std::vector<int> rank_;

public:
    explicit DSU_rank(int maxNode); // 禁止隐式类型转换

    int find(int x);          // 查找根结点(路径压缩)
    bool unite(int x, int y); // 合并集合
    bool isConnected(int x, int y);
};
