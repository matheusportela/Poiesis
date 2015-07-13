// Component that holds sprite information to be rendered.

#ifndef SPRITE_COMPONENT_H_
#define SPRITE_COMPONENT_H_

#include <string>

#include "bandit/Engine.h"

class SpriteComponent : public Component
{
  public:
    SpriteComponent(std::string filename, Vector position = Vector(0, 0),
        float rotation = 0, float rotationSpeed = 0, bool centered = true,
        float scale = 1, int numFrames = 1, float frameDuration = 0,
        bool repeat = true, bool multipleFiles = false);
    std::string GetComponentClass();

    std::string GetFilename();
    void SetFilename(std::string filename);

    Vector GetPosition();
    void SetPosition(Vector position);

    float GetRotation();
    void SetRotation(float rotation);

    float GetRotationSpeed();
    void SetRotationSpeed(float rotationSpeed);

    bool GetCentered();
    void SetCentered(bool centered);

    float GetBaseScale();
    void SetBaseScale(float baseScale);

    float GetScale();
    void SetScale(float scale);

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

    bool GetMultipleFiles();
    void SetMultipleFiles(bool multipleFiles);

  private:
    // Holds the file containing the image to be displayed.
    std::string filename;

    // Holds the position relative to the entity to render the sprite.
    Vector position;

    // Holds the rotation, in radians, the image must be displayed.
    float rotation;

    // Holds the speed, in radians/second, with which the image must be rotated.
    float rotationSpeed;

    // Holds whether the image should be displayed centered.
    bool centered;

    // Holds the initial scale.
    float baseScale;

    // Holds the scale factor to zoom the image in or out.
    float scale;

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

    // Holds whether the animation spreads through multiple files.
    bool multipleFiles;
};

#endif // SPRITE_COMPONENT_H_