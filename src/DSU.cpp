#include "DSU.h"

DSU_size::DSU_size(int maxNode)
{
    parent_.resize(maxNode + 1);
    size_.resize(maxNode + 1, 1);
    for (int i = 1; i <= maxNode; i++) {
        parent_[i] = i;
    }
}

int DSU_size::find(int x)
{
    if (x != parent_[x]) {
        parent_[x] = find(parent_[x]);
    }
    return parent_[x];
}

bool DSU_size::unite(int x, int y)
{
    int rx = find(x);
    int ry = find(y);
    if (rx == ry) {
        return false;           // 已经连通,无需合并
    }

    // 小集合并入大集合
    if (size_[rx] < size_[ry]) {
        parent_[rx] = ry;
        size_[ry] += size_[rx];
    }
    else {
        parent_[ry] = rx;
        size_[rx] += size_[ry];
    }
    return true;
}

bool DSU_size::isConnected(int x, int y)
{
    return find(x) == find(y);
}

int DSU_size::getBlockSize(int x)
{
    return size_[find(x)];
}

void testDSU_size()
{
    DSU_size dsu(5);
    std::cout << "1,2 是否连通：" << (dsu.isConnected(1, 2) ? "是" : "否") << "\n";

    dsu.unite(1, 2);
    dsu.unite(2, 3);
    std::cout << "1,3 是否连通: " << (dsu.isConnected(1, 3) ? "是" : "否") << "\n";
    std::cout << "1所在连通块大小: " << dsu.getBlockSize(1) << "\n";

    dsu.unite(4, 5);
    std::cout << "4所在连通块大小: " << dsu.getBlockSize(4) << "\n";
    std::cout << "1,4 是否连通: " << (dsu.isConnected(1, 4) ? "是" : "否") << "\n";

    dsu.unite(3, 5);
    std::cout << "1,5 是否连通: " << (dsu.isConnected(1, 5) ? "是" : "否") << "\n";
    std::cout << "1所在连通块总大小: " << dsu.getBlockSize(1) << "\n";

    // 重复合并测试（已经连通，返回false）
    bool ret = dsu.unite(1, 5);
    std::cout << "重复合并1和5, 执行结果: " << (ret ? "进行合并" : "已连通，无需合并") << "\n";
}


DSU_rank::DSU_rank(int maxNode)
{
    parent_.resize(maxNode + 1);
    rank_.resize(maxNode + 1, 0);
    for (int i = 1; i <= maxNode; i++) {
        parent_[i] = i;
    }
}

int DSU_rank::find(int x)
{
    if (x != parent_[x]) {
        parent_[x] = find(parent_[x]);
    }
    return parent_[x];
}

bool DSU_rank::unite(int x, int y)
{
    int rx = find(x);
    int ry = find(y);
    if (rx == ry)
        return false;
    
    if (rank_[rx] < rank_[ry]) {
        parent_[rx] = ry;
    }
    else {
        parent_[ry] = rx;
        if (rank_[rx] == rank_[ry]) {
            rank_[rx]++;
        }
        return true;
    }
}

bool DSU_rank::isConnected(int x, int y)
{
    return find(x) == find(y);
}