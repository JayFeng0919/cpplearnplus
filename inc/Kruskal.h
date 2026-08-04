#pragma once
#include <iostream>
#include <vector>

struct Edge {
    int start_;
    int end_;
    int weight_;

    Edge(int start, int end, int weight)
        : start_(start)
        , end_(end)
        , weight_(weight)
    {}
};

class KruskalMST {
public:
    /// @brief Kruskal求最小生成树
    /// @param vertexCnt 顶点总数（有效顶点1~vertexCnt）
    /// @param edges 所有边集合
    /// @param mstEdges [输出]存入构成MST的边
    /// @return MST总权值；无法构成生成树返回-1
    static int buildMST(int vertexCnt, std::vector<Edge> &edges, std::vector<Edge> &mstEdges);
};

void testKruskal();
