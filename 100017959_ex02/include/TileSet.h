// @file   TileSet.h
// @author Matheus Vieira Portela
// @date   08/04/2015
//
// @brief Tile container
//
// Definition of class for storing tile used when renderizing the game map.

#ifndef TILE_SET_H_
#define TILE_SET_H_

#include <string>

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

    // Renderizes the sprite in the given position for a valid index.
    void Render(int index, Point& point);

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