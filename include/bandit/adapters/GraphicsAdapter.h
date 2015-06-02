// Interface to graphics related methods.

#ifndef GRAPHICS_ADAPTER_H_
#define GRAPHICS_ADAPTER_H_

#include <string>

class GraphicsAdapter
{
  public:
    virtual ~GraphicsAdapter() {}

    // Creates a new window for displaying images. This window should be unique
    // for all graphics adapter instances.
    virtual void CreateWindow(std::string title, int width, int height) = 0;

    // Destroys current window.
    virtual void DestroyWindow() = 0;

    // Loads an image from a specified file to the memory.
    virtual void LoadImage(std::string file) = 0;

    // Unloads a previously loaded image from memory.
    virtual void UnloadImage(std::string file) = 0;

    // Checks whether an image has been loaded with this instance.
    virtual bool IsLoaded(std::string file) = 0;

    // GPU and rendering related initializations that must be executed every
    // rendering cycle.
    virtual void InitRendering() = 0;

    // Renders the image to a previously defined window in the given x, y
    // coordinates.
    virtual void RenderImage(std::string file, int x, int y, float scale = 1) = 0;

    // Renders the image with respect to the center position given by the x, y
    // coordinates.
    virtual void RenderCenteredImage(std::string file, int x, int y, float scale = 1) = 0;

    // GPU and rendering related finalizations that must be executed every
    // rendering cycle.
    virtual void FinishRendering() = 0;
};

#endif // GRAPHICS_ADAPTER_H_