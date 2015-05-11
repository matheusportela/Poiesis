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
    // Initializes a sprite sheet with an image file, the number of frames,
    // the duration each frame will be displayed and whether the animation
    // repeats after reaching the last frame.
    AnimatedSprite(std::string file, int numFrames, float frameDuration,
        bool repeat=true);

    // Adjust sprite width to compensate frames. For instance, if each frame
    // has 100px width, a sprite with 3 frames will have a 300px width. We
    // correct this here to avoid anomallies.
    void AdjustWidth();

    // Updates elapsed time since the beginning of the current frame.
    void UpdateElapsedTime(float dt);

    // Resets elapsed time accumulator.
    void ResetElapsedTime();

    // Checks whether the current frame is finished and should be replaced by
    // a new one.
    bool IsFrameFinished();

    // Updates the current frame.
    void UpdateCurrentFrame();

    // Sets the clipping rectangle to render the next animation frame. 
    void SetFrameClip();

    // Prepares everything necessary to render the next animation frame.
    void RenderNextFrame();

    // Updates the sprite to the next frame.
    void Update(float dt);

  private:
    // Frame that is currently being displayed.
    int currentFrame;

    // Number of frames in the sprite sheet file.
    int numFrames;

    // Amount of time each frame will be displayed, in seconds.
    float frameDuration;

    // Holds whether the animation will repeat after reaching the last frame.
    bool repeat;

    // Elapsed time since the sprite frame beginning, in seconds.
    float elapsedTime;
};

#endif // ANIMATED_SPRITE_H_