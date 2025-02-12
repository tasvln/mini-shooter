#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

using namespace std;

namespace txt
{
  class Texture
  {
  private:
    SDL_Texture *mTexture;

    int mWidth;
    int mHeight;

  public:
    // constructors
    Texture();
    ~Texture();

    // getters
    int getWidth() const;
    int getHeight() const;

    // modifiers
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMode(SDL_BlendMode blending);
    void setAlpha(Uint8 alpha);

    // functions
    bool loadFromFile(string path, SDL_Renderer *renderer);
    void render(int x, int y, SDL_Renderer *renderer, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void clear();
  };
}