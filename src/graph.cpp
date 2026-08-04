#include "graph.h"
#include <queue>
#include <algorithm>

Digraph::Digraph() {
    vertexes.emplace_back(""); // 0号占位顶点，无实际意义
}

void Digraph::addVertex(const std::string& data) {
    vertexes.emplace_back(data);
}

void Digraph::addEdge(const int from, const int to) {
    int total = static_cast<int>(vertexes.size()) - 1;
  
    if (from < 1 || from > total || to < 1 || to > total) {
        std::cout << "添加边失败: 顶点编号非法 (" << from << " -> " << to << ")\n";
        return;
    }
    vertexes[from].adjList_.push_back(to);
}

void Digraph::show() const {
    if (vertexes.size() <= 1) {
        std::cout << "图为空\n";
        return;
    }

    for (int i = 1; i < vertexes.size(); i++) {
        std::cout << vertexes[i].data_ << "(" << i << ")" << ": ";
        for (const int& id: vertexes[i].adjList_) {
            std::cout << vertexes[id].data_ << "(" << id << ")" << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Digraph::dfs() const {
    if (vertexes.size() <= 1) {
        std::cout << "图为空, 无法遍历\n";
        return;
    }

    std::vector<uint8_t> visited(vertexes.size(), 0);
    for (int i = 1; i < vertexes.size(); i++) {
        if (!visited[i])
            dfs(i, visited);
    }
    std::cout << "\n";
}

void Digraph::dfs(int start, std::vector<uint8_t> &visited) const {
    if (start < 1 || start >= vertexes.size())
        return;
    if (visited[start])
        return;

    std::cout << vertexes[start].data_ << "(" << start << ")" << " ";
    visited[start] = 1;

    for (const int& id: vertexes[start].adjList_) {
        dfs(id, visited);
    }
}

void Digraph::bfs() const {
    if (vertexes.size() <= 1) {
        std::cout << "图为空，无法遍历\n";
        return;
    }

    std::vector<uint8_t> visited(vertexes.size(), 0);
    for (int i = 1; i < vertexes.size(); i++) {
        if (visited[i])
            continue;
        std::queue<int> q;
        q.push(i);
        visited[i] = 1;

        while (!q.empty()) {
            int cur_id = q.front();
            q.pop();
            std::cout << vertexes[cur_id].data_ << "(" << cur_id << ")" << " ";

            for (const int& id: vertexes[cur_id].adjList_) {
                if (id < 1 || id >= vertexes.size())
                    continue;
                if (!visited[id]) {
                    q.push(id);
                    visited[id] = 1;
                }
            }
        }
    }
    std::cout << "\n";
}

void Digraph::bfsShortestPath(int start, int end) const {
    const int maxVtx = static_cast<int>(vertexes.size()) - 1;
    if (start < 1 || start > maxVtx || end < 1 || end > maxVtx) {
        std::cout << "错误: 起点/终点编号越界, 有效范围1~" << maxVtx << "\n";
        return;
    }
    if (start == end) {
        std::cout << "最短路径: " << vertexes[start].data_ << "\n";
        return;
    }

    std::vector<int> prev(vertexes.size(), 0);
    std::vector<uint8_t> visited(vertexes.size(), 0);
    std::queue<int> q;

    q.push(start);
    visited[start] = 1;
    bool found = false;

    while (!q.empty() && !found) {
        int cur_id = q.front();
        q.pop();

        for (const int &id : vertexes[cur_id].adjList_) {
            if (id < 1 || id > maxVtx)
                continue;
            if (visited[id])
                continue;

            q.push(id);
            visited[id] = 1;
            prev[id] = cur_id;

            if (id == end) {
                found = true;
                break;
            }
        }
    }

    if (found) {
        std::vector<int> reversePath;
        int cur = end;
        while (cur) {
            reversePath.push_back(cur);
            cur = prev[cur];
        }

        std::cout << "最短路径: ";
        for (size_t i = reversePath.size() - 1; i > 0; --i) {
            std::cout << vertexes[reversePath[i]].data_ << "(" << reversePath[i] << ")" << " -> ";
        }
        std::cout << vertexes[reversePath[0]].data_ << "(" << reversePath[0] << ")" << "\n";
    }
    else {
        std::cout << "不存在有效路径\n";
    }
}

void testDigraph() {
    Digraph g;
    // 1. 添加4个顶点，编号自动为 1、2、3、4
    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    g.addVertex("D");

    // 2. 添加有向边
    g.addEdge(1, 2);  // A -> B
    g.addEdge(1, 3);  // A -> C
    g.addEdge(2, 4);  // B -> D
    g.addEdge(3, 4);  // C -> D

    // 3. 打印邻接表
    std::cout << "=== 邻接表 ===" << "\n";
    g.show();

    // 4. 深度优先遍历
    std::cout << "=== DFS ===" << "\n";
    g.dfs();

    // 5. 广度优先遍历
    std::cout << "=== BFS ===" << "\n";
    g.bfs();

    // 6. bfs无权最短路径
    g.bfsShortestPath(1, 4);
}



WeightedGraph::WeightedGraph() {
    vertexes.emplace_back("");
}

void WeightedGraph::addVertex(const std::string &data) {
    vertexes.emplace_back(data);
}

void WeightedGraph::addEdge(const int from, const int to, const int weight) {
    int total = static_cast<int>(vertexes.size()) - 1;

    if (from < 1 || from > total || to < 1 || to > total) {
        std::cout << "添加边失败: 顶点编号非法 (" << from << " -- " << to << ")\n";
        return;
    }
    if (weight < 0) {
        std::cout << "警告: 存在负权边(" << from << "--" << to << "," << weight<< "), Dijkstra算法结果可能错误\n";
    }
    vertexes[from].adjList_.emplace_back(to, weight);
    vertexes[to].adjList_.emplace_back(from, weight);
}

void WeightedGraph::show() const {
    if (vertexes.size() <= 1) {
        std::cout << "图为空\n";
        return;
    }

    for (int i = 1; i < vertexes.size(); i++) {
        std::cout << vertexes[i].data_ << ": ";
        for (const Edge& e: vertexes[i].adjList_) {
            std::cout << vertexes[e.to_].data_ << "(" << e.weight_ << ")";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void WeightedGraph::dfs() const {
    if (vertexes.size() <= 1) {
        std::cout << "图为空, 无法遍历\n";
        return;
    }

    std::vector<uint8_t> visited(vertexes.size(), 0);
    for (int i = 1; i < vertexes.size(); i++) {
        if (visited[i])
            continue;
        dfs(i, visited);
    }
    std::cout << "\n";
}

void WeightedGraph::dfs(int start, std::vector<uint8_t> &visited) const {
    if (start < 1 || start >= vertexes.size())
        return;
    if (visited[start])
        return;

    std::cout << vertexes[start].data_ << "(" << start << ")" << " ";
    visited[start] = 1;

    for (const Edge& e: vertexes[start].adjList_) {
        dfs(e.to_, visited);
    }
}

void WeightedGraph::bfs() const {
    if (vertexes.size() <= 1) {
        std::cout << "图为空，无法遍历\n";
        return;
    }

    std::vector<uint8_t> visited(vertexes.size(), 0);
    for (int i = 1; i < vertexes.size(); i++) {
        if (visited[i])
            continue;
        std::queue<int> q;
        q.push(i);
        visited[i] = 1;

        while(!q.empty()) {
            int cur_id = q.front();
            q.pop();
            std::cout << vertexes[cur_id].data_ << "(" << cur_id << ")" << " ";

            for (const Edge& e: vertexes[cur_id].adjList_) {
                if (e.to_ < 1 || e.to_ >= vertexes.size())
                    continue;
                if(!visited[e.to_]) {
                    q.push(e.to_);
                    visited[e.to_] = 1;
                }
            }
        }
    }
    std::cout << "\n";
}

std::vector<int> WeightedGraph::dijkstra(int start) const {
    int total = static_cast<int>(vertexes.size()) - 1;
    if (start < 1 || start > total) {
        std::cout << "起点编号非法\n";
        return {};
    }

    // 距离数组：初始化为无穷大，起点距离为0
    std::vector<int> dist(vertexes.size(), INT_MAX);
    dist[start] = 0;

    // 最小堆：pair<距离, 顶点编号>，默认大顶堆，加greater变最小堆
    using P = std::pair<int, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u])
            continue;

        for (const Edge& e: vertexes[u].adjList_) {
            int v = e.to_;
            int w = e.weight_;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }
    }
    return dist;
}

void WeightedGraph::printShortestPath(int start, int end) const {
    int total = static_cast<int>(vertexes.size()) - 1;
    if (start < 1 || start > total || end < 1 || end > total) {
        std::cout << "顶点编号非法\n";
        return;
    }

    std::vector<int> dist(vertexes.size(), INT_MAX);
    std::vector<int> prev(vertexes.size(), 0);
    dist[start] = 0;

    using P = std::pair<int, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u])
            continue;

        for (const Edge& e: vertexes[u].adjList_) {
            int v = e.to_;
            int w = e.weight_;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.emplace(dist[v], v);
            }
        }
    }

    if (dist[end] == INT_MAX) {
        std::cout << vertexes[start].data_ << " 无法到达 " << vertexes[end].data_ << "\n";
        return;
    }

    // 回溯路径
    std::vector<int> path;
    for (int cur = end; cur != 0; cur = prev[cur]) {
        path.push_back(cur);
    }
    std::reverse(path.begin(), path.end());

    // 打印
    for (size_t i = 0; i < path.size(); i++) {
        if (i > 0)
            std::cout << " -> ";
        std::cout << vertexes[path[i]].data_;
    }
    std::cout << "\n总距离: " << dist[end] << "\n\n";
}

