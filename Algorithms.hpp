#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <string>
#include <vector>

namespace ariel {
    class Algorithms {
    public:
        static std::string negativeCycle(const Graph& graph);
        static std::string isBipartite(const Graph& graph);
        static std::string isContainsCycle(const Graph& graph);
        static std::string shortestPath(const Graph& graph, std::vector<int>::size_type start, std::vector<int>::size_type end);
        static bool isConnected(const Graph& graph);

    private:
       static bool isContainsCycleUtil(const Graph& graph, std::vector<std::vector<int>>::size_type v, std::vector<bool>& visited, int parent, std::vector<int>& path, std::vector<std::vector<int>>::size_type start);
    };
}

#endif // ALGORITHMS_HPP
