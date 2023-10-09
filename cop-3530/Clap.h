//
// Created by Aiden Zepp on 2023-10-08.
//

#ifndef PROJECT_1_CLAP_H
#define PROJECT_1_CLAP_H

// std...
#include <vector>
#include <string>

// custom...
#include "Node.h"

/**
 * @class Clap
 * 
 * @brief Represents the Command Line Argument Parser (C.L.A.P.) for parsing
 * the commands provided by the user.
 * 
 * The class provides functionalities for running the command line parser, validating inputs,
 * stripping unnecessary characters from labels, parsing commands, and executing commands.
 * 
 * The class also provides typedefs for Command, Arg, and Args, which represent a command string,
 * an argument string, and a vector of argument strings, respectively.
 * 
 * The class also stores a static root node pointer for the AVL tree.
 */
class Clap
{
public:

    //
    // Static Methods
    //

    /**
     * @brief Runs the Command Line Argument Parser (C.L.A.P.).
     * 
     * This method reads the number of commands from the standard input, 
     * then reads each command and executes it.
     * 
     * Time complexity: O(n) where n is the number of commands.
     */
    static void Run();

private:

    //
    // Typedefs
    //

    /** 
     * @typedef Command
     * @brief Represents a command string in the Command Line Argument Parser (C.L.A.P.).
     * The command is of type `std::string`.
     */
    using Command = std::string;

    /** 
     * @typedef Arg
     * @brief Represents an argument string in the Command Line Argument Parser (C.L.A.P.).
     * The argument is of type `std::string`.
     */
    using Arg = std::string;

    /** 
     * @typedef Args
     * @brief Represents a vector of argument strings in the Command Line Argument Parser (C.L.A.P.).
     * The arguments are of type `std::vector<Arg>`.
     */
    using Args = std::vector<Arg>;

    //
    // Static Methods
    //

    /**
     * @brief Checks if the given character is valid in the Command Line Argument Parser (C.L.A.P.).
     * The character is considered valid if it is alphabetic (a-z, A-Z), a space, or double quotation marks.
     * 
     * @param letter The character to be checked.
     * 
     * @return `true` if the character is valid, `false` otherwise.
     * 
     * Time complexity: O(1)
     */
    static bool Valid(const char& letter);

    /**
     * @brief Checks if the given value is valid in the Command Line Argument Parser (C.L.A.P.).
     * The value is considered valid if it is strictly eight digits long.
     * 
     * @param value The value to be checked.
     * 
     * @return `true` if the value is valid, `false` otherwise.
     * 
     * Time complexity: O(1)
     */
    static bool Valid(const Node::Value& value);

    /**
     * @brief Checks if the given label is valid in the Command Line Argument Parser (C.L.A.P.).
     * The label if considered valid if every character in the label is valid.
     * 
     * @param label The label to be checked.
     * 
     * @return `true` if the label is valid, `false` otherwise.
     * 
     * Time complexity: O(n) where n is the length of the label.
     */
    static bool Valid(const Node::Label& label);

    /**
     * @brief Strips unnecessary characters from the given label in the Command Line Argument Parser (C.L.A.P.).
     * Strips the double quotation marks from the ends of the label.
     * 
     * @param label The label to be stripped.
     * 
     * Time complexity: O(1)
     */
    static void Strip(Node::Label& label);

    /**
     * @brief Parses the given number of commands from the standard input in the Command Line Argument Parser (C.L.A.P.).
     * 
     * @param n The number of commands to be parsed.
     * 
     * Time complexity: O(n) where n is the number of commands.
     */
    static void Parse(unsigned int n);

    /**
     * @brief Executes the given command with the given arguments in the Command Line Argument Parser (C.L.A.P.).
     * 
     * @param command The command to be executed.
     * @param args The arguments to be passed to the command.
     * 
     * Time complexity: Varies depending on the command.
     */
    static void Execute(const Command& command, const Args& args);

    //
    // Properties
    //

    /**
     * @brief Represents the root node of the AVL tree used in the Command Line Argument Parser (C.L.A.P.).
     *
     * The root is of type Node.
     */
    static Node* root;
};

#endif //PROJECT_1_CLAP_H
