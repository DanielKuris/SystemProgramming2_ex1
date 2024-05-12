/*
Email: danielkuris6@gmail.com
ID: 214539397
Name: Daniel Kuris
*/
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

namespace ariel {

    class Graph {
    public:
        // Constructor and Destructor
        Graph();
        ~Graph();

        // Method to load the graph from a vector of vectors
        void loadGraph(const std::vector<std::vector<int>>& graph);

        // Method to print the graph information
        void printGraph();

        // Method to calculate the number of edges in the graph
        int calculateNumEdges(const std::vector<std::vector<int>>& graph);

        // Getter methods
        std::vector<std::vector<int>> getGraph() const;
        int getNumVertices() const;
        int getNumEdges() const;

        // Method to check if there is an edge between vertices u and v
        bool isEdge(std::vector<std::vector<int>>::size_type u, std::vector<std::vector<int>>::size_type v) const;

    private:
        // Private member variables
        std::vector<std::vector<int>> graph;
        int numVertices;
        int numEdges;
    };

}

#endif /* GRAPH_HPP */
