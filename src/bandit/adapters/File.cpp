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

std::string File::Join(std::string path, std::string filename)
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