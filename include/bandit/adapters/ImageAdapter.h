// Interface to image related methods.

#ifndef IMAGE_ADAPTER_H_
#define IMAGE_ADAPTER_H_

#include <string>

class ImageAdapter
{
  public:
    ImageAdapter() : width(0), height(0) {}
    virtual ~ImageAdapter() {}
    virtual float GetWidth() { return width; };
    virtual float GetHeight() { return height; };

    // Loads an image from a specified file to the memory.
    virtual void Load(std::string file) = 0;

    // Unloads a previously loaded image from memory.
    virtual void Unload() = 0;

    // Checks whether an image has been loaded with this instance.
    virtual bool IsLoaded() = 0;

  protected:
    // Image width in file.
    float width;

    // Image height in file.
    float height;
};

#endif // IMAGE_ADAPTER_H_