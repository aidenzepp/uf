//
// Created by Aiden Zepp on 2023-10-29.
//

#ifndef PROJECT_2_GRAPH_H
#define PROJECT_2_GRAPH_H


// std...
#include <map>
#include <vector>
#include <string>

/*
 * @class Graph
 *
 * @brief Represents an adjacency-list implementation of a graph with the
 * attributes of: directed, unweighted, unconnected, and cyclic. The graph
 * is a mild representation of a web-network.
 *
 * The graph stores values of type `std::map<std::string, std::vector<std::string>>`
 * which represents the graph itself. Each key represents a website, and
 * the vector of strings represents the websites that the aforementioned
 * website is linked to or from.
 *
 * Because of the chosen data-structure representation
 * (i.e., `std::map` and `std::vector`), the `Graph` is capable of taking
 * cyclical and directed patterns. These are patterns which are likely to
 * occur in a real web-network of links and webpages.
 */
class Graph
{
public:

    //
    // Typedef
    //

    /*
     * @typedef Node
     *
     * @brief Represents the type of the stored webpage name in the graph.
     */
    using Node = std::string;

    /*
     * @typedef Rank
     *
     * @brief Represents the type of the calculated 'PageRank' algorithm value.
     */
    using Rank = double;

    /*
     * @typedef Page
     *
     * @brief Represents the type of the calculated 'PageRank' algorithm result.
     */
    using Page = std::map<Node, Rank>;

    //
    // Construct / Destruct
    //

    /*
     * @brief Constructs a new `Graph` with an empty data field.
     */
    Graph();

    /*
     * @brief Destructs an old `Graph`.
     */
    ~Graph();

    //
    // Methods
    //

    /*
     * @brief Calculates the rankings of the webpages stored using the famous
     * 'PageRank' algorithm.
     *
     * @param power The number of iterations the 'PageRank' algorithm should
     * have before returning. Note that the values of `0` and `1` both return
     * the base page-ranks, where each webpage gets an equal ranking.
     *
     * @return The pages' ranks calculated using the 'PageRank' algorithm.
     */
    Page PageRank(unsigned int power) const;

    /*
     * @brief Inserts the nodes into the `Graph`.
     *
     * @param origin The origin webpage from which `target` emanates from.
     * @param target The target webpage, originating from `origin`.
     */
    void Insert(const Node& origin, const Node& target);

private:

    //
    // Typedefs
    //

    /*
     * @typedef List
     *
     * @brief Represents the type of the stored adjacent nodes for the list's
     * associated node.
     */
    using List = std::vector<Node>;

    /*
     * @typedef Data
     *
     * @brief Represents the totality of the graph's data, containing all of the
     * adjacency lists for every node.
     */
    using Data = std::map<Node, List>;

    /*
     * @enum Flow
     *
     * @brief Represents the direction order with which a `List` is generated.
     */
    enum Flow
    {
        /*
         * Used for finding the nodes that flow
         * "from" the given node.
         *
         * This is the default way that nodes
         * are stored in the `data` field.
         */
        From,

        /*
         * Used for finding the nodes that flow
         * "into" the given node.
         */
        Into,
    };

    //
    // Methods
    //

    /*
     * @brief Returns the number of unique nodes stored in the graph. Note that
     * the returned value is the maximum between the `from` and `into` data fields
     * in the event they become desynchronized.
     */
    unsigned int GetSize() const;

    /*
     * @briefs Returns the default ranks of the nodes in the graph; based off of
     * the 'PageRank' algorithm (i.e., `1.0 / GetSize()`).
     */
    Rank GetRank() const;

    /*
     * @brief Returns the rank of a node given a prior rank from `page` and the
     * out-degree of the `node`; based off of the 'PageRank' algorithm.
     *
     * @param node The node whose rank will be calculated.
     * @param page The values to use to calculate the new rank.
     *
     * @return The new rank of the node.
     */
    Rank GetRank(const Node& node, const Page& page) const;

    /*
     * @brief Returns the adjacency list of the node based on the `Flow`
     * direction.
     *
     * @param node The node whose adjacency list must be obtained.
     * @param flow The direction of the returned adjacency list.
     *
     * @return The adjacency list in the provided direction, or an empty
     * `List` if the node is not found.
     */
    List GetList(const Node& node, const Flow& flow) const;

    /*
     * @brief Returns the graph's data based on the flow direction provided.
     *
     * @param flow The direction of the returned data.
     */
    Data GetData(const Flow& flow) const;

    /*
     * @brief Returns the default `Page`; based off of the 'PageRank' algorithm.
     *
     * @return The default `Page`.
     */
    Page GetPage() const;

    /*
     * @brief Recursively calculates the `Page`; based off of the 'PageRank'
     * algorithm.
     *
     * @param power The number of iterations the 'PageRank' algorithm should
     * have before returning. Note that the values of `0` and `1` both return
     * the base page-ranks, where each webpage gets an equal ranking.
     * @param page The output `Page` being used and computed.
     */
    void GetPage(unsigned int power, Page& page) const;

    /*
     * @brief Inserts the nodes into the graph based on the flow direction.
     *
     * @param origin The origin webpage from which `target` emanates from.
     * @param target The target webpage, originating from `origin`.
     * @param flow The direction specification for which the `origin` and `target`
     * are inserted into.
     */
    void Insert(const Node& origin, const Node& target, const Flow& flow);

    //
    // Properties
    //

    /*
     * @brief Represents the stored data (i.e., nodes and their respective
     * adjacency lists) of the graph. The data is stored in the "from" form.
     */
    Data from;

    /*
     * @brief Represents the stored data (i.e., nodes and their respective
     * adjacency lists) of the graph. The data is stored in the "into" form.
     */
    Data into;
};


#endif //PROJECT_2_GRAPH_H
