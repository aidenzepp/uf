//
// Created by Aiden Zepp on 2023-10-29.
//

// std...
#include <iostream>
#include <algorithm>

// custom...
#include "Graph.h"

//
// --- Public ---
//

//
// Construct / Destruct
//

Graph::Graph()
{
    from = {};
    into = {};
}

Graph::~Graph()
{
    // Not necessary to do anything...
}

//
// Methods
//

Graph::Page Graph::PageRank(unsigned int power) const
{
    Page page = GetPage();

    GetPage(power, page);

    return page;
}

void Graph::Insert(const Graph::Node& origin, const Graph::Node& target)
{
    Insert(origin, target, Flow::From);
    Insert(origin, target, Flow::Into);
}


//
// --- Private ---
//

//
// Methods
//

unsigned int Graph::GetSize() const
{
    // Although it shouldn't reasonably ever happen, in the event that the two
    // `Data` fields become desynchronized, take the size of the larger one.
    return std::max(from.size(), into.size());
}

Graph::Rank Graph::GetRank() const
{
    const Rank size = static_cast<Rank>(GetSize());

    return (size != 0.0) ? 1.0 / size : 0.0;
}

Graph::Rank Graph::GetRank(const Graph::Node &node, const Graph::Page &page) const
{
    unsigned int outdegree = GetList(node, Graph::Flow::From).size();

    // `node` is found in `page` AND `outdegree` is not zero.
    try
    {
        return (outdegree != 0) ? page.at(node) / static_cast<Rank>(outdegree) : 0.0;
    }

    // `node` is not found in `page`.
    catch (const std::out_of_range& _)
    {
        return 0.0;
    }
}

Graph::List Graph::GetList(const Graph::Node &node, const Graph::Flow &flow) const
{
    // `node` is found in `Data`.
    try
    {
        if (flow == Flow::From)
        {
            return from.at(node);
        }

        if (flow == Flow::Into)
        {
            return into.at(node);
        }
    }

    // `node` is not found in `Data`.
    catch (const std::out_of_range& _)
    {
        return {};
    }

    // Just in case.
    return {};
}

Graph::Data Graph::GetData(const Graph::Flow &flow) const
{
    if (flow == Flow::From)
    {
        return from;
    }

    if (flow == Flow::Into)
    {
        return into;
    }

    // Just in case.
    return {};
}

Graph::Page Graph::GetPage() const
{
    Page page = {};

    for(const auto& pair : GetData(Flow::From))
    {
        page[pair.first] = GetRank();
    }

    return page;
}

void Graph::GetPage(unsigned int power, Graph::Page& page) const
{
    // Base case.
    if (power <= 1) return;

    // Recurse.
    GetPage(power - 1, page);

    // Calculate.
    Page temp = page;
    for(auto& pair : temp)
    {
        // Initialize the rank's value to 0.
        pair.second = 0.0;

        // For each node that flows into the current node...
        for(const Node& node : GetList(pair.first, Graph::Flow::Into))
        {
            // Calculate the "into-node's" rank. Add to current node.
            pair.second += GetRank(node, page);
        }
    }

    // Save values.
    page = temp;
}

void Graph::Insert(const Graph::Node &origin, const Graph::Node &target, const Graph::Flow &flow)
{
    if (flow == Flow::From)
    {
        // Add `target` to `origin`s list of nodes.
        from[origin].push_back(target);

        // If `target` doesn't yet exist, add it.
        from.emplace(target, List());
    }

    if (flow == Flow::Into)
    {
        // Add `origin` to `target`s list of nodes.
        into[target].push_back(origin);

        // If `origin` doesn't yet exist, add it.
        into.emplace(origin, List());
    }
}
