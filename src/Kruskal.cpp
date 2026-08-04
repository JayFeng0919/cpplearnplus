#include "Kruskal.h"
#include "DSU.h"
#include <algorithm>

int KruskalMST::buildMST(int vertexCnt, std::vector<Edge> &edges, std::vector<Edge> &mstEdges)
{
    mstEdges.clear();
    std::sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
              { return a.weight_ < b.weight_; });

    DSU_rank dsu(vertexCnt);
    int totalWeight = 0;

    for (const Edge& e: edges) {
        if (dsu.unite(e.start_, e.end_)) {
            totalWeight += e.weight_;
            mstEdges.push_back(e);
            if (mstEdges.size() == vertexCnt - 1) {
                break;
            }
        }
    }

    if (mstEdges.size() != vertexCnt - 1)
        return -1;
    return totalWeight;
}

void testKruskal()
{
    // 顶点：1,2,3,4
    std::vector<Edge> edges{
        Edge(1, 2, 1),
        Edge(1, 3, 4),
        Edge(2, 3, 2),
        Edge(2, 4, 5),
        Edge(3, 4, 1)};
    std::vector<Edge> mst;
    int sum = KruskalMST::buildMST(4, edges, mst);

    if (sum == -1) {
        std::cout << "图不连通，无最小生成树\n";
        return;
    }
    std::cout << "MST总权值: " << sum << "\n";
    std::cout << "MST包含边: \n";
    for (auto &e : mst)
    {
        std::cout << e.start_ << " - " << e.end_ << "  w=" << e.weight_ << "\n";
    }
}
