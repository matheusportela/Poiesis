// @file   Parser.h
// @author Matheus Vieira Portela
// @date   08/04/2015
//
// @brief Generic parser base class.
// 
// This class provides generic methods that are useful for any kind of parser,
// such as open file with verification. Specific methods, must be implemented by
// the child class.

#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <fstream>
#include <string>

class Parser
{
  public:
    // Opens file stream.
    void Open(std::string file);
    
    // Closes file stream.
    void Close();

    // Checks whether it is possible to read a line from the file stream. This
    // is false when end-of-file has been reached.
    bool CanRead();

    // Reads a single line.
    std::string ReadLine();

    // Checks whether the line that has been read is empty, i.e., does not
    // contain any human-readable character.
    bool IsEmptyLine(std::string line);

    // Parser specific method. Must be implemented by the child class. 
    virtual void Parse(std::string filename) = 0;

  private:
    std::ifstream filestream;
};

#endif // PARSER_H_