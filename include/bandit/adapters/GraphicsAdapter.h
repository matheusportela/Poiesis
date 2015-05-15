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
    virtual void UnloadImage() = 0;

    // Checks whether an image has been loaded with this instance.
    virtual bool IsLoaded() = 0;

    // Renders the image to a previously defined window.
    virtual void RenderImage() = 0;
};

#endif // GRAPHICS_ADAPTER_H_