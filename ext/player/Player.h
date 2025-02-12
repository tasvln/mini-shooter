#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>

const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 17;

const int TILE_SIZE = 32;

using namespace std;

namespace plyr
{
  class Player
  {
  private:
    int mWidth;
    int mHeight;
    int mX;
    int mY;
    bool mMoveUp, mMoveDown, mMoveLeft, mMoveRight;
    int mVel;
    SDL_Color mColor;

  public:
    Player(int x, int y, int w, int h, int vel, int velX, int velY, SDL_Color mColor);

    // getters
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;

    // functions
    void render(SDL_Renderer *renderer);
    void eventHandler(SDL_Event &e);
    void checkCollision(const vector<SDL_Rect> &walls);
    void move(const int sW, const int sH, const std::vector<SDL_Rect> &walls);
  };
}