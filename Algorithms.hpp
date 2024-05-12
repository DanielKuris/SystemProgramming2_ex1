#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <string>
#include <queue>
#include <vector>
#include <sstream>
#include <algorithm>

namespace ariel {
    class Algorithms {
    public:
        static bool negativeCycle(const Graph& graph);
        static bool isBipartite(const Graph& graph);
        static bool isContainsCycle(const Graph& graph);
        static std::string shortestPath(const Graph& graph, int start, int end);
        static bool isConnected(const Graph& graph);

    private:
        static bool isContainsCycleUtil(const Graph& graph, std::vector<std::vector<int>>::size_type v, std::vector<bool>& visited, int parent);
    };
}

#endif // ALGORITHMS_HPP
