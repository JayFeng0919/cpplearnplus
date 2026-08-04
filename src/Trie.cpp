#include "Trie.h"

Trie::Trie() {
    root_ = new TrieNode('\0', 0);
}

Trie::~Trie() {
    std::queue<TrieNode *> que;
    que.push(root_);

    while (!que.empty()) {
        TrieNode *front = que.front();
        que.pop();
        for (auto &pair : front->nodeMap_) {
            que.push(pair.second);
        }
        delete front;
    }
}

void Trie::add(const std::string &word) {
    if (word.empty())
        return;

    TrieNode *cur = root_;
    for (const char& c: word) {
        auto childIt = cur->nodeMap_.find(c);
        if (childIt == cur->nodeMap_.end()) {
            TrieNode *child = new TrieNode(c, 0);
            cur->nodeMap_.emplace(c, child);
            cur = child;
        }
        else {
            cur = childIt->second;
        }
    }
    cur->freqs_++;
}

void Trie::remove(const std::string &word) {
    if (word.empty())
        return;

    TrieNode *cur = root_;
    TrieNode *del = root_;
    char delch = word[0];

    for (int i = 0; i < word.size(); i++) {
        auto childIt = cur->nodeMap_.find(word[i]);
        if (childIt == cur->nodeMap_.end()) {
            return;
        }
        if (cur->freqs_ || cur->nodeMap_.size() > 1) {
            del = cur;
            delch = word[i];
        }
        cur = childIt->second;
    }

    // 单词存在
    if (cur->nodeMap_.empty()) {
        TrieNode *child = del->nodeMap_[delch];
        del->nodeMap_.erase(delch);
        
        std::queue<TrieNode *> que;
        que.push(child);

        while (!que.empty()) {
            TrieNode *front = que.front();
            que.pop();
            for (auto &pair : front->nodeMap_) {
                que.push(pair.second);
            }
            delete front;
        }
    }
    else {
        cur->freqs_ = 0;
    }
}

int Trie::query(const std::string &word) {
    if (word.empty())
        return 0;

    TrieNode *cur = root_;
    for (const char& c: word) {
        auto childIt = cur->nodeMap_.find(c);
        if (childIt == cur->nodeMap_.end()) {
            return 0;
        }
        cur = childIt->second;
    }
    return cur->freqs_;
}

void Trie::preorder() {
    std::string word = "";
    std::vector<std::string> wordList;
    preorder(root_, word, wordList);
    for (const std::string& word: wordList) {
        std::cout << word << "\n";
    }
    std::cout << "\n";
}

void Trie::preorder(TrieNode *cur, std::string& word, std::vector<std::string> &wordList) {
    if (cur != root_) {
        word.push_back(cur->ch_);
        if (cur->freqs_ > 0) {
            wordList.emplace_back(word);
        }
    }
    for (const auto& pair: cur->nodeMap_) {
        preorder(pair.second, word, wordList);
    }
}

std::vector<std::string> Trie::queryPrefix(const std::string &prefix) {
    TrieNode *cur = root_;
    for (const char& c: prefix) {
        auto childIt = cur->nodeMap_.find(c);
        if (childIt != cur->nodeMap_.end()) {
            cur = childIt->second;
        }
        else {
            return {};
        }
    }

    std::vector<std::string> wordList;
    std::string base = "";
    if (!prefix.empty()) {
        base = prefix.substr(0, prefix.size() - 1);
    }
    preorder(cur, base, wordList);
    return wordList;
}

void testTrie() {
    Trie t;
    t.add("hello");
    t.add("hello");
    t.add("helloo");
    t.add("hel");
    t.add("hel");
    t.add("hel");
    t.add("china");
    t.add("ch");
    t.add("ch");
    t.add("heword");
    t.add("hellw");

    std::cout << t.query("hello") << "\n";
    std::cout << t.query("helloo") << "\n";
    std::cout << t.query("hel") << "\n";
    std::cout << t.query("china") << "\n";
    std::cout << t.query("ch") << "\n";

    t.preorder();
    std::vector<std::string> words = t.queryPrefix("ch");
    for (auto& word: words) {
        std::cout << word << "\n";
    }
    std::cout << "\n";
}
