#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <vector>

namespace ariel {

    class Algorithms {
    public:
        // Function declarations
        static bool negativeCycle(const Graph& graph);
        static bool isBipartite(const Graph& graph);
        static bool isContainsCycle(const Graph& graph);
        static std::vector<int> shortestPath(const Graph& graph, int start, int end);
        static bool isConnected(const Graph& graph);

    private:
        // Private helper functions if any
        static bool isContainsCycleUtil(const Graph& graph, int v, std::vector<bool>& visited, int parent);
    };

}

#endif /* ALGORITHMS_HPP */
