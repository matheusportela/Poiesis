// Parse files to extract useful information.

#ifndef PARSER_H_
#define PARSER_H_

#include "bandit/adapters/File.h"

class Parser
{
  public:
    virtual ~Parser() {}

    // Extract information from file.
    virtual void Parse(File& file) = 0;
};

#endif // PARSER_H_