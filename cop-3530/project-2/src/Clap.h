//
// Created by Aiden Zepp on 2023-10-29.
//

#ifndef PROJECT_2_CLAP_H
#define PROJECT_2_CLAP_H


// std...
#include <vector>
#include <string>

// custom...
#include "Graph.h"

/**
 * @class Clap
 *
 * @brief Represents the Command Line Argument Parser (C.L.A.P.) for parsing
 * the commands provided by the user.
 *
 * The class provides functionalities for running the command line parser and
 * executing commands.
 *
 * The class stores a `Graph` data field for maintaining the user's graph.
 */
class Clap
{
public:

    //
    // Static Methods
    //

    /*
     * @brief Runs the C.L.A.P., parsing each input and subsequently print the
     * 'PageRank' computation's result.
     */
    void Run();

private:

    //
    // Methods
    //

    /*
     * @brief Parses the given number of inputs `count` and subsequently prints
     * out the 'PageRank' computation using `power` levels of power.
     *
     * @param count The number of inputs to parse from the user.
     * @param power The number of power levels to use for the 'PageRank' algorithm.
     */
    void Parse(unsigned int count, unsigned int power);

    /*
     * @brief Inserts the provided nodes into the `Graph` structure.
     *
     * @param origin The origin webpage from which `target` emanates from.
     * @param target The target webpage, originating from `origin`.
     */
    void Insert(const Graph::Node& origin, const Graph::Node& target);

    /*
     * @brief Prints the 'PageRank' computation's result using the nodes input into
     * the `graph`.
     *
     * @param power The number of power levels to use for the 'PageRank' algorithm.
     */
    void Print(unsigned int power);

    /*
     * @brief Prints an error message regarding an invalid input for the nodes.
     */
    void Error();

    /*
     * @brief Prints an error message regarding an invalid input for the count.
     *
     * @param provided The number of provided input lines from the user.
     * @param expected The number of expected input lines from the user.
     */
    void Error(unsigned int provided, unsigned int expected);

    //
    // Properties
    //

    /*
     * @brief Represents the stored graph for the user.
     */
    Graph graph;
};


#endif //PROJECT_2_CLAP_H
