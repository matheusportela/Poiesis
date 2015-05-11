// @file   Resources.cpp
// @author Matheus Vieira Portela
// @date   10/04/2015
//
// @brief Resource manager implementation

#include "Resources.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;

bool Resources::HasImage(std::string file)
{
    return (Resources::imageTable.find(file) != Resources::imageTable.end());
}

SDL_Texture* Resources::LoadImage(std::string file)
{
    SDL_Texture* texture;
    texture = IMG_LoadTexture(Game::GetInstance()->GetRenderer(), file.c_str());

    if (!texture)
    {
        std::cerr << "ERROR [Resources] Could not load image " << file
                  << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        exit(1);
    }

    // Places a successfully allocated texture into image table.
    Resources::imageTable[file] = texture;
    
    return texture;
}

SDL_Texture* Resources::GetImage(std::string file)
{
    if (HasImage(file))
        return Resources::imageTable[file];
    else
        return LoadImage(file);
}

void Resources::ClearImages()
{
    SDL_Texture* texture;
    std::unordered_map<std::string, SDL_Texture*>::iterator it;

    while (Resources::imageTable.size() != 0)
    {
        it = Resources::imageTable.begin();
        texture = it->second;
        SDL_DestroyTexture(texture);
        Resources::imageTable.erase(it->first);
    }
}