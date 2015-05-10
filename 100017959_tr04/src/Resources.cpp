// @file   Resources.cpp
// @author Matheus Vieira Portela
// @date   10/04/2015
//
// @brief Resource manager implementation

#include "Resources.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundEffectTable;

bool Resources::HasImage(std::string file)
{
    return (Resources::imageTable.find(file) != Resources::imageTable.end());
}

SDL_Texture* Resources::LoadImage(std::string file)
{
    SDL_Texture* texture =
        IMG_LoadTexture(Game::GetInstance()->GetRenderer(), file.c_str());

    if (!texture)
    {
        LOG_E("[Resources] Could not load image \"" << file << "\". "
            << SDL_GetError());
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

bool Resources::HasMusic(std::string file)
{
    return (Resources::musicTable.find(file) != Resources::musicTable.end());
}

Mix_Music* Resources::LoadMusic(std::string file)
{
    Mix_Music* music = Mix_LoadMUS(file.c_str());

    if (!music)
    {
        LOG_E("[Resources] Could not load music \"" << file << "\". "
            << SDL_GetError());
        exit(1);
    }

    // Places a successfully allocated music into music table.
    Resources::musicTable[file] = music;
    
    return music;
}

Mix_Music* Resources::GetMusic(std::string file)
{
    if (HasMusic(file))
        return Resources::musicTable[file];
    else
        return LoadMusic(file);
}

void Resources::ClearMusics()
{
    Mix_Music* music;
    std::unordered_map<std::string, Mix_Music*>::iterator it;

    while (Resources::musicTable.size() != 0)
    {
        it = Resources::musicTable.begin();
        music = it->second;
        Mix_FreeMusic(music);
        Resources::musicTable.erase(it->first);
    }
}

bool Resources::HasSoundEffect(std::string file)
{
    return (Resources::soundEffectTable.find(file)
        != Resources::soundEffectTable.end());
}

Mix_Chunk* Resources::LoadSoundEffect(std::string file)
{
    Mix_Chunk* soundEffect = Mix_LoadWAV(file.c_str());

    if (!soundEffect)
    {
        LOG_E("[Resources] Could not load sound effects \"" << file << "\". "
            << SDL_GetError());
        exit(1);
    }

    // Places a successfully allocated music into music table.
    Resources::soundEffectTable[file] = soundEffect;
    
    return soundEffect;
}

Mix_Chunk* Resources::GetSoundEffect(std::string file)
{
    if (HasSoundEffect(file))
        return Resources::soundEffectTable[file];
    else
        return LoadSoundEffect(file);
}

void Resources::ClearSoundEffects()
{
    Mix_Chunk* soundEffect;
    std::unordered_map<std::string, Mix_Chunk*>::iterator it;

    while (Resources::soundEffectTable.size() != 0)
    {
        it = Resources::soundEffectTable.begin();
        soundEffect = it->second;
        Mix_FreeChunk(soundEffect);
        Resources::soundEffectTable.erase(it->first);
    }
}