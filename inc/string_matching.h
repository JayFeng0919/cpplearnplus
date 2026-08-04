#pragma once
#include <iostream>
#include <string>
#include <vector>

int BF(const std::string &s, const std::string &t);     // O(n*m) time complexity, O(1) space complexity
int KMP(const std::string &s, const std::string &t);    // O(n + m) time complexity, O(m) space complexity
void teststring_matching();
