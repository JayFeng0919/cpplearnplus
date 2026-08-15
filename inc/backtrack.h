#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<cstdint>

// 子集  LeetCode 78
class Subsets{
private:
    void backtrack(std::vector<std::vector<int>> &res, std::vector<int> &path, std::vector<int> &nums, int start);
public:    
    std::vector<std::vector<int>> subsets(std::vector<int> &nums);
    void test();
};

// 组合  LeetCode 77
class Combine{
private:
    void backtrack(std::vector<std::vector<int>> &res, std::vector<int> &path, int n, int k, int start, int length);
public:    
    std::vector<std::vector<int>> combine(int n, int k);
    void test();
};


// 全排列  LeetCode 46
class Permute{
private:
    void backtrack(std::vector<std::vector<int>> &res, std::vector<int> &path,
                   std::vector<uint8_t> &used, std::vector<int> &nums, int length);
public:    
    std::vector<std::vector<int>> permute(std::vector<int> &nums);
    void test();
};
