//
// Created by Aiden Zepp on 2023-10-01.
//

#ifndef PROJECT_1_NODE_H
#define PROJECT_1_NODE_H

// std...
#include <vector>
#include <string>

/**
 * @class Node
 * 
 * @brief Represents a node in a Binary Search Tree (BST), more specifically that
 * of a self-balancing AVL tree.
 * 
 * Each node stores a value of type `long long`, a label of type `std::string`, and a cache of type `unsigned int`.
 * The cache is used to store the height of the node in the AVL tree.
 * 
 * The class provides functionalities for constructing and destructing nodes, as well as static methods for
 * inserting nodes, removing nodes, searching nodes, and printing nodes or their properties.
 * 
 * The class also provides private static methods for calculating the height of a node, the maximum height of a node's children,
 * the balance factor of a node, finding the in-order successor of a node, searching for a label in the tree,
 * traversing the tree in different orders, rotating the tree left, right, left-right, and right-left, and repairing the tree.
 * 
 * The class also stores pointers to the left and right child nodes.
 */
class Node
{
public:

    //
    // Typedefs
    //

    /** 
     * @typedef Value
     * @brief Represents the type of the stored value in the node.
     * The value is of type `long long`.
     */
    using Value = unsigned long long;

    /** 
     * @typedef Label
     * @brief Represents the type of the stored label in the node.
     * The label is of type `std::string`.
     */
    using Label = std::string;

    /** 
     * @typedef Cache
     * @brief Represents the type of the stored cache in the node.
     * The cache is used to store the height of the node in the AVL tree and is of type `unsigned int`.
     */
    using Cache = unsigned int;

    /** 
     * @enum Order
     * @brief Represents the traversal orders allowed in the tree.
     */
    enum Order
    {
        /** 
         * @brief Pre-Order Traversal (Node, Left, Right)
         */
        NLR,

        /** 
         * @brief In-Order Traversal (Left, Node, Right)
         */
        LNR,

        /** 
         * @brief Post-Order Traversal (Left, Right, Node)
         */
        LRN,
    };

    //
    // Construct / Destruct
    //

    /**
     * @brief Constructs a new Node with the given value and label.
     * 
     * @param value The value to be stored in the node.
     * @param label The label to be stored in the node.
     * 
     * Time complexity: O(1)
     * - Only requires the initialization of variables.
     */
    Node(Value value, Label label);

    //
    // Static Methods
    //

    /**
     * @brief Inserts a new node with the given value and label into the tree rooted at the given node. 
     * If inserted, "successful" is printed. Otherwise, "unsuccessful" is printed.
     * 
     * @param root The root of the tree where the new node will be inserted.
     * @param value The value to be stored in the new node.
     * @param label The label to be associated with the new node.
     * 
     * @return The root of the tree after the insertion.
     * 
     * Time complexity: O(log n) where n is the number of nodes in the `root` tree.
     * - AVL tree insertion is a O(log n) process, as the tree is self-balancing.
     * - If the tree were instead BST, the worst case scenario would be O(n)
     */
    static Node* Insert(Node* root, const Value& value, const Label& label);

    /**
     * @brief Removes the node with the given value from the tree rooted at the given node. If removed,
     * "successful" is printed. Otherwise, "unsuccessful" is printed.
     * 
     * @param root The root of the tree where the node will be removed.
     * @param value The value of the node to be removed.
     * 
     * @return The root of the tree after the removal.
     * 
     * Time complexity: O(log n) where n is the number of nodes in the `root` tree.
     * - AVL tree deletion is a O(log n) process, as the tree is self-balancing.
     * - Obtaining the balance factor is constant time since the height is cached in the node.
     * - Each rotation, if even necessary, is constant time, thus adding no additional overhead.
     */
    static Node* Remove(Node* root, const Value& value);

    /**
     * @brief Removes the n-th node in the tree via an in-order traversal. If removed,
     * "successful" is printed. Otherwise, "unsuccessful" is printed.
     * 
     * @param root The root of the tree where the node will be removed.
     * @param n The in-order index of the node to be removed.
     * 
     * @return The root of the tree after the removal.
     * 
     * Time complexity: O(n * log(n)) where n is the number of nodes in the `root` tree.
     * - Due to the algorithm programmed, the tree must first be traversed in its entirety to find
     *   the n-th node in the tree. In the worst case, the node is found and thus has to be deleted.
     * - To remove the node from the tree, the tree must be traversed via the original remove method,
     *   which has O(log n) time complexity. Therefore, the total complexity is O(n * log(n)).
     * - There is room for optimization.
     */
    static Node* Remove(Node* root, unsigned int n);

