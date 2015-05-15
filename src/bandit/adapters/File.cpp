#include "bandit/adapters/File.h"

File::File(std::string file)
{
    Open(file);
}

File::~File()
{
    Close();
}

void File::Open(std::string file)
{
    filestream.open(file);

    if (!filestream.is_open())
    {
        std::cerr << "[File] Could not open file: " << file << std::endl;
        exit(1);
    }
}

void File::Close()
{
    if (filestream.is_open())
        filestream.close();
}

bool File::CanRead()
{
    return filestream.good();
}

std::string File::ReadLine()
{
    std::string line;
    getline(filestream, line);
    return line;
}