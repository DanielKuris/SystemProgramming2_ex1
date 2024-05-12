/*
Email: danielkuris6@gmail.com
ID: 214539397
Name: Daniel Kuris
*/
#include "Graph.hpp" // Include the header file containing the class definition
#include <iostream> // Include necessary standard library headers
#include <vector>

namespace ariel {
    // Constructor
    Graph::Graph() {
        this->numVertices = 0;
        this->numEdges = 0;
    }

    // Destructor
    Graph::~Graph() {
        // Destructor implementation
    }
    void Graph::loadGraph(const std::vector<std::vector<int>>& graph) {
        // Check if the graph is empty
        if (graph.empty()) {
            throw std::invalid_argument("Invalid graph: The graph is empty.");
        }

        // Check if the graph is square
        if (graph.size() != graph[0].size()) {
            throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
        }

        // Check if the graph contains non-zero diagonal elements
        for (size_t i = 0; i < graph.size(); ++i) {
            if (graph[i][i] != 0) {
                throw std::invalid_argument("Invalid graph: The graph contains non-zero diagonal elements.");
            }
        }

        // Assign the graph to the member variable
        this->graph = graph;

        // Calculate number of vertices and edges
        numVertices = graph.size();
        numEdges = calculateNumEdges(graph);
    }

    // Method to print the graph information
    void Graph::printGraph() {
        std::cout << "Graph with " << numVertices << " vertices and " << numEdges << " edges." << std::endl;
    }

    // Method to calculate the number of edges in the graph
    int Graph::calculateNumEdges(const std::vector<std::vector<int>>& graph) {
        int edges = 0;
        for (size_t i = 0; i < graph.size(); ++i) {
            for (size_t j = 0; j < graph[i].size(); ++j) {
                // Skip counting diagonal elements (self-loops)
                if (i != j && graph[i][j] != 0) {
                    edges++;
                }
            }
        }
        // Assuming that if an edge exists twice its an indirected graph thus should be counted
        return edges;
    }


    std::vector<std::vector<int>> Graph::getGraph() const {
        return graph; // Return the adjacency matrix
    }

    int Graph::getNumVertices() const {
        return numVertices; // Return the number of vertices
    }

    int Graph::getNumEdges() const {
        return numEdges; // Return the number of edges
    }

    bool Graph::isEdge(std::vector<std::vector<int>>::size_type u, std::vector<std::vector<int>>::size_type v) const {
        return graph[u][v] != 0; // Check if there is an edge between u and v
    }

}