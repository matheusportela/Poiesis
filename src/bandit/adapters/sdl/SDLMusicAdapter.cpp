#include "bandit/adapters/sdl/SDLMusicAdapter.h"

std::unordered_map<std::string, Mix_Music*> SDLMusicAdapter::musicsTable;

SDLMusicAdapter::~SDLMusicAdapter()
{
    UnloadAllMusics();
}

void SDLMusicAdapter::Load(std::string file)
{
    Mix_Music* music = Mix_LoadMUS(file.c_str());

    if (!music)
    {
        std::cerr << "[SDLMusicAdapter] Could not load music file \"" << file
            << "\". " << SDL_GetError() << std::endl;
        exit(1);
    }

    musicsTable[file] = music;
}

void SDLMusicAdapter::Unload(std::string file)
{
    if (IsLoaded(file))
    {
        Mix_FreeMusic(musicsTable[file]);
        musicsTable.erase(file);
    }
}

void SDLMusicAdapter::UnloadAllMusics()
{
    Mix_Music* music;
    std::unordered_map<std::string, Mix_Music*>::iterator it;

    while (musicsTable.size() != 0)
    {
        it = musicsTable.begin();
        music = it->second;
        Mix_FreeMusic(music);
        musicsTable.erase(it->first);
    }
}

bool SDLMusicAdapter::IsLoaded(std::string file)
{
    return (musicsTable.find(file) != musicsTable.end());
}

void SDLMusicAdapter::Play(std::string file, int repetitions)
{
    if (!IsLoaded(file))
    {
        std::cerr << "[SDLMusicAdapter] Cannot play music without loading it "
            << "first." << std::endl;
        exit(1);
    }

    Mix_PlayMusic(musicsTable[file], repetitions);
}

void SDLMusicAdapter::Stop(std::string file)
{
    if (!IsLoaded(file))
    {
        std::cerr << "[SDLMusicAdapter] Cannot stop music without loading it "
            << "first." << std::endl;
        exit(1);
    }
    
    Mix_FadeOutMusic(FADE_OUT_TIME);
}