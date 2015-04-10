// @file   FileUtils.cpp
// @author Matheus Vieira Portela
// @date   31/03/2015
//
// @brief Useful functions for file handling

#include "FileUtils.h"

std::string join(std::string path, std::string filename)
{
    std::string complete_path;

    complete_path.append(path);

    // Transform "path" into "path/"
    if (path.back() != '/')
        complete_path.append("/");

    // Avoid "path//filename" situation
    if (filename.front() == '/')
        complete_path.append(filename.substr(1, filename.size()));
    else
        complete_path.append(filename);

    return complete_path;
}