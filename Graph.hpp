#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <stdexcept>
#include <string>

namespace ariel {

    class Graph {
    private:
        std::vector<std::vector<int>> graph; // Adjacency matrix representation of the graph
        size_t numVertices; // Number of vertices in the graph
        int numEdges; // Number of edges in the graph

        // Helper method to calculate the number of edges in the graph
        int calculateNumEdges(const std::vector<std::vector<int>>& graph) const;

        // Member function to check if the current graph is valid
        bool validGraph() const;

        // Helper method to check if the current graph is fully contained within another graph
        bool isContainedIn(const Graph& graph1, const Graph& graph2) const;

    public:
        // Constructor
        Graph();

        // Destructor
        ~Graph();

        // Load graph from adjacency matrix
        void loadGraph(const std::vector<std::vector<int>>& graph);

        // Print graph information
        void printGraph();

        // Getters
        std::vector<std::vector<int>> getGraph() const;
        int getNumVertices() const;
        int getNumEdges() const;

        // Check if there is an edge between two vertices
        bool isEdge(std::vector<std::vector<int>>::size_type u, std::vector<std::vector<int>>::size_type v) const;

        // Operator +
        Graph operator+(const Graph& other) const;

        // Operator -
        Graph operator-(const Graph& other) const;

        // Operator +=
        Graph& operator+=(const Graph& other);

        // Operator -=
        Graph& operator-=(const Graph& other);

        // Unary Operator -
        Graph operator-() const;

        // Operator ++
        Graph& operator++();

        // Operator --
        Graph& operator--();

        // Operator *
        Graph& operator*(int scalar);

        // Operator *
        Graph operator*(const Graph& other) const;

        // Operator <
        bool operator<(const Graph& other) const;

        // Operator >
        bool operator>(const Graph& other) const;

        // Operator ==
        bool operator==(const Graph& other) const;

        // Operator !=
        bool operator!=(const Graph& other) const;
        
        // Operator <=
        bool operator<=(const Graph& other) const;

        // Operator >=
        bool operator>=(const Graph& other) const;

        // Visual representation of the graph
        void visualGraph() const;
    };

} // namespace ariel

#endif /* GRAPH_HPP */
