// @file   TileMapParser.cpp
// @author Matheus Vieira Portela
// @date   08/04/2015
//
// @brief Implementation of tile map parser.

#include "TileMapParser.h"

TileMapParser::TileMapParser() : parsedWidth(0), parsedHeight(0),
    parsedDepth(0), parserState(TileMapParserState::ParseSize)
{
}

int TileMapParser::GetParsedWidth()
{
    return parsedWidth;
}

int TileMapParser::GetParsedHeight()
{
    return parsedHeight;
}

int TileMapParser::GetParsedDepth()
{
    return parsedDepth;
}

std::vector<int>& TileMapParser::GetParsedTileMap()
{
    return parsedTileMap;
}

void TileMapParser::ParseSizeToken(std::string token, int index)
{
    switch (index)
    {
        case 0:
            parsedWidth = std::stoi(token);
            break;
        case 1:
            parsedHeight = std::stoi(token);
            break;
        case 2:
            parsedDepth = std::stoi(token);
            parserState = TileMapParserState::ParseLayer;
            break;
    }
}

void TileMapParser::ParseLayerToken(std::string token, int index)
{
    // This is ugly.
    // The tile map file stores tiles with an offset of 1. This means that
    // whenever there is a 0 in the file, no tile must be rendered.
    // We remove this offset here in a hardcoded fashion.
    parsedTileMap.emplace_back(std::stoi(token) - 1);
}

void TileMapParser::ParseToken(std::string token, int index)
{
    switch (parserState)
    {
        case TileMapParserState::ParseSize:
            ParseSizeToken(token, index);
            break;
        case TileMapParserState::ParseLayer:
            ParseLayerToken(token, index);
            break;
    }
}

void TileMapParser::ParseLine(std::string line)
{
    std::string delimiter = TILE_MAP_DELIMITER;
    std::string token;
    size_t pos = 0;
    int index = 0;

    while ((pos = line.find(delimiter)) != std::string::npos)
    {
        token = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());
        ParseToken(token, index);
        ++index;
    }
}

void TileMapParser::Parse(std::string filename)
{
    std::string line;

    Open(filename);

    while (CanRead())
    {
        line = ReadLine();
        ParseLine(line);
    }

    Close();
}