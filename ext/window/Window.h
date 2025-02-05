#include <SDL.h>
#include <string>
#include <iostream>

using namespace std;

namespace wdw
{
  class Window
  {
  public:
    // constructors
    Window();
    Window(const string &title, int w, int h);
    ~Window();

    // modifiers
    bool setWindowTitle(string &title);

    // getters
    int getWidth();
    int getHeight();
    string getTitle();

    // functions
    bool init();
    void free();
    void clearScreen(int r, int g, int b, int a);
    void presentRender();

    SDL_Renderer *getRenderer() const;

  private:
    string mTitle;
    int mWidth;
    int mHeight;

    SDL_Window *window;
    SDL_Renderer *renderer;
  };
};