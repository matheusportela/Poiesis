// @file   AnimatedSprite.h
// @author Matheus Vieira Portela
// @date   01/05/2015
//
// @brief Allows sequential rendering of sprites from a single image file.
//
// AnimatedSprite provides sequential usage of sprites that are located in a
// single image, creating an effect of animation.

#ifndef ANIMATED_SPRITE_H_
#define ANIMATED_SPRITE_H_

#include <string>

#include "Sprite.h"

class AnimatedSprite : public Sprite
{
  public:
    // Initializes a sprite sheet with an image file, the number of frames and
    // the time each frame will be displayed.
    AnimatedSprite(std::string file, int numFrames, float frameTime);

    void UpdateElapsedTime(float dt);

    void ResetElapsedTime();

    bool IsFrameFinished();

    void UpdateCurrentFrame();

    void RenderNextFrame();

    void SetFrameClip();

    // Updates the sprite to the next frame.
    void Update(float dt);

  private:
    // Frame that is currently being displayed.
    int currentFrame;

    // Number of frames in the sprite sheet file.
    int numFrames;

    // Amount of time each frame will be displayed, in seconds.
    float frameTime;

    // Elapsed time since the sprite frame beginning, in seconds.
    float elapsedTime;

    // Width of each frame, in pixels.
    int frameWidth;
};

#endif // ANIMATED_SPRITE_H_