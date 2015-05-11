// @file   Parser.cpp
// @author Matheus Vieira Portela
// @date   08/04/2015
//
// @brief Generic parser base class.

#include "Parser.h"

void Parser::Open(std::string file)
{
    filestream.open(file);

    if (!filestream.is_open())
    {
        std::cerr << "ERROR [Parser] Could not open file: " << file << std::endl;
        exit(1);
    }
}

void Parser::Close()
{
    filestream.close();
}

bool Parser::CanRead()
{
    return filestream.good();
}

std::string Parser::ReadLine()
{
    std::string line;
    getline(filestream, line);
    return line;
}

bool Parser::IsEmptyLine(std::string line)
{
    char c;

    for (unsigned int i = 0; i < line.length(); ++i)
    {
        c = line[i];

        if (isprint(c) and !isspace(c))
            return false;
    }

    return true;
}