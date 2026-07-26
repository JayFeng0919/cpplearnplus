#include "skiplist.h"

SkipList::SkipList() {
    dummy_ = new DummyNode(1);
}

SkipList::~SkipList() {
    while (dummy_) {
        Node* cur = dummy_->next_;
        while (cur) {
            Node* next = cur->next_;
            delete cur;
            cur = next;
        }

        DummyNode* nextDummy = static_cast<DummyNode*>(dummy_->down_);
        delete dummy_;
        dummy_ = nextDummy;
    }
}

int SkipList::getLevel() const {
    static bool seed_init = false;
    if (!seed_init) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seed_init = true;
    }

    int level = 1;
    while (level < 16 && std::rand() % 2) {
        ++level;
    }
    return level;
}

bool SkipList::find(int data) const {
    Node* cur = dummy_;
    while (cur) {
        while (cur->next_ && cur->next_->data_ < data) {
            cur = cur->next_;
        }

        if (cur->next_ && cur->next_->data_ == data) {
            return true;
        }

        cur = cur->down_;
    }
    return false;
}

void SkipList::insert(int data) {
    if (find(data)) return;

    int level = getLevel();
    if (level > dummy_->level_) {
        for (int i = dummy_->level_ + 1; i <= level; ++i) {
            DummyNode *newDummy = new DummyNode(i);
            newDummy->down_ = dummy_;
            dummy_ = newDummy;
        }
    }

    std::vector<Node*> update(dummy_->level_, nullptr);
    Node *cur = dummy_;
    for (int i = dummy_->level_ - 1; i >= 0; --i) {
        while (cur->next_ && cur->next_->data_ < data) {
            cur = cur->next_;
        }
        update[i] = cur;
        cur = cur->down_;
    }

    std::vector<Node*> newNodes(level, nullptr);
    for (int i = 0; i < level; ++i) {
        newNodes[i] = new Node(data);
        if (i > 0) {
            newNodes[i]->down_ = newNodes[i - 1];
        }
    }

    for (int i = 0; i < level; ++i) {
        newNodes[i]->next_ = update[i]->next_;
        update[i]->next_ = newNodes[i];
    }
}

void SkipList::remove(int data) {
    std::vector<Node*> update(dummy_->level_, nullptr);
    std::vector<Node*> match(dummy_->level_, nullptr);
    Node* cur = dummy_;

    for (int i = dummy_->level_ - 1; i >= 0; --i) {
        while (cur->next_ && cur->next_->data_ < data) {
            cur = cur->next_;
        }
        update[i] = cur;
        if (cur->next_ && cur->next_->data_ == data) {
            match[i] = cur->next_;
        }
        cur = cur->down_;
    }

    if (!match[0]) return;

    std::vector<Node*> del_list;
    for (int i = 0; i < match.size(); ++i) {
        if (match[i]) {
            update[i]->next_ = match[i]->next_;
            del_list.push_back(match[i]);
        }
    }

    for (Node* p : del_list) {
        delete p;
    }

    while (dummy_ && dummy_->next_ == nullptr && dummy_->down_) {
        DummyNode *old = dummy_;
        dummy_ = static_cast<DummyNode*>(dummy_->down_);
        delete old;
    }
}

void SkipList::show() const {
    Node *layer = dummy_;
    while (layer) {
        Node *cur = layer->next_;
        while (cur) {
            std::cout << cur->data_ << " ";
            cur = cur->next_;
        }
        std::cout << "\n";
        layer = layer->down_;
    }
    std::cout << "\n";
}

void testSkipList() {
    SkipList sl;
    for (int i = 0; i < 30; ++i) {
        sl.insert(std::rand() % 100);
    }
    sl.show();
    sl.insert(50);
    sl.show();
    std::cout << "Find 50: " << (sl.find(50) ? "Found" : "Not Found") << std::endl;
    sl.remove(50);
    sl.show();
    std::cout << "Find 50: " << (sl.find(50) ? "Found" : "Not Found") << std::endl;
}