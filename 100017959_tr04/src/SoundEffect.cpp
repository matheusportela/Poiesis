// @file   SoundEffect.cpp
// @author Matheus Vieira Portela
// @date   10/05/2015
//
// @brief Sound effect playing class.

#include "SoundEffect.h"
#include "Resources.h"

SoundEffect::SoundEffect() : soundEffect(NULL)
{
}


SoundEffect::SoundEffect(std::string file) : SoundEffect()
{
    Open(file);
}


void SoundEffect::Open(std::string file)
{
    soundEffect = Resources::GetSoundEffect(file);
}


bool SoundEffect::IsOpen() const
{
    return (soundEffect != NULL);
}


void SoundEffect::Play(int times)
{
    channel = Mix_PlayChannel(DEFAULT_CHANNEL, soundEffect, times);
}


void SoundEffect::Stop()
{
    Mix_HaltChannel(channel);
}