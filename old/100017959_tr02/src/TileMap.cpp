// @file   TileMap.cpp
// @author Matheus Vieira Portela
// @date   08/04/2015
//
// @brief 3 dimensional matrix representing the game map

#include "TileMap.h"

TileMap::TileMap(std::string file, TileSet* tileSet) : tileSet(tileSet)
{
    Load(file);
}

int TileMap::GetWidth()
{
    return width;
}

int TileMap::GetHeight()
{
    return height;
}

int TileMap::GetDepth()
{
    return depth;
}

void TileMap::SetTileSet(TileSet* tileSet)
{
    this->tileSet = tileSet;
}

void TileMap::Load(std::string file)
{
    tileMapParser.Parse(file);
    width = tileMapParser.GetParsedWidth();
    height = tileMapParser.GetParsedHeight();
    depth = tileMapParser.GetParsedDepth();
    tileMatrix = tileMapParser.GetParsedTileMap();
}

bool TileMap::IsValidIndex(int x, int y, int z)
{
    return ((x < width) && (y < height) && (z < depth));
}


int& TileMap::At(int x, int y, int z)
{
    if (!IsValidIndex(x, y, z))
    {
        std::cerr << "ERROR [TileMap] Index (" << x << ", " << y << ", " << z
                  << ") out of bounds. Max: (" << width << ", " << height << ", "
                  << depth << ")" << std::endl;
        exit(1);
    }

    return tileMatrix[x + y*width + z*width*height];
}

void TileMap::Print()
{
    std::cout << "Width: " << tileMapParser.GetParsedWidth() << std::endl;
    std::cout << "Height: " << tileMapParser.GetParsedHeight() << std::endl;
    std::cout << "Depth: " << tileMapParser.GetParsedDepth() << std::endl;
    std::cout << "Map:" << std::endl;

    for (int z = 0; z < depth; ++z)
    {
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                // Print with two digits
                std::cout << std::setw(2) << At(x, y, z) << " ";
            }

            std::cout << std::endl;
        }

        std::cout << std::endl;
    }
}

Point TileMap::ApplyParallax(int layer, Point tilePoint, Point cameraPoint)
{
    Point parallax_point;

    // Layers start at zero but we still want to move the first layer.
    int speed = (layer + 1)*CFG_GETI("PARALLAX_SPEED");

    parallax_point.Set(cameraPoint);
    parallax_point.Multiply(speed);
    parallax_point.Add(tilePoint);

    return parallax_point;
}

void TileMap::RenderLayer(int layer, Point& cameraPoint)
{
    Point tile_point;
    int tile_width = tileSet->GetTileWidth();
    int tile_height = tileSet->GetTileHeight();
    int tile_index;

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            tile_index = At(x, y, layer);

            // Ignore all tiles marked as -1
            if (tile_index == -1)
                continue;

            tile_point.Set(x*tile_width, y*tile_height);

            if (CFG_GETB("PARALLAX_ON"))
                tile_point = ApplyParallax(layer, tile_point, cameraPoint);
            else
                tile_point.Add(cameraPoint);

            tileSet->Render(tile_index, tile_point);
        }
    }
}

void TileMap::Render(Point& cameraPoint)
{
    for (int z = 0; z < depth; ++z)
        RenderLayer(z, cameraPoint);
}