    /**
     * @brief Searches for the node with the given value in the tree rooted at the given node. If found,
     * the node's label is printed. Otherwise, "unsuccessful" is printed.
     * 
     * @param root The root of the tree where the search will be performed.
     * @param value The value of the node to be searched for.
     * 
     * Time complexity: O(log n) where n is the number of nodes in the `root` tree.
     * - AVL tree searches are a O(log n) process, as the tree is self-balancing.
     */
    static void Search(const Node* root, const Value& value);

    /**
     * @brief Searches for the node(s) with the given label in the tree rooted at the given node. If any
     * are found, the nodes' values are printed in a comma-separated fashion. Otherwise, "unsuccessful"
     * is printed.
     * 
     * @param root The root of the tree where the search will be performed.
     * @param label The label of the node to be searched for.
     * 
     * Time complexity: O(n) where n is the number of nodes in the `root` tree.
     * - To find all nodes matching the label, all nodes must be traversed. Therefore, the worst case
     *   (and average case, for that matter) is O(n).
     */
    static void Search(const Node* root, const Label& label);

    /**
     * @brief Prints the nodes' labels of the tree rooted at the given node in the given order.
     * 
     * @param root The root of the tree whose nodes will be printed.
     * @param order The order in which the nodes will be printed.
     * 
     * Time complexity: O(n) where n is the number of nodes in the `root` tree.
     * - To print all nodes in the tree, all nodes must be traversed. Thus, O(n) is the worst
     *   case.
     */
    static void Print(const Node* root, Order order);

    /**
     * @brief Prints the level of the given node. Prints `0` if the node is null.
     * 
     * @param node The node whose level will be printed.
     * 
     * Time complexity: O(1)
     * - Since the height is cached in the node, the complexity to print the node's height
     *   is simply O(1).
     */
    static void Print(const Node* node);

    /**
     * @brief Prints the given label.
     * 
     * @param label The label to be printed.
     * 
     * Time complexity: O(1)
     * - Printing a string to the console is O(1).
     */
    static void Print(const std::string& phrase);

    /**
     * @brief Prints the phrase "successful" to the console.
     *
     * Time complexity: O(1)
     * - Printing a string to the console is O(1).
     */
    static void PrintSuccess();

    /**
     * @brief Prints the phrase "unsuccessful" to the console.
     *
     * Time complexity: O(1)
     * - Printing a string to the console is O(1).
     */
    static void PrintFailure();

private:

    //
    // Static Methods
    //

    /**
     * @brief Left-pads a node's value with zeroes, such that it has the
     * appearance of a valid 8-digit value.
     *
     * @param node The node whose value will be interpreted.
     *
     * @return The node's value as a string, left-padded by zeroes.
     *
     * Time complexity: O(1)
     * - Adding strings together is a constant time operation.
     */
     static Label Pad(const Node* node);

    /**
     * @brief Safely returns the cached height of the node.
     * 
     * @param node The node whose height is to be returned.
     * 
     * @return The cached height of the node.
     * 
     * Time complexity: O(1)
     * - Since the height is cached and only updated upon insertion or deletion,
     *   this function's operation only takes constant time.
     */
    static Cache Height(const Node* node);

    /**
     * @brief Calculates the maximum height of the given node's children.
     * 
     * @param node The node whose children's heights are to be compared.
     * 
     * @return The maximum height of the node's children.
     * 
     * Time complexity: O(1)
     * - Since the height is cached and only updated upon insertion or deletion,
     *   this function's operation only takes constant time.
     */
    static Cache Max(const Node* node);

    /**
     * @brief Calculates the balance factor of the given node.
     * 
     * @param node The node whose balance factor is to be calculated.
     * 
     * @return The balance factor of the node.
     * 
     * Time complexity: O(1)
     * - Since the height is cached and only updated upon insertion or deletion,
     *   this function's operation only takes constant time.
     */
    static int Factor(Node* node);

    /**
     * @brief Finds the in-order successor of the given node.
     * 
     * @param root The root of the tree in which to find the successor.
     * 
     * @return The in-order successor of the node.
     * 
     * Time complexity: O(log n) where n is the number of nodes in the `root` tree.
     * - Traversing the tree by value is a O(log n) operation since the tree
     *   is self-balancing.
     */
    static Node* Successor(Node* root);

