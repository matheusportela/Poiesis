// @file   ConfigParser.cpp
// @author Matheus Vieira Portela
// @date   29/03/2015
//
// @brief Configuration parser
//
// Implementation of configuration parser.

#include "ConfigParser.h"

ConfigParser& ConfigParser::GetInstance()
{
    // Singleton pattern using the approach suggested at
    // http://stackoverflow.com/questions/1008019/c-singleton-design-pattern
    static ConfigParser instance;
    return instance;
};

void ConfigParser::SetPath(std::string path)
{
    this->path = path;
}

void ConfigParser::Parse(std::string filename)
{
    std::string line;
    configurationFilename = filename;

    Open(filename);

    while (CanRead())
    {
        line = ReadLine();

        if (IsEmptyLine(line) or IsCommentLine(line))
            continue;
        
        ParseLine(line);
    }

    Close();
}

bool ConfigParser::IsCommentLine(std::string line)
{
    return line[0] == '#';
}

bool ConfigParser::IsSpecialKey(std::string key)
{
    return key.front() == '$';
}

void ConfigParser::ParseLine(std::string line)
{
    // Using the approach suggested at http://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
    std::string delimiter = DELIMITER;
    size_t pos = line.find(delimiter);
    std::string key = SanitizeLine(line.substr(0, pos));
    std::string value = SanitizeLine(line.substr(pos + delimiter.length(),
                                                 line.length()));

    if (IsSpecialKey(key) and key == "$PATH")
        SetPath(value);

    if (Contains(key))
    {
        std::cerr << "ERROR [ConfigParser] Key \"" << key << "\" defined "
                  << "multiple times in configuration file." << std::endl;
        exit(1);
    }

    configurationMap[key] = value;
}

std::string ConfigParser::SanitizeLine(std::string line)
{
    // Using the approach suggested at http://codereview.stackexchange.com/questions/40124/trim-white-space-from-string
    if (line.empty())
        return line;

    size_t first = line.find_first_not_of(' ');
    size_t last  = line.find_last_not_of(' ');
    return line.substr(first, last-first+1);
}

void ConfigParser::Print()
{
    std::unordered_map<std::string, std::string>::iterator it;

    std::cout << "=============================================" << std::endl;
    std::cout << "Configuration file: " << configurationFilename << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << std::endl;

    for (it = configurationMap.begin(); it != configurationMap.end(); ++it)
        std::cout << it->first << " -> " << it->second << std::endl;
}

bool ConfigParser::Contains(std::string key)
{
    // find returns end when the key has not been found in the map
    return (configurationMap.find(key) != configurationMap.end());
}

std::string ConfigParser::Get(std::string key)
{
    if (Contains(key))
    {
        return configurationMap[key];
    }
    else
    {
        std::cerr << "ERROR [ConfigParser] Key \"" << key << "\" does not exist in the "
                  << "configuration file." << std::endl;
        exit(1);
    }
}

std::string ConfigParser::GetWithPath(std::string key)
{
    if (path.empty())
    {
        std::cerr << "ERROR [ConfigParser] Trying to read entry without setting path. "
                  << "Define \"$PATH\" in your configuration file first."
                  << std::endl;
        exit(1);
    }

    return (join(path, Get(key)));
}

int ConfigParser::GetAsInteger(std::string key)
{
    return std::stoi(Get(key));
}

int ConfigParser::GetAsFloat(std::string key)
{
    return std::stof(Get(key));
}

char ConfigParser::GetAsChar(std::string key)
{
    std::string value = Get(key);
    return value[0];
}

std::string ConfigParser::operator[](std::string key)
{
    return Get(key);
}