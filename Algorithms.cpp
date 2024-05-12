#include "Algorithms.hpp"
#include <queue>
#include <vector>
#include <unordered_set>
#include <climits>
#include <limits>

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

    bool Algorithms::isBipartite(const Graph& graph) {
    auto V = static_cast<std::vector<std::vector<int>>::size_type>(graph.getNumVertices());
    std::vector<int> color(V, -1); // Initialize all vertices with no color
    std::queue<std::vector<std::vector<int>>::size_type> q;

    // Start BFS traversal from vertex 0
    q.push(0);
    color[0] = 1; // Assign the first vertex color 1

    while (!q.empty()) {
        auto u = q.front();
        q.pop();

        // Traverse all adjacent vertices of u
        for (std::vector<std::vector<int>>::size_type v = 0; v < V; v++) {
            if (graph.isEdge(u, v) && color[v] == -1) {
                color[v] = 1 - color[u]; // Assign opposite color to v
                q.push(v);
            } else if (graph.isEdge(u, v) && color[v] == color[u]) {
                return false; // Graph is not bipartite
            }
        }
    }

    return true; // Graph is bipartite
    }



    bool Algorithms::isContainsCycle(const Graph& graph) {
    auto V = static_cast<std::vector<std::vector<int>>::size_type>(graph.getNumVertices());
    vector<bool> visited(V, false);

    for (std::vector<std::vector<int>>::size_type i = 0; i < V; i++) {
        if (!visited[i] && isContainsCycleUtil(graph, i, visited, -1)) {
            return true; // Cycle found
        }
    }

    return false; // No cycle found
    }

    bool Algorithms::isContainsCycleUtil(const Graph& graph, std::vector<std::vector<int>>::size_type v, vector<bool>& visited, int parent) {
        visited[v] = true;

        auto V = static_cast<std::vector<std::vector<int>>::size_type>(graph.getNumVertices());
        for (std::vector<std::vector<int>>::size_type u = 0; u < V; u++) {
            if (graph.getGraph()[v][u] != 0) {
                if (!visited[u]) {
                    if (isContainsCycleUtil(graph, u, visited, v)) {
                        return true;
                    }
                } else if (u != parent) {
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

        std::stringstream ss;
        std::vector<int>::size_type current = end;
        while (current != -1) {
            ss << current;
            if (prev[current] != -1) {
                ss << "->";
            }
            current = prev[current];
        }

        return ss.str();
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


