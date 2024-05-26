/*
Email: danielkuris6@gmail.com
ID: 214539397
Name: Daniel Kuris
*/
#include "Graph.hpp"
#include "Algorithms.hpp"
#include <vector>
#include <string>
#include <stdexcept>
#include "doctest.h" 

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
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "Negative cycle detected");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The graph contains a cycle: 0->1->2->0");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph isn't bipartite.");
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle found");
}

TEST_CASE("Test graph with negative weights")
{
    ariel::Graph g;
    vector<vector<int>> graph = {{0, -1, 0},
                                 {-1, 0, -1},
                                 {0, -1, 0}};

    g.loadGraph(graph); // Load the graph to the object.
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "Negative cycle detected");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "Negative cycle found"); 
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}.");
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle found");
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
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0}, B={1}.");
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
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1, 3}.");
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
    CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "0->1");
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
    CHECK(ariel::Algorithms::isConnected(g) == false);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "There is no path between 0 and 4");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The graph contains a cycle: 1->2->3->4->0");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 1, 3}, B={2, 4}.");
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");
}

TEST_CASE("Test bipartite graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "0->3");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The graph contains a cycle: 0->1->2->3->0");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1, 3}.");
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");
}

TEST_CASE("Test directed graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 0}
    };
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "0->1->2->3");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "No cycle found");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1, 3}.");
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");
}

TEST_CASE("Test graph with negative and positive weights")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0, 0},
        {-1, 0, 1, 0},
        {0, 0, 0, -1},
        {0, -1, 0, 0}
    };
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "Negative cycle detected");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "Negative cycle found");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph isn't bipartite.");
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle found");
}

TEST_CASE("Test graph with one verticle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {{0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 0) == "Invalid start or end vertex");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "No cycle found");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph isn't bipartite.");
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");
}

TEST_CASE("Test graph with two verticles")
{
    ariel::Graph g;
    vector<vector<int>> graph = {{0, 1},
                                 {1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "0->1");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "No cycle found");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0}, B={1}.");
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");
}

TEST_CASE("Test shortestPath to himself")
{
    ariel::Graph g;
    vector<vector<int>> graph = {{0, 1, 0},
                                 {1, 0, 1},
                                 {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 1, 1) == "Invalid request - path to itself");
}

TEST_CASE("Test shortestPath to non-existing verticle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {{0, 1, 0},
                                 {1, 0, 1},
                                 {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 1, 3) == "Invalid start or end vertex");
}


// --------------------- PART B TESTS ---------------------

