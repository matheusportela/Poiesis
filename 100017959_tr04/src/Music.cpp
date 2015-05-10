// @file   Music.cpp
// @author Matheus Vieira Portela
// @date   10/05/2015
//
// @brief Music playing class.

#include "Music.h"
#include "Resources.h"

Music::Music() : music(NULL)
{
}


Music::Music(std::string file) : Music()
{
    Open(file);
}


void Music::Open(std::string file)
{
    music = Resources::GetMusic(file);
}


bool Music::IsOpen() const
{
    return (music != NULL);
}


void Music::Play(int times)
{
    Mix_PlayMusic(music, times);
}


void Music::Stop()
{
    Mix_FadeOutMusic(FADE_OUT_TIME);
}