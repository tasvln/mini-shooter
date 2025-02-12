
#ifndef CAMERA_H
#define CAMERA_H

#include <SDL.h>

namespace cam
{
  class Camera
  {
  private:
    int mWidth;
    int mHeight;
    int mX;
    int mY;

  public:
    Camera(int w, int h);

    // getters
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;

    // functions
    void cycle(int pX, int pY, int mapW, int mapH);
    SDL_Rect getViewPort();
  };
}

#endif // CAMERA_H