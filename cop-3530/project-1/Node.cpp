//
// Created by Aiden Zepp on 2023-10-05.
//

// std...
#include <iostream>

// custom...
#include "Node.h"


//
// --- Public ---
//

//
// Construct / Destruct
//

Node::Node(Node::Value value, Node::Label label)
{
    this->value = value;
    this->label = std::move(label);
    this->cache = 1;
    this->nodeL = nullptr;
    this->nodeR = nullptr;
}

//
// Static Methods
//

Node* Node::Insert(Node* root, const Node::Value& value, const Node::Label& label)
{
    // Empty location found; successful insert!
    if (!root)
    {
        PrintSuccess();

        return new Node(value, label);
    }

    // Insert to the left subtree...
    else if (root->value > value)
    {
        root->nodeL = Insert(root->nodeL, value, label);
    }

    // Insert to the right subtree...
    else if (root->value < value)
    {
        root->nodeR = Insert(root->nodeR, value, label);
    }

    // Values must be unique; unsuccessful insert!
    else
    {
        PrintFailure();

        return root;
    }

    // Update the cache.
    root->cache = Max(root) + 1;

    // Re-balance the tree (if necessary).
    return Repair(root);
}

Node* Node::Remove(Node* root, const Node::Value& value)
{
    // Expected a node; unsuccessful remove!
    if (!root)
    {
        PrintFailure();

        return root;
    }

    // Remove in the left subtree...
    else if (root->value > value)
    {
        root->nodeL = Remove(root->nodeL, value);
    }

    // Remove in the right subtree...
    else if (root->value < value)
    {
        root->nodeR = Remove(root->nodeR, value);
    }

    // Found the node to delete; successful deletion!
    else
    {
        // Removal for node with 1 child or no child.
        if (!root->nodeL || !root->nodeR)
        {
            PrintSuccess();

            Node* temp = (root->nodeL) ? root->nodeL : root->nodeR;

            delete root;
            return temp;
        }

        // Removal for node with 2 children.
        else
        {
            // Get the in-order successor.
            Node* temp = Successor(root->nodeR);

            root->value = temp->value;
            root->label = temp->label;
            root->nodeR = Remove(root->nodeR, temp->value);
        }
    }

    // Update the cache.
    root->cache = Max(root) + 1;

    // Re-balance the tree (if necessary).
    return Repair(root);
}

Node* Node::Remove(Node* root, unsigned int n)
{
    std::vector<Node*> nodes;
    Traverse(root, Order::LNR, nodes);

    // Try to remove the node at the n-th position.
    try
    {
        return Remove(root, nodes.at(n)->value);
    }

    // N-th position unobtainable; unsuccessful remove!
    catch (...)
    {
        PrintFailure();

        return root;
    }
}

void Node::Search(const Node* root, const Node::Value& value)
{
    // Expected a node; unsuccessful search!
    if (!root)
    {
        PrintFailure();
    }

    // Found the matching value; successful search!
    else if (root->value == value)
    {
        Print(root->label);
    }

    // Search to the left subtree...
    else if (root->value > value)
    {
        Search(root->nodeL, value);
    }

    // Search to the right subtree...
    else if (root->value < value)
    {
        Search(root->nodeR, value);
    }
}

void Node::Search(const Node* root, const Node::Label& label)
{
    std::string result;
    Search(root, label, result);

    if (!result.empty())
    {
        // Print, but remove the last newline insertion.
        Print(result.substr(0, result.rfind('\n')));
    }

    else
    {
        PrintFailure();
    }
}

void Node::Print(const Node* root, Node::Order order)
{
    std::string result;
    Traverse(root, order, result);

    if (!result.empty())
    {
        // Print, but remove the last ", " comma insertion.
        Print(result.substr(0, result.rfind(',')));
    }

    else
    {
        Print(result);
    }
}

void Node::Print(const Node* node)
{
    std::cout << Height(node) << std::endl;
}

void Node::Print(const std::string& phrase)
{
    std::cout << phrase << std::endl;
}

void Node::PrintSuccess()
{
    std::cout << "successful" << std::endl;
}

void Node::PrintFailure()
{
    std::cout << "unsuccessful" << std::endl;
}


//
// --- Private ---
//

//
// Static Methods
//

Node::Label Node::Pad(const Node* node)
{
    std::string padded = std::to_string(node->value);

    if (padded.size() < 8)
    {
        return std::string(8 - padded.size(), '0') + padded;
    }

    else
    {
        return padded;
    }
}

