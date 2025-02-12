#include "Texture.h"

namespace txt
{
  Texture::Texture()
  {
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
  }

  Texture::~Texture()
  {
    clear();
  }

  int Texture::getWidth() const
  {
    return mWidth;
  }

  int Texture::getHeight() const
  {
    return mHeight;
  }

  void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue)
  {
    SDL_SetTextureColorMod(mTexture, red, green, blue);
  }

  void Texture::setBlendMode(SDL_BlendMode blending)
  {
    SDL_SetTextureBlendMode(mTexture, blending);
  }

  void Texture::setAlpha(Uint8 alpha)
  {
    SDL_SetTextureAlphaMod(mTexture, alpha);
  }

  void Texture::render(int x, int y, SDL_Renderer *renderer, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
  {
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    if (clip != NULL)
    {
      renderQuad.w = clip->w;
      renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
  }

  bool Texture::loadFromFile(string path, SDL_Renderer *renderer)
  {
    clear();

    SDL_Texture *newTexture = NULL;

    SDL_Surface *loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL)
    {
      printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
      SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

      newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

      if (newTexture == NULL)
      {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
      }
      else
      {
        mWidth = loadedSurface->w;
        mHeight = loadedSurface->h;
      }

      SDL_FreeSurface(loadedSurface);
    }

    mTexture = newTexture;
    return mTexture != NULL;
  }

  void Texture::clear()
  {
    if (mTexture != NULL)
    {
      SDL_DestroyTexture(mTexture);
      mTexture = NULL;
    }

    mWidth = 0;
    mHeight = 0;
  }
}