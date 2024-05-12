#include "Graph.hpp" // Include the header file containing the class definition

namespace ariel {
    // Constructor
    Graph::Graph() {
        this->numVertices = 0;
        this->numEdges = 0;
   
}


    // Destructor
    Graph::~Graph() {
        // Cleanup if necessary
    }

    // Method to load the graph from a vector of vectors
    void Graph::loadGraph(const vector<vector<int>>& graph) {
        // Assign the graph to the member variable
        this->graph = graph;
        // Calculate number of vertices and edges
        numVertices = graph.size();
        numEdges = calculateNumEdges(graph);
    }

    // Method to print the graph information
    void Graph::printGraph() {
        cout << "Graph with " << numVertices << " vertices and " << numEdges << " edges." << endl;
    }

    // Method to calculate the number of edges in the graph
    int Graph::calculateNumEdges(const vector<vector<int>>& graph) {
        int edges = 0;
        for (const auto& row : graph) {
            for (int val : row) {
                edges += val;
            }
        }
        // Since each edge is counted twice in the adjacency matrix
        return edges / 2;
    }

    vector<vector<int>> Graph::getGraph() const {
        return graph; // Return the adjacency matrix
    }

    int Graph::getNumVertices() const {
        return numVertices; // Return the number of vertices
    }

    int Graph::getNumEdges() const {
        return numEdges; // Return the number of edges
    }

    bool Graph::isEdge(int u, int v) const {
        return graph[u][v] != 0; // Check if there is an edge between u and v
    }

    
}