Node::Cache Node::Height(const Node* node)
{
    return (node) ? node->cache : 0;
}

Node::Cache Node::Max(const Node* node)
{
    if (node)
    {
        return std::max(Height(node->nodeL), Height(node->nodeR));
    }

    else
    {
        return 0;
    }
}

int Node::Factor(Node* node)
{
    return (node) ? Height(node->nodeL) - Height(node->nodeR) : 0;
}

Node* Node::Successor(Node* root)
{
    // *Safely* guarantee there is no node to the left.
    if (!root || !root->nodeL)
    {
        return root;
    }

    return Successor(root->nodeL);
}

void Node::Search(const Node* root, const Node::Label& label, std::string& output)
{
    if (!root)
    {
        return;
    }

    if (root->nodeL)
    {
        Search(root->nodeL, label, output);
    }

    if (root->label == label)
    {
        output.append(Pad(root));
        output.append("\n");
    }

    if (root->nodeR)
    {
        Search(root->nodeR, label, output);
    }
}

void Node::Traverse(const Node* root, const Node::Order& order, std::string& output)
{
    // Base case.
    if (!root)
    {
        return;
    }

    // Pre-Order Traversal
    else if (order == Order::NLR)
    {
        output.append(root->label + ", ");
        Traverse(root->nodeL, order, output);
        Traverse(root->nodeR, order, output);
    }

    // In-Order Traversal
    else if (order == Order::LNR)
    {
        Traverse(root->nodeL, order, output);
        output.append(root->label + ", ");
        Traverse(root->nodeR, order, output);
    }

    // Post-Order Traversal
    else if (order == Order::LRN)
    {
        Traverse(root->nodeL, order, output);
        Traverse(root->nodeR, order, output);
        output.append(root->label + ", ");
    }
}

void Node::Traverse(Node* root, const Node::Order& order, std::vector<Node*>& output)
{
    // Base case.
    if (!root)
    {
        return;
    }

    // Pre-Order Traversal
    else if (order == Order::NLR)
    {
        output.push_back(root);
        Traverse(root->nodeL, order, output);
        Traverse(root->nodeR, order, output);
    }

    // In-Order Traversal
    else if (order == Order::LNR)
    {
        Traverse(root->nodeL, order, output);
        output.push_back(root);
        Traverse(root->nodeR, order, output);
    }

    // Post-Order Traversal
    else if (order == Order::LRN)
    {
        Traverse(root->nodeL, order, output);
        Traverse(root->nodeR, order, output);
        output.push_back(root);
    }
}

Node* Node::RotateL(Node* node)
{
    Node* rotateNode = node->nodeR;
    Node* grandchild = node->nodeR->nodeL;

    rotateNode->nodeL = node;
    node->nodeR = grandchild;

    // Update heights.
    node->cache = Max(node) + 1;
    rotateNode->cache = Max(rotateNode) + 1;

    return rotateNode;
}

Node* Node::RotateR(Node* node)
{
    Node* rotateNode = node->nodeL;
    Node* grandchild = node->nodeL->nodeR;

    rotateNode->nodeR = node;
    node->nodeL = grandchild;

    // Update heights.
    node->cache = Max(node) + 1;
    rotateNode->cache = Max(rotateNode) + 1;

    return rotateNode;
}

Node* Node::RotateLR(Node* node)
{
    node->nodeL = RotateL(node->nodeL);
    node = RotateR(node);

    return node;
}

Node* Node::RotateRL(Node* node)
{
    node->nodeR = RotateR(node->nodeR);
    node = RotateL(node);

    return node;
}

Node* Node::Repair(Node* root)
{
    const int balanceN = Factor(root);
    const int balanceL = Factor(root->nodeL);
    const int balanceR = Factor(root->nodeR);

    // L-L Case
    if (balanceN > 1 && balanceL >= 0)
    {
        return RotateR(root);
    }

    // L-R Case
    if (balanceN > 1 && balanceL < 0)
    {
        return RotateLR(root);
    }

    // R-R Case
    if (balanceN < -1 && balanceR <= 0)
    {
        return RotateL(root);
    }

    // R-L Case
    if (balanceN < -1 && balanceR > 0)
    {
        return RotateRL(root);
    }

    // Just in case.
    return root;
}
