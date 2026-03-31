\# cpplearnplus

C++ 数据结构与算法学习仓库，从零实现经典数据结构，附完整源码与使用说明。



\## 📦 项目简介

本项目是个人 C++ 学习过程中的数据结构实现集合，涵盖线性表、树、查找、排序等核心数据结构与算法，所有代码均为手动实现，无第三方依赖，适合学习与参考。



\## ✨ 已实现内容

\### 线性表

\- 单链表 (`list.cpp` / `list.h`)

\- 顺序表/动态数组 (`vector.cpp` / `vector.h`)

\- 栈 (`stack.cpp` / `stack.h`)

\- 队列 (`queue.cpp` / `queue.h`)



\### 树形结构

\- 二叉搜索树 BST (`BST.cpp` / `BST.h` / `BSTREE.cpp` / `BSTREE.h`)

\- AVL 平衡二叉树 (`AVL.cpp` / `AVL.h`)

\- 红黑树 RBTREE (`RBTREE.cpp` / `RBTREE.h`)



\### 查找与排序

\- 二分查找 (`binary\_search.cpp` / `binary\_search.h`)

\- 哈希表 (`hashtable.cpp` / `hashtable.h`)

\- 经典排序算法 (`sort\_algorithm.cpp` / `sort\_algorithm.h`)



\### 其他

\- 大数据处理示例 (`bigdata.cpp` / `bigdata.h`)

\- 主函数入口 (`main.cpp`)



\## 🛠️ 环境要求

\- 编译器：GCC 7+ / Clang 6+ / MSVC 2019+

\- C++ 标准：C++11 及以上

\- 构建工具：CMake 3.10+（可选）



\## 🚀 编译与运行

\### 方法1：使用 CMake（推荐）

```bash

\# 1. 创建构建目录

mkdir build \&\& cd build

\# 2. 生成构建文件

cmake ..

\# 3. 编译

cmake --build .

\# 4. 运行

./cpplearnplus  # Linux/macOS

\# 或 Windows 下运行 build/Debug/cpplearnplus.exe

