#include "HuffmanTree.h"

HuffmanTree::HuffmanTree()
    : root_(nullptr)
    , minHeap_([](TreeNode *n1, TreeNode *n2) -> bool
                               { return n1->weight_ > n2->weight_; })
{
}

HuffmanTree::~HuffmanTree() {
    destroy(root_);
}

void HuffmanTree::destroy(TreeNode *root) {
    if (!root)
        return;
    destroy(root->left_);
    destroy(root->right_);
    delete root;
}

void HuffmanTree::create(const std::string &str) {
    destroy(root_);
    root_ = nullptr;
    codeMap_.clear();
    while (!minHeap_.empty())
        minHeap_.pop();

    if (str.empty())
        return;

    std::unordered_map<char, unsigned int> dataMap;
    for (const char& ch: str) {
        dataMap[ch]++;
    }
    for (auto& [ch, cnt]: dataMap) {
        minHeap_.push(new TreeNode(ch, cnt));
    }

    while (minHeap_.size() > 1) {
        TreeNode *n1 = minHeap_.top();
        minHeap_.pop();
        TreeNode *n2 = minHeap_.top();
        minHeap_.pop();

        TreeNode *node = new TreeNode('\0', n1->weight_ + n2->weight_);
        node->left_ = n1;
        node->right_ = n2;

        minHeap_.push(node);
    }
    root_ = minHeap_.top();
    minHeap_.pop();
}

void HuffmanTree::getHuffmanCode() {
    codeMap_.clear();
    if (!root_)
        return;
    
    /* 处理只有单字符建树的情况, 这时根结点就是唯一节点 */
    if (!root_->left_ && !root_->right_) {
        codeMap_[root_->data_] = "0";
        return;
    }
    std::string code = "";
    getHuffmanCode(root_, code);
}

void HuffmanTree::getHuffmanCode(TreeNode *root, std::string &code) {
    if (!root->left_ && !root->right_) {
        codeMap_[root->data_] = code;
        return;
    }

    code.push_back('0');
    getHuffmanCode(root->left_, code);
    code.pop_back();

    code.push_back('1');
    getHuffmanCode(root->right_, code);
    code.pop_back();
}

void HuffmanTree::showHuffmanCode() {
    for (const auto& [ch, str]: codeMap_) {
        std::cout << ch << ": " << str << "\n";
    }
    std::cout << "\n";
}

void HuffmanTree::init(const std::string& str) {
    create(str);
    getHuffmanCode();
    showHuffmanCode();
}

std::string HuffmanTree::encode(const std::string &str) {
    std::string encode_str = "";
    for (const char &ch : str) {
        auto it = codeMap_.find(ch);
        if (it == codeMap_.end()) {
            std::cout << "错误: 存在建树时未出现的字符\n";
            return "";
        }
        encode_str.append(it->second);
    }
    return encode_str;
}

std::string HuffmanTree::decode(const std::string &str) {
    if (!root_) {
        std::cout << "错误: 哈夫曼树尚未构建, 请先调用create()\n";
        return "";
    }

    std::string decode_str = "";
    TreeNode *cur = root_;
    for (const char& ch: str) {
        if (ch != '0' && ch != '1') {
            std::cout << "错误: 存在非0/1字符\n";
            return "";
        }
        cur = ch == '0' ? cur->left_ : cur->right_;
        if (!cur->left_ && !cur->right_) {
            decode_str += cur->data_;
            cur = root_;
        }
    }

    if (cur != root_) {
        std::cout << "错误: 二进制码不完整\n";
        return "";
    }

    return decode_str;
}

void testHuffmanTree() {
    std::string str = "ABACDAE";
    HuffmanTree htree;
    htree.init(str);
    std::cout << htree.encode("ADBCAR") << "\n";
    std::cout << htree.decode(htree.encode("ADBCA")) << "\n";
}