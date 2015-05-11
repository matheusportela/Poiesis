// @file   TileMapParser.h
// @author Matheus Vieira Portela
// @date   08/04/2015
//
// @brief Parse tile map from it's definition file.

#ifndef TILE_MAP_PARSER_H_
#define TILE_MAP_PARSER_H_

#include <fstream>
#include <vector>

#include "Parser.h"

#define TILE_MAP_DELIMITER ","

namespace TileMapParserState
{
    enum State
    {
        ParseSize,
        ParseLayer
    };
}

class TileMapParser : public Parser
{
  public:
    // Initializes tile map parser.
    TileMapParser();

    // Getters and setters
    int GetParsedWidth();
    int GetParsedHeight();
    int GetParsedDepth();
    std::vector<int>& GetParsedTileMap();

    // Parses the index-th token and interpret it as either width, height or
    // number of layers.
    // Also, updates parser state when the last token has been encountered.
    void ParseSizeToken(std::string token, int index);

    // Parses the index-th token and interpret it as a tile map layer token,
    // placing it in the parsed tile map vector.
    void ParseLayerToken(std::string token, int index);

    // Parses the index-th token encountered in the current tile map file line,
    // according to the current parser state.
    void ParseToken(std::string token, int index);

    // Parses a single tile map file line.
    void ParseLine(std::string line);

    // Parses tile map from file.
    void Parse(std::string filename);

  private:
    // Tile map size definitions.
    int parsedWidth;
    int parsedHeight;
    int parsedDepth;

    // Tile map with contents parsed from the tile map definition file.
    std::vector<int> parsedTileMap;

    // Indicates in which parsing step the parser is.
    TileMapParserState::State parserState;
};

#endif // TILE_MAP_PARSER_H_