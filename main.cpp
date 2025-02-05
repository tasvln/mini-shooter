#include "main.h"

bool loadMedia()
{
  bool loading = true;

  gFont = TTF_OpenFont("lib/inter.ttf", 28);

  if (gFont == NULL)
  {
    printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
    loading = false;
  }

  return loading;
}

void closeApp()
{
  TTF_CloseFont(gFont);
  gFont = NULL;

  TTF_Quit();
  SDL_Quit();
}

int main(int argc, char *argv[])
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  }
  else
  {
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
      printf("Warning: Linear texture filtering not enabled!");
    }

    if (TTF_Init() == -1)
    {
      printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    }

    Window window("MINI SHOOTER", SCREEN_WIDTH, SCREEN_HEIGHT);

    if (!window.init())
    {
      printf("Failed to initialize Window!\n");
    }
    else
    {

      if (!loadMedia())
      {
        printf("Failed to load Images/Textures!\n");
      }
      else
      {
        int score = 0;
        bool isRunning = true;
        bool gameOver = false;
        SDL_Event evt;

        while (isRunning)
        {
          while (SDL_PollEvent(&evt) != 0)
          {
            if (evt.type == SDL_QUIT)
            {
              isRunning = false;
            }

            // if (gameOver && evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_r)
            // {
            //   gameOver = false;
            //   score = 0;
            // }
          }

          window.clearScreen(0xFF, 0xFF, 0xFF, 0xFF);

          window.presentRender();
        }
      }
    }
  }

  closeApp();

  return 0;
}