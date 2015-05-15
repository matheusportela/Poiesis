// File adapter, providing operating system and C++ STL abstraction.

#ifndef FILE_H_
#define FILE_H_

#include <fstream>
#include <iostream>
#include <string>

class File
{
  public:
    File(std::string file);
    ~File();

    // Opens file stream.
    void Open(std::string file);
    
    // Closes file stream.
    void Close();

    // Checks whether it is possible to read a line from the file stream. This
    // is false when end-of-file has been reached.
    bool CanRead();

    // Reads a single line.
    std::string ReadLine();

  private:
    std::ifstream filestream;
};

#endif // FILE_H_