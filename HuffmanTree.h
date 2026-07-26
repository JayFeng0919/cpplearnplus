#pragma once
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

class HuffmanTree {
public:
    HuffmanTree();
    ~HuffmanTree();

public:
    void init(const std::string &str);
    void showHuffmanCode();
    std::string encode(const std::string &str);    // 字符串转编码
    std::string decode(const std::string &str);    // 编码转字符串

private : 
    struct TreeNode {
        TreeNode(char data, unsigned int weight)
            : data_(data)
            , weight_(weight)
            , left_(nullptr)
            , right_(nullptr)
        {}

        char data_;
        unsigned int weight_;
        TreeNode *left_;
        TreeNode *right_;
    };

private:
    void destroy(TreeNode* root);
    void create(const std::string &str);                      // 创建哈夫曼树
    void getHuffmanCode();                                    // 获取哈夫曼编码
    void getHuffmanCode(TreeNode *root, std::string &code);

private:
    using MinHeap = std::priority_queue<TreeNode *, std::vector<TreeNode *>, std::function<bool(TreeNode *, TreeNode *)>>;
    TreeNode *root_;
    std::unordered_map<char, std::string> codeMap_;
    MinHeap minHeap_;
};

void testHuffmanTree();