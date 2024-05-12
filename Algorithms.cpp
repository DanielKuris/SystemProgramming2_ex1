#include "Algorithms.hpp"
#include <queue>
#include <vector>
#include <unordered_set>
#include <climits>
#include <limits>
#include <iostream>

using namespace std;

namespace ariel {
    bool Algorithms::negativeCycle(const Graph& graph) {
        auto V = static_cast<std::vector<std::vector<int>>::size_type>(graph.getNumVertices());
        std::vector<std::vector<int>> adjMatrix = graph.getGraph(); // Get the adjacency matrix
        std::vector<int> dist(V, INT_MAX);
        dist[0] = 0;

        // Relax edges V - 1 times
        for (std::vector<std::vector<int>>::size_type i = 0; i < V - 1; i++) {
            for (std::vector<std::vector<int>>::size_type u = 0; u < V; u++) {
                for (std::vector<std::vector<int>>::size_type v = 0; v < V; v++) {
                    if (graph.isEdge(u, v) && dist[u] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v]) {
                        dist[v] = dist[u] + adjMatrix[u][v];
                    }
                }
            }
        }

        // Check for negative cycles
        for (std::vector<std::vector<int>>::size_type u = 0; u < V; u++) {
            for (std::vector<std::vector<int>>::size_type v = 0; v < V; v++) {
                if (graph.isEdge(u, v) && dist[u] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v]) {
                    return true; // Negative cycle found
                }
            }
        }

        return false; // No negative cycle found
    }


    std::string Algorithms::isBipartite(const Graph& graph) {
        auto V = static_cast<std::vector<std::vector<int>>::size_type>(graph.getNumVertices());
        std::vector<int> color(V, -1); // Initialize all vertices with no color
        std::queue<std::vector<std::vector<int>>::size_type> q;
        std::vector<std::vector<int>::size_type> partitionA, partitionB;

        // Start BFS traversal from vertex 0
        q.push(0);
        color[0] = 1; // Assign the first vertex color 1
        partitionA.push_back(0); // Add the first vertex to partition A

        while (!q.empty()) {
            auto u = q.front();
            q.pop();

            // Traverse all adjacent vertices of u
            for (std::vector<std::vector<int>>::size_type v = 0; v < V; v++) {
                if (graph.isEdge(u, v)) {
                    if (color[v] == -1) {
                        color[v] = 1 - color[u]; // Assign opposite color to v
                        q.push(v);
                        // Add v to the corresponding partition
                        if (color[v] == 1) {
                            partitionA.push_back(v);
                        } else {
                            partitionB.push_back(v);
                        }
                    } else if (color[v] == color[u]) {
                        return "The graph isn't bipartite."; // Graph is not bipartite
                    }
                }
            }
        }

        // Construct and return the output string
        std::string output = "The graph is bipartite: A={";
        for (size_t i = 0; i < partitionA.size(); ++i) {
            output += std::to_string(partitionA[i]);
            if (i < partitionA.size() - 1) {
                output += ", ";
            }
        }
        output += "}, B={";
        for (size_t i = 0; i < partitionB.size(); ++i) {
            output += std::to_string(partitionB[i]);
            if (i < partitionB.size() - 1) {
                output += ", ";
            }
        }
        output += "}.";
        return output;
    }


    std::string Algorithms::isContainsCycle(const Graph& graph) {
        auto V = static_cast<std::vector<std::vector<int>>::size_type>(graph.getNumVertices());
        vector<bool> visited(V, false);
        vector<int> parent(V, -1);

        for (std::vector<std::vector<int>>::size_type i = 0; i < V; i++) {
            if (!visited[i] && isContainsCycleUtil(graph, i, visited, parent)) {
                // Construct the cycle path
                std::string path;
                std::vector<std::vector<int>>::size_type cycleStart = static_cast<std::vector<std::vector<int>>::size_type>(-1);
                std::vector<std::vector<int>>::size_type cycleEnd = static_cast<std::vector<std::vector<int>>::size_type>(-1);
                for (std::vector<std::vector<int>>::size_type v = 0; v < V; ++v) {
                    if (visited[v]) {
                        cycleEnd = v;
                        cycleStart = static_cast<std::vector<std::vector<int>>::size_type>(parent[v]);
                        break;
                    }
                }
                while (cycleStart != cycleEnd) {
                    path = std::to_string(cycleEnd) + "->" + path;
                    cycleEnd = static_cast<std::vector<std::vector<int>>::size_type>(parent[cycleEnd]);
                }
                path = std::to_string(cycleStart) + "->" + path;

                return "The graph contains a cycle: " + path;
            }
        }

        return "The graph doesn't contain a cycle";
    }


      bool Algorithms::isContainsCycleUtil(const Graph& graph, std::vector<std::vector<int>>::size_type v, vector<bool>& visited, vector<int>& parent) {
        visited[v] = true;

        auto V = static_cast<std::vector<std::vector<int>>::size_type>(graph.getNumVertices());
        for (std::vector<std::vector<int>>::size_type u = 0; u < V; u++) {
            if (graph.getGraph()[v][u] != 0) {
                if (!visited[u]) {
                    parent[u] = v;
                    if (isContainsCycleUtil(graph, u, visited, parent)) {
                        return true;
                    }
                } else if (u != parent[v]) {
                    return true;
                }
            }
        }

        return false;
    }


    std::string Algorithms::shortestPath(const Graph& graph, std::vector<int>::size_type start, std::vector<int>::size_type end) {
        auto V = static_cast<std::vector<int>::size_type>(graph.getNumVertices()); // Use auto for V

        std::vector<std::vector<int>> adjMatrix = graph.getGraph();
        std::priority_queue<std::pair<int, std::vector<int>::size_type>, std::vector<std::pair<int, std::vector<int>::size_type>>, std::greater<std::pair<int, std::vector<int>::size_type>>> pq;
        std::vector<int> dist(V, INT_MAX);
        std::vector<std::vector<int>::size_type> prev(V, std::numeric_limits<std::vector<int>::size_type>::max());

        dist[start] = 0;

        pq.push(std::make_pair(0, start));

        while (!pq.empty()) {
            std::vector<int>::size_type u = pq.top().second;
            pq.pop();

            for (std::vector<int>::size_type v = 0; v < V; ++v) { // Use auto for v and cast V to unsigned
                if (graph.isEdge(u, v) && dist[u] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjMatrix[u][v];
                    prev[v] = u;
                    pq.push(std::make_pair(dist[v], v));
                }
            }
        }

        // Reconstruct the shortest path if it exists
        if (dist[end] == INT_MAX) {
            return "There is no path between " + std::to_string(start) + " and " + std::to_string(end);
        } else {
            std::vector<std::vector<int>::size_type> pathVertices;
            std::vector<int>::size_type current = end;
            while (current != std::numeric_limits<std::vector<int>::size_type>::max()) {
                pathVertices.push_back(current);
                current = prev[current];
            }
            std::reverse(pathVertices.begin(), pathVertices.end());

            // Convert the vertices to a string with arrow separators
            std::stringstream ss;
            for (size_t i = 0; i < pathVertices.size(); ++i) {
                ss << pathVertices[i];
                if (i < pathVertices.size() - 1) {
                    ss << "->";
                }
            }

            return ss.str();
        }
    }


    bool Algorithms::isConnected(const Graph& graph) {
        auto V = static_cast<std::vector<std::vector<int>>::size_type>(graph.getNumVertices());
        vector<bool> visited(V, false);

        // Start BFS traversal from vertex 0
        queue<std::vector<std::vector<int>>::size_type> q; // Change the queue type
        q.push(0);
        visited[0] = true;

        while (!q.empty()) {
            std::vector<std::vector<int>>::size_type u = q.front(); // Change the type of u
            q.pop();

            // Traverse all adjacent vertices of u
            for (std::vector<std::vector<int>>::size_type v = 0; v < V; v++) { // Change the type of v
                if (graph.isEdge(u, v) && !visited[v]) {
                    q.push(v);
                    visited[v] = true;
                }
            }
        }

        // Check if all vertices are visited
        for (std::vector<std::vector<int>>::size_type i = 0; i < V; i++) { // Change the type of i
            if (!visited[i]) {
                return false; // Graph is not connected
            }
        }

        return true; // Graph is connected
    }

}