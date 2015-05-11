// @file   TileMap.cpp
// @author Matheus Vieira Portela
// @date   08/04/2015
//
// @brief 3 dimensional matrix representing the game map

#include "TileMap.h"

TileMap::TileMap(std::string file, std::unique_ptr<TileSet> tileSet) :
    tileSet(std::move(tileSet))
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

void TileMap::SetTileSet(std::unique_ptr<TileSet> tileSet)
{
    this->tileSet = std::move(tileSet);
}

void TileMap::Load(std::string file)
{
    LOG_I("Loading tile map: " << file);

    tileMapParser.Parse(file);
    width = tileMapParser.GetParsedWidth();
    height = tileMapParser.GetParsedHeight();
    depth = tileMapParser.GetParsedDepth();
    tileMatrix = tileMapParser.GetParsedTileMap();
    Print();
}

bool TileMap::IsValidIndex(int x, int y, int z)
{
    return ((x < width) && (y < height) && (z < depth));
}


int& TileMap::At(int x, int y, int z)
{
    if (!IsValidIndex(x, y, z))
    {
        LOG_E("[TileMap] Index (" << x << ", " << y << ", " << z
            << ") out of bounds. Max: (" << width << ", " << height << ", "
            << depth << ")");
        exit(1);
    }

    return tileMatrix[x + y*width + z*width*height];
}

void TileMap::Print()
{
    std::stringstream map_line;

    LOG_D("Tile map");
    LOG_D("Width: " << tileMapParser.GetParsedWidth());
    LOG_D("Height: " << tileMapParser.GetParsedHeight());
    LOG_D("Depth: " << tileMapParser.GetParsedDepth());
    LOG_D("Map:");

    for (int z = 0; z < depth; ++z)
    {
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                // Print with two digits
                map_line << std::setw(2) << At(x, y, z) << " ";
            }

            LOG_D(map_line.str());
            map_line.str("");
        }

        LOG_D("");
    }
}

Point TileMap::ApplyParallax(int layer, const Point& tilePoint,
    const Point& cameraPoint)
{
    // Layers start at zero but we still want to move the first layer.
    int speed = (layer + 1)*CFG_GETI("PARALLAX_SPEED");

    Point parallax_point = cameraPoint;
    parallax_point.Multiply(speed);
    parallax_point.Add(tilePoint);

    return parallax_point;
}

void TileMap::RenderLayer(int layer, const Point& cameraPoint)
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

void TileMap::Render(const Point& cameraPoint)
{
    for (int z = 0; z < depth; ++z)
        RenderLayer(z, cameraPoint);
}

void TileMap::RenderBaseLayer(const Point& cameraPoint)
{
    RenderLayer(0, cameraPoint);
}

void TileMap::RenderUpperLayers(const Point& cameraPoint)
{
    for (int z = 1; z < depth; ++z)
        RenderLayer(z, cameraPoint);
}