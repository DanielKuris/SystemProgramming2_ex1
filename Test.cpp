#include "catch.hpp"
#include "Graph.h"
#include "Algorithms.h"
#include <vector>
#include <string>

using namespace std;

TEST_CASE("Test empty graph")
{
    ariel::Graph g;
    vector<vector<int>> graph;
    CHECK_THROWS_AS(g.loadGraph(graph), std::invalid_argument);
}

TEST_CASE("Test graph with non-zero diagonal")
{
    ariel::Graph g;
    vector<vector<int>> graph = {{1, 0, 0},
                                 {0, 1, 0},
                                 {0, 0, 1}};
    CHECK_THROWS_AS(g.loadGraph(graph), std::invalid_argument);
}

TEST_CASE("Test graph with non-square matrix")
{
    ariel::Graph g;
    vector<vector<int>> graph = {{1, 0, 0},
                                 {0, 1, 0}};
    CHECK_THROWS_AS(g.loadGraph(graph), std::invalid_argument);
}

TEST_CASE("Test demo graph")
{
    ariel::Graph g;
    // 3x3 matrix that represents a connected graph.
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph); // Load the graph to the object.
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "No cycle found"); 
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}.");
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");
    
}

TEST_CASE("Test graph with all zeros")
{
    ariel::Graph g;
    vector<vector<int>> graph = {{0, 0, 0},
                                 {0, 0, 0},
                                 {0, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == false);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "There is no path between 0 and 2"); 
    CHECK(ariel::Algorithms::isContainsCycle(g) == "No cycle found");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph isn't bipartite.");
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");
}

TEST_CASE("Test graph with a cycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {{0, 1, 0},
                                 {0, 0, 1},
                                 {1, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The graph contains a cycle: 0->1->2->0");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph isn't bipartite.");
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");
}

TEST_CASE("Test graph with a negative cycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {{0, -1, 0},
                                 {0, 0, -1},
                                 {-1, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The graph contains a cycle: 0->1->2->0");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph isn't bipartite.");
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle found: 0->1->2->0");
}

TEST_CASE("Test graph with negative weights")
{
    ariel::Graph g;
    vector<vector<int>> graph = {{0, -1, 0},
                                 {-1, 0, -1},
                                 {0, -1, 0}};

    g.loadGraph(graph); // Load the graph to the object.
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "No cycle found"); 
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}.");
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");
}

TEST_CASE("Test graph with disconnected components")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == false);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "There is no path between 0 and 2");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "No cycle found");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph isn't bipartite.");
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");
}

TEST_CASE("Test 4 verticles graph with cycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {1, 0, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "0->1->2->3");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The graph contains a cycle: 0->1->2->3->0");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph isn't bipartite.");
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");
}

TEST_CASE("Test graph with multiple paths between vertices")
{
    ariel::Graph g;
    vector<vector<int>> graph = {{0, 1, 1},
                                 {1, 0, 1},
                                 {1, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "0->1");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The graph contains a cycle: 0->1->2->0");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph isn't bipartite.");
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");
}


TEST_CASE("Test graph with all ones") //Multiple cycles
{
    ariel::Graph g;
    vector<vector<int>> graph = {{0, 1, 1, 1, 1},
                                 {1, 0, 1, 1, 1},
                                 {1, 1, 0, 1, 1},
                                 {1, 1, 1, 0, 1},
                                 {1, 1, 1, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->2");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The graph contains a cycle: 0->1->2->0");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph isn't bipartite.");
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");
}


TEST_CASE("Test graph with 2->3->4->2 cycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1},
        {1, 1, 0, 0, 0}
    };
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "0->4");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The graph contains a cycle: 2->3->4->2");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph isn't bipartite.");
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");
}