std::vector<std::vector<int>> WeightedGraph::floyd() const {
    int total = static_cast<int>(vertexes.size());
    const int INF = 1e9;
    std::vector<std::vector<int>> dist(total, std::vector<int>(total, INF));

    for (int i = 1; i < total; i++) {
        dist[i][i] = 0;
    }
    for (int u = 1; u < total; u++) {
        for (const Edge& e: vertexes[u].adjList_) {
            int v = e.to_;
            dist[u][v] = e.weight_;
            dist[v][u] = e.weight_;
        }
    }

    for (int k = 1; k < total; k++) {
        for (int i = 1; i < total; i++) {
            for (int j = 1; j < total; j++) {
                dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    return dist;
}

void testWeightedGraph() {
    WeightedGraph g;
    // 添加5个顶点
    g.addVertex("A"); // 1
    g.addVertex("B"); // 2
    g.addVertex("C"); // 3
    g.addVertex("D"); // 4
    g.addVertex("E"); // 5

    // 添加无向带权边
    g.addEdge(1, 2, 6);  // A-B 权6
    g.addEdge(1, 3, 2);  // A-C 权2
    g.addEdge(2, 3, 3);  // B-C 权3
    g.addEdge(2, 4, 5);  // B-D 权5
    g.addEdge(3, 4, 4);  // C-D 权4
    g.addEdge(3, 5, 10); // C-E 权10
    g.addEdge(4, 5, 1);  // D-E 权1

    std::cout << "=== 带权无向图邻接表 ===\n";
    g.show();

    std::cout << "=== A到E的最短路径 ===\n";
    g.printShortestPath(1, 2);
    g.printShortestPath(1, 3);
    g.printShortestPath(1, 4);
    g.printShortestPath(1, 5);

    std::vector<std::vector<int>> dist = g.floyd();
    for (int i = 1; i < dist.size(); i++) {
        for (int j = 1; j < dist[i].size(); j++) {
            std::cout << dist[i][j] << " ";
        }
        std::cout << "\n";
    }
}