TEST_CASE("Test graph operators with simple cases")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {{0, 1, 0},
                                   {1, 0, 1},
                                   {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {{0, 0, 1},
                                   {0, 0, 0},
                                   {1, 0, 0}};
    g2.loadGraph(graph2);

    ariel::Graph g3;
    vector<vector<int>> graph3 = {{0, 2, 0},
                                   {2, 0, 2},
                                   {0, 2, 0}};
    g3.loadGraph(graph3);

    ariel::Graph result_addition = g1 + g2;
    vector<vector<int>> expected_addition = {{0, 1, 1},
                                              {1, 0, 1},
                                              {1, 1, 0}};
    CHECK(result_addition.getGraph() == expected_addition);

    ariel::Graph result_subtraction = g1 - g2;
    vector<vector<int>> expected_subtraction = {{0, 1, -1},
                                                 {1, 0, 1},
                                                 {-1, 1, 0}};
    CHECK(result_subtraction.getGraph() == expected_subtraction);

    ariel::Graph result_scalar_multiplication = g1 * 2;
    vector<vector<int>> expected_scalar_multiplication = {{0, 2, 0},
                                                          {2, 0, 2},
                                                          {0, 2, 0}};
    CHECK(result_scalar_multiplication.getGraph() == expected_scalar_multiplication);

    ariel::Graph result_matrix_multiplication = g1 * g2;
    vector<vector<int>> expected_matrix_multiplication = {{0, 0, 0},
                                                          {1, 0, 1},
                                                          {0, 0, 0}};
    CHECK(result_matrix_multiplication.getGraph() == expected_matrix_multiplication);

    ariel::Graph result_increment = g1++;
    vector<vector<int>> expected_increment = {{0, 2, 0},
                                              {2, 0, 2},
                                              {0, 2, 0}};
    CHECK(result_increment.getGraph() == expected_increment);

    ariel::Graph result_decrement = g3--;
    vector<vector<int>> expected_decrement = {{0, 1, 0},
                                              {1, 0, 1},
                                              {0, 1, 0}};
    CHECK(result_decrement.getGraph() == expected_decrement);
}

TEST_CASE("Test graph equal operators")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {{0, 1, 0},
                                   {1, 0, 1},
                                   {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {{0, 1, 0},
                                   {1, 0, 1},
                                   {0, 1, 0}};
    g2.loadGraph(graph2);

    ariel::Graph g3;
    vector<vector<int>> graph3 = {{0, 0, 1},
                                   {0, 0, 0},
                                   {1, 0, 0}};
    g3.loadGraph(graph3);

    CHECK(g1 == g2);
    CHECK(g1 != g3);
}

TEST_CASE("Test graph contain operators")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {{0, 1, 0},
                                   {1, 0, 1},
                                   {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {{0, 0, 1},
                                   {0, 0, 0},
                                   {1, 0, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 > g2);
    CHECK(g2 < g1);
}

TEST_CASE("Test graph contain/equal operators")
{
    //Taken from moodle forum
    ariel::Graph g1;
    vector<vector<int>> graph1 = {{0, 3},
                                   {1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {{0, 4, 3},
                                   {1, 0, -7},
                                   {0, 6, 0}};
    g2.loadGraph(graph2);

    ariel::Graph g3;
    vector<vector<int>> graph3 = {{0, 0, 1},
                                   {1, 0, 1},
                                   {1, 1, 0}};
    g3.loadGraph(graph3);

    CHECK(g1 <= g2);
    CHECK(g3 >= g1);
  
}

TEST_CASE("Test graph arithmetic operators")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {{0, 3},
                                   {1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {{0, 4, 3},
                                   {1, 0, -7},
                                   {0, 6, 0}};
    g2.loadGraph(graph2);

    SUBCASE("Test addition operator") {
        // Addition should throw an exception since graphs are of different sizes
        CHECK_THROWS_AS(g1 + g2, std::invalid_argument);
    }

    SUBCASE("Test subtraction operator") {
        // Subtraction should throw an exception since graphs are of different sizes
        CHECK_THROWS_AS(g1 - g2, std::invalid_argument);
    }

    SUBCASE("Test scalar multiplication with zero") {
        // Scalar multiplication with zero should throw an exception
        CHECK_THROWS_AS(0 * g1, std::invalid_argument);
    }

    SUBCASE("Test multiplication operator") {
        // Multiplication should throw an exception since graphs are of different sizes
        CHECK_THROWS_AS(g1 * g2, std::invalid_argument);
    }

    SUBCASE("Test message after matrix multiplication") {
        std::string errorMessage;
        try {
            ariel::Graph result = g1 * g2;
        } catch (const std::invalid_argument& e) {
            errorMessage = e.what();
        }
        // Check that the error message indicates invalid graph after matrix multiplication
        CHECK(errorMessage.find("Invalid graph after matrix multiplication") != std::string::npos);
    }

}

TEST_CASE("Visual representation of a graph") {
    // Create a sample graph
    ariel::Graph graph;
    std::vector<std::vector<int>> adjacencyMatrix = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };
    graph.loadGraph(adjacencyMatrix);

    // Check the visual representation
    SUBCASE("Test visual representation") {
        // Redirect cout to a stringstream
        std::stringstream output;
        std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        // Print the visual representation
        graph.visualGraph();

        // Reset cout
        std::cout.rdbuf(oldCout);

        // Check the output
        std::string expectedOutput =
            "Visual Representation of the Graph:\n"
            "   0 1 2 3 \n"
            "  ----------\n"
            "0| 0 1 0 1 \n"
            "1| 1 0 1 0 \n"
            "2| 0 1 0 1 \n"
            "3| 1 0 1 0 \n";
        CHECK(output.str() == expectedOutput);
    }
}
