#include "Graph.hpp"
#include <iostream>
#include <stdexcept>

namespace ariel {
    // Constructor
    Graph::Graph() : numVertices(0), numEdges(0) {}

    // Destructor
    Graph::~Graph() {}

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

    void Graph::printGraph() {
        std::cout << "Graph with " << numVertices << " vertices and " << numEdges << " edges." << std::endl;
    }

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
        // Assuming that if an edge exists twice, it's an undirected graph and should be counted
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

    // --------------------------------------------------------------

    //PART B - OPERATORS

    // Member function to check if the current graph is valid
    bool Graph::validGraph() const {
        // Check if the graph is empty
        if (this->graph.empty()) {
            throw std::invalid_argument("Invalid graph: The graph is empty.");
            return false;
        }

        // Check if the graph is square
        if (this->graph.size() != this->graph[0].size()) {
            throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
            return false;
        }

        // Check if the graph contains non-zero diagonal elements
        for (size_t i = 0; i < this->graph.size(); ++i) {
            if (this->graph[i][i] != 0) {
                throw std::invalid_argument("Invalid graph: The graph contains non-zero diagonal elements.");
                return false;
            }
        }

        return true;
    }

    // Operator +
    Graph Graph::operator+(const Graph& other) const {
        if (this->numVertices != other.numVertices) {
            throw std::invalid_argument("Graphs must have the same dimensions to be added.");
        }

        std::vector<std::vector<int>> result = this->graph;

        for (size_t i = 0; i < result.size(); ++i) {
            for (size_t j = 0; j < result[i].size(); ++j) {
                result[i][j] += other.graph[i][j];
            }
        }

        Graph newGraph;
        newGraph.loadGraph(result);
        if (!newGraph.validGraph()) {
            throw std::invalid_argument("Invalid graph after addition.");
        }
        return newGraph;
    }

    // Operator -
    Graph Graph::operator-(const Graph& other) const {
        if (this->numVertices != other.numVertices) {
            throw std::invalid_argument("Graphs must have the same dimensions to be subtracted.");
        }

        std::vector<std::vector<int>> result = this->graph;

        for (size_t i = 0; i < result.size(); ++i) {
            for (size_t j = 0; j < result[i].size(); ++j) {
                result[i][j] -= other.graph[i][j];
            }
        }

        Graph newGraph;
        newGraph.loadGraph(result);
        if (!newGraph.validGraph()) {
            throw std::invalid_argument("Invalid graph after subtraction.");
        }
        return newGraph;
    }

    // Operator +=
    Graph& Graph::operator+=(const Graph& other) {
        if (this->numVertices != other.numVertices) {
            throw std::invalid_argument("Graphs must have the same dimensions to be added.");
        }

        for (size_t i = 0; i < this->graph.size(); ++i) {
            for (size_t j = 0; j < this->graph[i].size(); ++j) {
                this->graph[i][j] += other.graph[i][j];
            }
        }

        // Recalculate the number of edges
        this->numEdges = calculateNumEdges(this->graph);
        if (!this->validGraph()) {
            throw std::invalid_argument("Invalid graph after addition.");
        }
        return *this;
    }

    // Operator -=
    Graph& Graph::operator-=(const Graph& other) {
        if (this->numVertices != other.numVertices) {
            throw std::invalid_argument("Graphs must have the same dimensions to be subtracted.");
        }

        for (size_t i = 0; i < this->graph.size(); ++i) {
            for (size_t j = 0; j < this->graph[i].size(); ++j) {
                this->graph[i][j] -= other.graph[i][j];
            }
        }

        // Recalculate the number of edges
        this->numEdges = calculateNumEdges(this->graph);
        if (!this->validGraph()) {
            throw std::invalid_argument("Invalid graph after subtraction.");
        }
        return *this;
    }

    // Unary Operator -
    Graph Graph::operator-() const {
        std::vector<std::vector<int>> result = this->graph;

        for (size_t i = 0; i < result.size(); ++i) {
            for (size_t j = 0; j < result[i].size(); ++j) {
                result[i][j] *= -1;
            }
        }

        Graph newGraph;
        newGraph.loadGraph(result);
        if (!newGraph.validGraph()) {
            throw std::invalid_argument("Invalid graph after unary minus.");
        }
        return newGraph;
    }

    // Operator ++
    Graph& Graph::operator++() {
        for (size_t i = 0; i < this->numVertices; ++i) {
            for (size_t j = 0; j < this->numVertices; ++j) {
                if (this->graph[i][j] != 0) {
                    this->graph[i][j]++;
                }
            }
        }
        // Recalculate the number of edges
        this->numEdges = calculateNumEdges(this->graph);
        if (!this->validGraph()) {
            throw std::invalid_argument("Invalid graph after increment.");
        }
        return *this;
    }

