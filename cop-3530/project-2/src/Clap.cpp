//
// Created by Aiden Zepp on 2023-10-29.
//

// std...
#include <iostream>
#include <iomanip>
#include <sstream>

// src...
#include "Clap.h"

//
// --- Public ---
//

//
// Methods
//

void Clap::Run()
{
    unsigned int count;
    unsigned int power;

    std::cin >> count;
    std::cin >> power;

    // Ignore the newline.
    std::cin.ignore();

    Parse(count, power);
}


//
// --- Private ---
//

//
// Methods
//

void Clap::Parse(unsigned int count, unsigned int power)
{
    // Declare the necessary variables.
    std::string inputs;
    Graph::Node origin;
    Graph::Node target;

    // Iterate through the user's inputs.
    for(unsigned int i = 0; i < count; i++)
    {
        if (!std::getline(std::cin, inputs))
        {
            Error(i, count);
            break;
        }


        if (std::istringstream(inputs) >> origin >> target)
        {
            Insert(origin, target);
        }

        else
        {
            Error();
        }
    }

    Print(power);
}

void Clap::Insert(const Graph::Node& origin, const Graph::Node& target)
{
    graph.Insert(origin, target);
}

void Clap::Print(unsigned int power)
{
    for(const auto& pair : graph.PageRank(power))
    {
        std::cout << pair.first << " ";
        std::cout << std::fixed << std::setprecision(2) << pair.second << std::endl;
    }
}

void Clap::Error()
{
    std::cout << "Received more/less than the expected 2 nodes of input in a line.";
    std::cout << std::endl;
}

void Clap::Error(unsigned int provided, unsigned int expected)
{
    std::cout << "Expected " << expected << " number of lines. ";
    std::cout << "CLAP was provided " << provided << " instead.";
    std::cout << std::endl;
}
