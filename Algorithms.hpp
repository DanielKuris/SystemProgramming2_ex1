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
        static std::string isBipartite(const Graph& graph);
        static std::string isContainsCycle(const Graph& graph);
        static std::string shortestPath(const Graph& graph, std::vector<int>::size_type start, std::vector<int>::size_type end);
        static bool isConnected(const Graph& graph);

    private:
        static bool isContainsCycleUtil(const Graph& graph, std::vector<std::vector<int>>::size_type v, std::vector<bool>& visited, std::vector<int>& parent);
    };
}

#endif // ALGORITHMS_HPP