    /**
     * @brief A helper function for the public method `Search`. Searches for the node(s) with the given label in the
     * tree and appends the value(s) to `output`.
     * 
     * @param root The root of the tree where the search will be performed.
     * @param label The label of the node to be searched for.
     * @param output The value(s) of the nodes matching the label. May be empty.
     * 
     * Time complexity: O(n) where n is the number of nodes in the `root` tree.
     * - To find all nodes matching the label, all nodes must be traversed. Therefore, the worst case
     *   (and average case, for that matter) is O(n).
     */
    static void Search(const Node* root, const Label& label, std::string& output);

    /**
     * @brief A helper function for the public method `Print`. Traverses the tree and appends each node's
     * label to the output string.
     *
     * @param root The root of the tree where the traversal will be performed.
     * @param order The order of the node to be searched for.
     * @param output The labels of all nodes in the tree. May be empty.
     *
     * Time complexity: O(n) where n is the number of nodes in the `root` tree.
     * - Traversing all nodes in the tree means traversing n nodes. Thus, a time complexity of O(n).
     */
    static void Traverse(const Node* root, const Order& order, std::string& output);

    /**
     * @brief Traverses the tree rooted at the given node in the given order and stores the nodes in the output vector.
     * 
     * @param root The root of the tree to be traversed.
     * @param order The order in which the nodes will be traversed.
     * @param output The vector where the nodes will be stored.
     * 
     * Time complexity: O(n) where n is the number of nodes in the `root` tree.
     * - Traversing all nodes in the tree means traversing n nodes. Thus, a time complexity of O(n).
     */
    static void Traverse(Node* root, const Order& order, std::vector<Node*>& output);

    /**
     * @brief Performs a left rotation on the given node.
     * 
     * @param node The node to be rotated.
     * 
     * @return The new root of the subtree after the rotation.
     * 
     * Time complexity: O(1)
     * - Rotating a node simply requires refactoring the relevant nodes' properties, which is a constant time
     *   operation.
     */
    static Node* RotateL(Node* node);

    /**
     * @brief Performs a right rotation on the given node.
     * 
     * @param node The node to be rotated.
     * 
     * @return The new root of the subtree after the rotation.
     * 
     * Time complexity: O(1)
     * - Rotating a node simply requires refactoring the relevant nodes' properties, which is a constant time
     *   operation.
     */
    static Node* RotateR(Node* node);

    /**
     * @brief Performs a left-right rotation on the given node.
     * 
     * @param node The node to be rotated.
     * 
     * @return The new root of the subtree after the rotation.
     * 
     * Time complexity: O(1)
     * - Rotating a node simply requires refactoring the relevant nodes' properties, which is a constant time
     *   operation.
     * - Likewise, all functions utilized internally by this function are also constant time operations.
     */
    static Node* RotateLR(Node* node);

    /**
     * @brief Performs a right-left rotation on the given node.
     * 
     * @param node The node to be rotated.
     * 
     * @return The new root of the subtree after the rotation.
     * 
     * Time complexity: O(1)
     * - Rotating a node simply requires refactoring the relevant nodes' properties, which is a constant time
     *   operation.
     * - Likewise, all functions utilized internally by this function are also constant time operations.
     */
    static Node* RotateRL(Node* node);

    /**
     * @brief Repairs the tree rooted at the given node by performing necessary rotations.
     * 
     * @param root The root of the tree to be repaired.
     * 
     * @return The new root of the tree after the repair.
     * 
     * Time complexity: O(1)
     * - Re-balancing (i.e., repairing) an AVL tree requires O(1) complexity because every operation contained
     *   withing the function is also constant time.
     * - With the heights cached, there is no additional overhead with obtaining balance factors and thus
     *   subtrees' heights.
     */
    static Node* Repair(Node* root);

    //
    // Properties
    //

    /** 
     * @brief Represents the stored value of the node. 
     * The value is of type `Value`.
     */
    Value value;

    /** 
     * @brief Represents the stored label of the node. 
     * The label is of type `Label`.
     */
    Label label;

    /** 
     * @brief Represents the stored cache of the node. 
     * The cache is used to store the height of the node in the AVL tree and is of type `Cache`.
     */
    Cache cache;

    /** 
     * @brief Represents the stored left-node pointer of the current node. 
     * Points to the left child node in the AVL tree.
     */
    Node* nodeL;

    /** 
     * @brief Represents the stored right-node pointer of the current node. 
     * Points to the right child node in the AVL tree.
     */
    Node* nodeR;
};

#endif //PROJECT_1_NODE_H
