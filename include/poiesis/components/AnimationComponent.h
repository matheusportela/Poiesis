// Component that holds sprite animation information to be rendered.

#ifndef ANIMATION_COMPONENT_H_
#define ANIMATION_COMPONENT_H_

#include <string>

#include "poiesis/components/SpriteComponent.h"

class AnimationComponent : public SpriteComponent
{
  public:
    AnimationComponent(std::string filename, int numFrames, float frameDuration,
        bool repeat = true, Vector position = Vector(0, 0),
        bool centered = true, float scale = 1);
    std::string GetComponentClass();

    int GetCurrentFrame();
    void SetCurrentFrame(int currentFrame);

    int GetNumFrames();
    void SetNumFrames(int numFrames);

    float GetFrameDuration();
    void SetFrameDuration(float frameDuration);

    bool GetRepeat();
    void SetRepeat(bool repeat);

    float GetElapsedTime();
    void SetElapsedTime(float elapsedTime);

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

#endif // ANIMATION_COMPONENT_H_