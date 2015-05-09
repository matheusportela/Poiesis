// @file   TileMap.h
// @author Matheus Vieira Portela
// @date   08/04/2015
//
// @brief 3 dimensional matrix representing the game map
//
// Tile map is a 3-dimensional matrix that provides tiles renderization. It is
// build on top of a tile set, which means that all tiles are contained in a
// single image file.
// The tile map is defined in a configuration file, parsed and renderized to the
// screen.

#ifndef TILE_MAP_H_
#define TILE_MAP_H_

#include <iomanip>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "ConfigParser.h"
#include "Logger.h"
#include "Point.h"
#include "TileMapParser.h"
#include "TileSet.h"

class TileMap
{
  public:
    // Initializes the tile map.
    TileMap(std::string file, std::unique_ptr<TileSet> tileSet);

    // Getters and setters.
    int GetWidth();
    int GetHeight();
    int GetDepth();
    void SetTileSet(std::unique_ptr<TileSet> tileSet);

    // Loads a tile map from tile configuration file.
    void Load(std::string file);

    // Checks whether the given indices are within bounds.
    bool IsValidIndex(int x, int y, int z);

    // Finds the tile reference.
    int& At(int x, int y, int z = 0);

    // Prints tile map to standard output.
    void Print();

    // Parallax scrolling makes each layer move with different speed. Higher
    // layers will move faster than lower layers.
    Point ApplyParallax(int layer, const Point& tilePoint,
        const Point& cameraPoint);

    // Render a single map layer.
    void RenderLayer(int layer, const Point& cameraPoint);

    // Render all map layers.
    void Render(const Point& cameraPoint);

    // Render the first layer only.
    void RenderBaseLayer(const Point& cameraPoint);

    // Render all layers above the first one.
    void RenderUpperLayers(const Point& cameraPoint);

  private:
    // Parser for getting tile map definition from a file.
    TileMapParser tileMapParser;

    // Tile map stored as a vector structure for performance purposes.
    std::vector<int> tileMatrix;

    // Tile set in use.
    std::unique_ptr<TileSet> tileSet;

    // Tile map size defitions.
    int width;
    int height;
    int depth;
};

#endif // TILE_MAP_H_