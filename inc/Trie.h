#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <queue>

class Trie {
public:
    Trie();
    ~Trie();

public:
    void add(const std::string &word);
    void remove(const std::string &word);
    int query(const std::string &word);
    void preorder();
    std::vector<std::string> queryPrefix(const std::string &prefix);

private:
    struct TrieNode {
        TrieNode(char ch, int freqs)
            : ch_(ch)
            , freqs_(freqs)
        {}

        char ch_;
        int freqs_;
        std::map<char, TrieNode *> nodeMap_;
    };

private:
    void preorder(TrieNode *root, std::string &word, std::vector<std::string> &wordList);

private:
    TrieNode *root_;
};

void testTrie();
