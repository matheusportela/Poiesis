// @file   TileSet.cpp
// @author Matheus Vieira Portela
// @date   08/04/2015
//
// @brief Tile container implementation

#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file) :
    tileWidth(tileWidth), tileHeight(tileHeight)
{
    tileSprite = new Sprite(file);

    // Calculates the number of columns and rows in the given tile set image.
    columns = tileSprite->GetWidth() / tileWidth;
    rows = tileSprite->GetHeight() / tileHeight;
}

TileSet::~TileSet()
{
    delete tileSprite;
}

int TileSet::GetTileWidth()
{
    return tileWidth;
}

int TileSet::GetTileHeight()
{
    return tileHeight;
}

bool TileSet::IsValidIndex(int index)
{
    return ((index < rows*columns) && (index >= 0));
}

void TileSet::Render(int index, const Point& point)
{
    if (!IsValidIndex(index))
    {
        LOG_E("[TileSet] Index " << index << " out of bounds. "
            << "Columns: " <<  columns << " Rows: " << rows);
        exit(1);
    }

    // It is necessary to convert from index to (x, y) image coordinates for
    // clipping.
    int tile_x = (index % columns)*tileWidth;
    int tile_y = (index / columns)*tileHeight;
    Point tilePoint(tile_x, tile_y);

    tileSprite->SetClip(tilePoint, tileWidth, tileHeight);
    tileSprite->Render(point);
}