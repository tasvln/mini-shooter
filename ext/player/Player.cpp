#include "Player.h"

namespace plyr
{
  Player::Player(int x, int y, int w, int h, int vel, int velX, int velY, SDL_Color color)
  {
    mWidth = w;
    mHeight = h;
    mY = y;
    mX = x;
    mMoveUp = false;
    mMoveDown = false;
    mMoveLeft = false;
    mMoveRight = false;
    mVel = vel;
    mColor = color;
  }

  int Player::getX() const
  {
    return this->mX;
  }

  int Player::getY() const
  {
    return this->mY;
  }

  int Player::getWidth() const
  {
    return this->mWidth;
  }

  int Player::getHeight() const
  {
    return this->mHeight;
  }

  void Player::render(SDL_Renderer *renderer)
  {
    if (renderer)
    {
      SDL_SetRenderDrawColor(renderer, mColor.r, mColor.g, mColor.b, mColor.a);

      SDL_Rect rect = {mX, mY, mWidth, mHeight};

      SDL_RenderFillRect(renderer, &rect);
    }
  }

  void Player::eventHandler(SDL_Event &e)
  {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
      switch (e.key.keysym.sym)
      {
      case SDLK_UP:
        mMoveUp = true;
        break;
      case SDLK_DOWN:
        mMoveDown = true;
        break;
      case SDLK_LEFT:
        mMoveLeft = true;
        break;
      case SDLK_RIGHT:
        mMoveRight = true;
        break;
      }
    }
    else if (e.type == SDL_KEYUP)
    {
      switch (e.key.keysym.sym)
      {
      case SDLK_UP:
        mMoveUp = false;
        break;
      case SDLK_DOWN:
        mMoveDown = false;
        break;
      case SDLK_LEFT:
        mMoveLeft = false;
        break;
      case SDLK_RIGHT:
        mMoveRight = false;
        break;
      }
    }
  }

  void Player::checkCollision(const vector<SDL_Rect> &walls)
  {
    SDL_Rect playerRect = {mX, mY, mWidth, mHeight};

    for (const auto &wall : walls)
    {
      if (SDL_HasIntersection(&playerRect, &wall))
      {
        if (mMoveUp)
          mY += mVel; // Prevent moving up into the wall
        if (mMoveDown)
          mY -= mVel; // Prevent moving down into the wall
        if (mMoveLeft)
          mX += mVel; // Prevent moving left into the wall
        if (mMoveRight)
          mX -= mVel;
      }
    }
  }

  void Player::move(const int sW, const int sH, const std::vector<SDL_Rect> &walls)
  {
    if (mMoveUp)
      mY -= mVel;
    if (mMoveDown)
      mY += mVel;
    if (mMoveLeft)
      mX -= mVel;
    if (mMoveRight)
      mX += mVel;

    checkCollision(walls);

    if (mX < 0)
      mX = 0;
    if (mX + mWidth > sW)
      mX = sW - mWidth;

    if (mY < 0)
      mY = 0;
    if (mY + mHeight > sH)
      mY = sH - mHeight;
  }
}