// @file   TileSet.h
// @author Matheus Vieira Portela
// @date   08/04/2015
//
// @brief Tile container
//
// Tile set is an unique image which can be cut in several small rectangles in
// order to render tiles on the screen.
// Each tile is accessed through it's index value, which accesses the tile set
// image as a 1-dimensional vector, such as in the scheme below.
//  ------------------------
// |  0 |  1 |  2 |  3 |  4 |
//  ------------------------
// |  5 |  6 |  7 |  8 |  9 |
//  ------------------------
// | 10 | 11 | 12 | 13 | 14 |
//  ------------------------

#ifndef TILE_SET_H_
#define TILE_SET_H_

#include <string>

#include "Logger.h"
#include "Point.h"
#include "Sprite.h"

class Sprite;

class TileSet
{
  public:
    // Initializes the tile set.
    TileSet(int tileWidth, int tileHeight, std::string file);

    // Destroys the tile set.
    ~TileSet();

    // Getters and setters
    int GetTileWidth();
    int GetTileHeight();

    // Checks whether the tile index is within bounds.
    bool IsValidIndex(int index);

    // Renderizes the indexed tile in the given window position.
    void Render(int index, Point point);

  private:
    // Tile sprite.
    Sprite* tileSprite;

    // Tile set size.
    int rows;
    int columns;

    // Tile sprite size.
    int tileWidth;
    int tileHeight;
};

#endif // TILE_SET_H_