#include "string_matching.h"

int BF(const std::string &s, const std::string &t) {
    int i = 0, j = 0;
    while (i < s.size() && j < t.size()) {
        if (s[i] == t[j]) {
            i++;
            j++;
        }
        else {
            i = i - j + 1;
            j = 0;
        }
    }
    return j == t.size() ? i - j : -1;
}

int KMP(const std::string &s, const std::string &t) {
    int m = s.size(), n = t.size();
    std::vector<int> next(n, 0);
    for (int i = 1, j = 0; i < n; i++) {
        while (j > 0 && t[i] != t[j]) {
            j = next[j - 1];
        }
        if (t[i] == t[j]) {
            j++;
        }
        next[i] = j;
    }
    for (int i = 0, j = 0; i < m; i++) {
        while (j > 0 && s[i] != t[j]) {
            j = next[j - 1];
        }
        if (s[i] == t[j]) {
            j++;
        }
        if (j == n) {
            return i - n + 1;
        }
    }
    return -1;
}

void teststring_matching() {
    std::string s = "ababcabcacbab";
    std::string t = "abcac";
    int index1 = BF(s, t);
    int index2 = KMP(s, t);
    if (index1 != -1) {
        std::cout << "Pattern found at index: " << index1 << "\n";
    }
    if (index2 != -1) {
        std::cout << "Pattern found at index: " << index2 << "\n";
    }
    else {
        std::cout << "Pattern not found." << "\n";
    }
}
