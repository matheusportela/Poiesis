// @file   Config.cpp
// @author Matheus Vieira Portela
// @date   29/03/2015
//
// @brief Configuration parser
//
// Implementation of configuration parser.

#include "Config.h"

Config& Config::GetInstance()
{
    // Singleton pattern using the approach suggested at
    // http://stackoverflow.com/questions/1008019/c-singleton-design-pattern
    static Config instance;
    return instance;
};

void Config::SetPath(std::string path)
{
    this->path = path;
}

void Config::Read(std::string filename)
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

void Config::Open(std::string filename)
{
    filestream.open(filename);

    if (!filestream.is_open())
    {
        std::cerr << "ERROR [Config] Could not open configuration file."
                  << std::endl;
        exit(1);
    }
}

void Config::Close()
{
    filestream.close();
}

bool Config::CanRead()
{
    return filestream.good();
}

std::string Config::ReadLine()
{
    std::string line;
    getline(filestream, line);
    return line;
}

bool Config::IsEmptyLine(std::string line)
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

bool Config::IsCommentLine(std::string line)
{
    return line[0] == '#';
}

bool Config::IsSpecialKey(std::string key)
{
    return key.front() == '$';
}

void Config::ParseLine(std::string line)
{
    // Using the approach suggested by http://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
    std::string delimiter = DELIMITER;
    size_t pos = line.find(delimiter);
    std::string key = SanitizeLine(line.substr(0, pos));
    std::string value = SanitizeLine(line.substr(pos + delimiter.length(),
                                                 line.length()));

    if (IsSpecialKey(key) and key == "$PATH")
        SetPath(value);

    configurationMap[key] = value;
}

std::string Config::SanitizeLine(std::string line)
{
    std::stringstream trimmer;
    trimmer << line;
    line.clear();
    trimmer >> line;
    return line;
}

void Config::Print()
{
    std::map<std::string, std::string>::iterator it;

    std::cout << "=============================================" << std::endl;
    std::cout << "Configuration file: " << configurationFilename << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << std::endl;

    for (it = configurationMap.begin(); it != configurationMap.end(); ++it)
        std::cout << it->first << " -> " << it->second << std::endl;
}

bool Config::Contains(std::string key)
{
    // Iterator receives std::map::end value when the map does not contain any
    // entry with the given key.
    std::map<std::string, std::string>::iterator it = configurationMap.find(key);

    return (it != configurationMap.end());
}

std::string Config::Get(std::string key)
{
    if (Contains(key))
    {
        return configurationMap[key];
    }
    else
    {
        std::cerr << "ERROR [Config] Key \"" << key << "\" does not exist in the "
                  << "configuration file." << std::endl;
        exit(1);
    }
}

std::string Config::GetWithPath(std::string key)
{
    if (path.empty())
    {
        std::cerr << "ERROR [Config] Trying to read entry without setting path. "
                  << "Define \"$PATH\" in your configuration file first."
                  << std::endl;
        exit(1);
    }

    return (join(path, Get(key)));
}

std::string Config::operator[](std::string key)
{
    return Get(key);
}