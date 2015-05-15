#include "bandit/core/parser/ConfigParser.h"

ConfigParser& ConfigParser::GetInstance()
{
    static ConfigParser instance;
    return instance;
};

void ConfigParser::Parse(File& file)
{
    std::string line;

    while (file.CanRead())
    {
        line = file.ReadLine();

        if (IsEmptyLine(line) or IsCommentLine(line))
            continue;
        
        ParseLine(line);
    }

    Print();
}

void ConfigParser::SetPath(std::string path)
{
    this->path = path;
}

bool ConfigParser::IsEmptyLine(std::string line)
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

    if (IsSpecialKey(key)) 
    {
        if (key == "$PATH")
            SetPath(value);
    }

    if (Contains(key))
    {
        LOG_E("[ConfigParser] Key \"" << key << "\" defined multiple times in "
            << "configuration file.");
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

    LOG_D("[ConfigParser] Configuration");

    for (it = configurationMap.begin(); it != configurationMap.end(); ++it)
        LOG_D(it->first << " -> " << it->second);
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
        LOG_E("[ConfigParser] Key \"" << key << "\" does not exist in the "
            << "configuration file.");
        exit(1);
    }
}

std::string ConfigParser::GetWithPath(std::string key)
{
    if (path.empty())
    {
        LOG_E("[ConfigParser] Trying to read entry without setting path. "
            "Define \"$PATH\" in your configuration file first.");
        exit(1);
    }

    return (File::Join(path, Get(key)));
}

int ConfigParser::GetAsInteger(std::string key)
{
    return std::stoi(Get(key));
}

float ConfigParser::GetAsFloat(std::string key)
{
    return std::stof(Get(key));
}

char ConfigParser::GetAsChar(std::string key)
{
    std::string value = Get(key);
    return value[0];
}

bool ConfigParser::GetAsBool(std::string key)
{
    std::string value = Get(key);

    if (value == "true")
        return true;
    else if (value == "false")
        return false;
    
    LOG_E("[ConfigParser] Unknown boolean value \"" << value << "\". "
        << "Allowed values are \"true\" and \"false\".");
    exit(1);

}

std::string ConfigParser::operator[](std::string key)
{
    return Get(key);
}