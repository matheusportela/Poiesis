// @file   TileMap.h
// @author Matheus Vieira Portela
// @date   08/04/2015
//
// @brief 3 dimensional matrix representing the game map
//
// Tile map contains a vector with holds the entire game map. It provides
// functionality to let tiles without renderization, simulating transparency.

#ifndef TILE_MAP_H_
#define TILE_MAP_H_

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

#include "TileMapParser.h"
#include "TileSet.h"

class TileSet;

class TileMap
{
  public:
    // Initializes the tile map.
    TileMap(std::string file, TileSet* tileSet);

    // Getters and setters.
    int GetWidth();
    int GetHeight();
    int GetDepth();
    void SetTileSet(TileSet* tileSet);

    // Loads a tile map from tile configuration file.
    void Load(std::string file);

    // Checks whether the given indices are within bounds.
    bool IsValidIndex(int x, int y, int z);

    // Finds the tile reference.
    int& At(int x, int y, int z = 0);

    // Prints tile map to standard output.
    void Print();

    // Render a single map layer.
    void RenderLayer(int layer, Point& cameraPoint);

    // Render all map layers.
    void Render(Point& cameraPoint);

  private:
    // Parser for getting tile map definition from a file.
    TileMapParser tileMapParser;

    // Tile map stored as a vector structure for performance purposes.
    std::vector<int> tileMatrix;

    // Tile set in use.
    TileSet* tileSet;

    // Tile map size defitions.
    int width;
    int height;
    int depth;
};

#endif // TILE_MAP_H_