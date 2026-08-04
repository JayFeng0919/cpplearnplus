#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
#include <vector>

// 倒排项
struct InvertTerm {
    InvertTerm(std::string docid, int freqs, int location);

    std::string docid_;            // 文档
    int freqs_;                    // 次数
    std::list<int> locations_;     // 位置
};

// 倒排链表
class InvertList {
public:
    void addTerm(std::string docid, int location);
    const std::list<InvertTerm> &getInvertList() const;

private:
    std::list<InvertTerm> termList_;    // 当前倒排列表所有的倒排项
};

// 倒排索引
class InvertIndex {
public:

private:
    std::list<std::string> fileList_;                       // 所有需要建立倒排的文件
    std::unordered_map<std::string, InvertList> invertMap_; // 词典 + 倒排链表
};