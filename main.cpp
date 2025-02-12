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

vector<SDL_Rect> getWalls()
{
  vector<SDL_Rect> walls;

  for (int row = 0; row < MAP_HEIGHT; row++)
  {
    for (int col = 0; col < MAP_WIDTH; col++)
    {
      if (map[row][col] == 1) // Wall detected
      {
        SDL_Rect wall = {col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE};
        walls.push_back(wall);
      }
    }
  }

  return walls;
}

void renderWalls(SDL_Renderer *renderer, const std::vector<SDL_Rect> &walls)
{
  for (const SDL_Rect &wall : walls)
  {
    SDL_Rect renderQuad = {wall.x, wall.y, wall.w, wall.h};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0); // Wall color (black)
    SDL_RenderFillRect(renderer, &renderQuad);
  }
}

void closeApp()
{
  TTF_CloseFont(gFont);
  gFont = NULL;

  TTF_Quit();
  SDL_Quit();
}

void drawMap(SDL_Renderer *renderer)
{
  for (int y = 0; y < MAP_HEIGHT; ++y)
  {
    for (int x = 0; x < MAP_WIDTH; ++x)
    {
      SDL_Rect tileRect = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};

      if (map[y][x] == 1)
      {
        // Draw black (non-playable) tile
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black
      }
      else
      {
        // Draw white (playable) tile
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
      }

      SDL_RenderFillRect(renderer, &tileRect);
    }
  }
}

void renderMiniMap(SDL_Renderer *renderer, int pX, int pY, const vector<SDL_Rect> &walls)
{
  SDL_Rect miniMapRect = {SCREEN_WIDTH - MINI_MAP_WIDTH, SCREEN_HEIGHT - MINI_MAP_HEIGHT, MINI_MAP_WIDTH, MINI_MAP_HEIGHT};
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &miniMapRect);

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black border
  SDL_RenderDrawRect(renderer, &miniMapRect);

  int pMiniMapW = scaleX * PLYR_SIZE;
  int pMiniMapH = scaleY * PLYR_SIZE;

  SDL_Rect pMiniMap = {SCREEN_WIDTH - MINI_MAP_WIDTH, SCREEN_HEIGHT - MINI_MAP_HEIGHT, pMiniMapW, pMiniMapH};
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
  SDL_RenderFillRect(renderer, &pMiniMap);

  // for (const auto &wall : walls)
  // {
  //   int wallMiniMapX = wall.x * scaleX;
  //   int wallMiniMapY = wall.y * scaleY;
  //   int wallMiniMapWidth = wall.w * scaleX;
  //   int wallMiniMapHeight = wall.h * scaleY;

  //   SDL_Rect miniWall = {wallMiniMapX, wallMiniMapY, wallMiniMapWidth, wallMiniMapHeight};
  //   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  //   SDL_RenderFillRect(renderer, &miniWall);
  // }
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

    SDL_Color plyrColor = {255, 0, 0};

    Window window("MINI SHOOTER", SCREEN_WIDTH, SCREEN_HEIGHT);

    Player player(window.getWidth() / 2, window.getHeight() / 2, PLYR_SIZE, PLYR_SIZE, 2, 0, 0, plyrColor);

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
        vector<SDL_Rect> walls = getWalls();
        bool isRunning = true;
        SDL_Event evt;

        while (isRunning)
        {
          while (SDL_PollEvent(&evt) != 0)
          {
            if (evt.type == SDL_QUIT)
            {
              isRunning = false;
            }

            player.eventHandler(evt);
          }

          player.move(window.getWidth(), window.getHeight(), walls);

          window.clearScreen(0xFF, 0xFF, 0xFF, 0xFF);

          renderWalls(window.getRenderer(), walls);

          player.render(window.getRenderer());

          // renderMiniMap(window.getRenderer(), player.getX(), player.getY(), walls);

          window.presentRender();
        }
      }
    }
  }

  closeApp();

  return 0;
}