    // Operator --
    Graph& Graph::operator--() {
        for (size_t i = 0; i < this->numVertices; ++i) {
            for (size_t j = 0; j < this->numVertices; ++j) {
                if (this->graph[i][j] != 0) {
                    this->graph[i][j]--;
                }
            }
        }
        // Recalculate the number of edges
        this->numEdges = calculateNumEdges(this->graph);
        if (!this->validGraph()) {
            throw std::invalid_argument("Invalid graph after decrement.");
        }
        return *this;
    }

    // Operator *
    Graph& Graph::operator*(int scalar) {
        for (size_t i = 0; i < this->numVertices; ++i) {
            for (size_t j = 0; j < this->numVertices; ++j) {
                this->graph[i][j] *= scalar;
            }
        }
        // Recalculate the number of edges
        this->numEdges = calculateNumEdges(this->graph);
        if (!this->validGraph()) {
            throw std::invalid_argument("Invalid graph after scalar multiplication.");
        }
        return *this;
    }

    // Operator *
    Graph Graph::operator*(const Graph& other) const {
        // Check if the graphs have the same number of vertices
        if (this->numVertices != other.numVertices) {
            throw std::invalid_argument("Invalid operation: Graphs have different number of vertices.");
        }

        // Initialize a new graph for the result
        Graph result;
        result.numVertices = this->numVertices;
        result.graph.resize(this->numVertices, std::vector<int>(this->numVertices, 0));

        // Perform matrix multiplication
        for (size_t i = 0; i < this->numVertices; ++i) {
            for (size_t j = 0; j < this->numVertices; ++j) {
                for (size_t k = 0; k < this->numVertices; ++k) {
                    result.graph[i][j] += this->graph[i][k] * other.graph[k][j];
                }
            }
        }

        // Ensure zero-diagonal
        for (size_t i = 0; i < result.numVertices; ++i) {
            result.graph[i][i] = 0;
        }

        if (!result.validGraph()) {
            throw std::invalid_argument("Invalid graph after matrix multiplication.");
        }

        return result;
    }

       // Helper method to check if the current graph is fully contained within another graph
    bool isContainedIn(const Graph& graph1, const Graph& graph2) {
        if (graph1.getNumVertices() > graph2.getNumVertices()) return false;

        size_t n = graph1.getNumVertices();
        size_t m = graph2.getNumVertices();
        const auto& g1 = graph1.getGraph();
        const auto& g2 = graph2.getGraph();

        for (size_t i = 0; i <= m - n; ++i) {
            for (size_t j = 0; j <= m - n; ++j) {
                bool match = true;
                for (size_t k = 0; k < n; ++k) {
                    for (size_t l = 0; l < n; ++l) {
                        if (g1[k][l] != 0 && g1[k][l] != g2[i + k][j + l]) {
                            match = false;
                            break;
                        }
                    }
                    if (!match) break;
                }
                if (match) return true;
            }
        }
        return false;
    }


    // Operator <
    bool Graph::operator<(const Graph& other) const {
        if (isContainedIn(*this, other)) {
            return true;
        } else if (isContainedIn(other, *this)) {
            return false;
        } else {
            return this->numEdges < other.numEdges;
        }
    }

    // Operator >
    bool Graph::operator>(const Graph& other) const {
        if (isContainedIn(other, *this)) {
            return true;
        } else if (isContainedIn(*this, other)) {
            return false;
        } else {
            return this->numEdges > other.numEdges;
        }
    }

    // Operator ==
    bool Graph::operator==(const Graph& other) const {
        if (this->numVertices != other.numVertices) {
            return false;
        }

        const auto& g1 = this->graph;
        const auto& g2 = other.graph;

        for (size_t i = 0; i < this->numVertices; ++i) {
            for (size_t j = 0; j < this->numVertices; ++j) {
                if (g1[i][j] != g2[i][j]) {
                    return false;
                }
            }
        }

        return true;
    }

    // Operator !=
    bool Graph::operator!=(const Graph& other) const {
        return !(*this == other);
    }
    
    // Operator <=
    bool Graph::operator<=(const Graph& other) const {
        return (*this < other) || (*this == other);
    }

    // Operator >=
    bool Graph::operator>=(const Graph& other) const {
        return (*this > other) || (*this == other);
    }

    // Member function to print a graphical representation of the graph
    void Graph::visualGraph() const {
        const auto& matrix = this->graph;
        size_t numVertices = this->numVertices;

        std::cout << "Visual Representation of the Graph:" << std::endl;

        // Print column numbers
        std::cout << "   ";
        for (size_t i = 0; i < numVertices; ++i) {
            std::cout << i << " ";
        }
        std::cout << std::endl;

        // Print horizontal line
        std::cout << "  ";
        for (size_t i = 0; i < numVertices * 2; ++i) {
            std::cout << "-";
        }
        std::cout << std::endl;

        // Print matrix
        for (size_t i = 0; i < numVertices; ++i) {
            // Print row number
            std::cout << i << "| ";

            // Print row elements
            for (size_t j = 0; j < numVertices; ++j) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
}