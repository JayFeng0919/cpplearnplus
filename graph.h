#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdint>

/* ------------------------------  无权有向图  ----------------------------- */
class Digraph {
public:
    Digraph();

    void addVertex(const std::string &data); // 添加顶点，编号自动从1开始递增
    void addEdge(const int from, const int to);          // 添加有向边 from -> to
    void show() const;
    void dfs() const;
    void bfs() const;
    void bfsShortestPath(int start, int end) const;

private:
    void dfs(int start, std::vector<uint8_t> &visited) const;

private:
    /*  顶点  */
    struct Vertex {
        Vertex(std::string data)
            : data_(std::move(data))
        {}

        std::string data_;              // 顶点信息
        std::list<int> adjList_;        // 邻接链表
    };

private:
    std::vector<Vertex> vertexes;       // 邻接表结构
};

void testDigraph();



/* ------------------------------  有权无向图  ----------------------------- */
class WeightedGraph {
public:
    WeightedGraph();

    void addVertex(const std::string &data);
    void addEdge(const int from, const int to, const int weight);
    void show() const;
    void dfs() const;
    void bfs() const;

    std::vector<int> dijkstra(int start) const;
    void printShortestPath(int start, int end) const;

    std::vector<std::vector<int>> floyd() const;

private:
    void dfs(int start, std::vector<uint8_t> &visited) const;

private:
    struct Edge {
        Edge(int to, int weight)
            : to_(to)
            , weight_(weight)
        {}
        int to_;
        int weight_;
    };

    struct Vertex {
        Vertex(std::string data)
            : data_(std::move(data))
        {}
        std::string data_;
        std::vector<Edge> adjList_;
    };

private:
    std::vector<Vertex> vertexes;
};

void testWeightedGraph();