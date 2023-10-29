//
// Created by Aiden Zepp on 2023-10-08.
//

// std...
#include <iostream>
#include <sstream>

// custom...
#include "Clap.h"


//
// --- Public ---
//

//
// Static Methods
//

void Clap::Run()
{
    unsigned int numCommands;
    std::cin >> numCommands;

    // Ignore the newline.
    std::cin.ignore();

    Parse(numCommands);
}


//
// --- Private ---
//

//
// Define Static Properties
//

Node* Clap::root = nullptr;

//
// Static Methods
//

bool Clap::Valid(const char &letter)
{
    return std::isalpha(letter) || std::isspace(letter) || letter == '"';
}

bool Clap::Valid(const Node::Value& value)
{
    /**
     * To be valid, the value must be 8 digits. The highest possible 8
     * digit ID is `99999999`. Thus, if the value is lower than that
     * value it should be considered valid.
     *
     * Examples include:
     * - `0` as a value is really `00000000`
     * - `1` as a value is really `00000001`
     */
    return value <= 99999999;
}

bool Clap::Valid(const Node::Label& label)
{
    for(const char letter : label)
    {
        if (!Valid(letter))
        {
            return false;
        }
    }

    return true;
}

void Clap::Strip(Node::Label& label)
{
    // Strips `"` characters from the end.
    label = label.substr(label.find('"'), label.rfind('"'));
}

void Clap::Parse(unsigned int n)
{
    for(unsigned int i = 0; i < n; i++)
    {
        // Declare the line.
        std::string line;

        // Get the string input from the user.
        std::getline(std::cin, line);

        // Need to parse as stream.
        std::istringstream iss(line);

        // Set command first.
        Command command;
        iss >> command;

        Args args;
        Arg arg;

        while(iss >> arg)
        {
            unsigned int limit = 0;
            while(arg.front() == '"' && arg.back() != '"' && limit <= 3)
            {
                Arg temp;

                iss >> temp;

                arg.append(" " + temp);
                limit++;
            }

            args.push_back(arg);
        }

        Execute(command, args);
    }
}

void Clap::Execute(const Clap::Command& command, const Clap::Args& args)
{
    // Base case sanity check.
    if (command.empty())
    {
        // Do nothing...
    }

    else if (command == "insert")
    {
        Node::Value value;
        Node::Label label;

        // Try to access args.
        try
        {
            value = std::stoull(args.at(1));
            label = args.at(0);
        }

        // Args couldn't be properly accessed.
        catch (...)
        {
            Node::PrintFailure();

            return;
        }

        // Validate input.
        if (Valid(value) && Valid(label))
        {
            // Remove `"` from both ends.
            Strip(label);

            Clap::root = Node::Insert(Clap::root, value, label);
        }

        // Invalid input; unsuccessful insert!
        else
        {
            Node::PrintFailure();
        }
    }

    else if (command == "remove")
    {
        Node::Value value;

        // Try to access args.
        try
        {
            value = std::stoull(args.at(0));
        }

        // Args couldn't be properly accessed.
        catch (...)
        {
            Node::PrintFailure();

            return;
        }

        // If `value` is not a valid `Value`, the value wouldn't
        // have been inserted anyway. Thus, it doesn't necessarily
        // need to be checked.
        Clap::root = Node::Remove(Clap::root, value);
    }

    else if (command == "removeInorder")
    {
        unsigned int n;

        // Try to access args.
        try
        {
            n = std::stoi(args.at(0));
        }

        // Args couldn't be properly accessed.
        catch (...)
        {
            Node::PrintFailure();

            return;
        }

        Clap::root = Node::Remove(Clap::root, n);
    }

    else if (command == "search")
    {
        Arg arg;

        // Try to access args.
        try
        {
            arg = args.at(0);
        }

        // Args couldn't be properly accessed.
        catch (...)
        {
            Node::PrintFailure();

            return;
        }


        // Arg is a <ID> argument.
        if (arg.front() != '"')
        {
            Node::Value value;

            // Try to convert arg.
            try
            {
                value = std::stoull(arg);
            }

            // Arg couldn't be properly converted.
            catch (...)
            {
                Node::PrintFailure();

                return;
            }

            Node::Search(Clap::root, value);
        }

        // Arg is a <NAME> argument.
        else
        {
            Node::Label label = arg;
            Strip(label);

            Node::Search(Clap::root, label);
        }
    }

    else if (command == "printPreorder")
    {
        Node::Print(Clap::root, Node::Order::NLR);
    }

    else if (command == "printInorder")
    {
        Node::Print(Clap::root, Node::Order::LNR);
    }

    else if (command == "printPostorder")
    {
        Node::Print(Clap::root, Node::Order::LRN);
    }

    else if (command == "printLevelCount")
    {
        Node::Print(Clap::root);
    }

    else
    {
        Node::PrintFailure();
    }
}
