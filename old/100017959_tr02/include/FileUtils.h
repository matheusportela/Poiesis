// @file   FileUtils.h
// @author Matheus Vieira Portela
// @date   31/03/2015
//
// @brief Useful functions for file handling

#ifndef FILE_UTILS_H_
#define FILE_UTILS_H_

#include <string>

// Join path and filename, compensating for leading and trailing slashes.
std::string join(std::string path, std::string filename);

#endif // FILE_UTILS_H_