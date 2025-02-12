#include "Camera.h"

namespace cam
{
  Camera::Camera(int w, int h)
  {
    mWidth = w;
    mHeight = h;
    mX = 0;
    mY = 0;
  }

  int Camera::getX() const
  {
    return this->mX;
  }

  int Camera::getY() const
  {
    return this->mY;
  }

  int Camera::getWidth() const
  {
    return this->mWidth;
  }

  int Camera::getHeight() const
  {
    return this->mHeight;
  }

  void Camera::cycle(int pX, int pY, int mapW, int mapH)
  {
    mX = pX - mWidth / 2;
    mY = pY - mHeight / 2;

    if (mX < 0)
      mX = 0;
    if (mY < 0)
      mY = 0;
    if (mX + mWidth > mapW)
      mX = mapW - mWidth;
    if (mY + mHeight > mapH)
      mY = mapH - mHeight;
  }

  SDL_Rect Camera::getViewPort()
  {
    SDL_Rect viewport = {mX, mY, mWidth, mHeight};
    return viewport;
  }
}