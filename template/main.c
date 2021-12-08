#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#define WIDTH 800
#define HEIGHT 800

typedef struct {
  float x, y;
} Vec2;

Vec2 vec2_add(Vec2 o, Vec2 add) {
  float x = o.x + add.x;
  float y = o.y + add.y;
  return (Vec2) {.x=x, .y=y};
}

Vec2 vec2_sub(Vec2 o, Vec2 sub) {
  float x = o.x - sub.x;
  float y = o.y - sub.y;
  return (Vec2) {.x=x, .y=y};
}

Vec2 vec2_mult(Vec2 o, float mult) {
  float x = o.x * mult;
  float y = o.y * mult;
  return (Vec2) {.x=x, .y=y};
}

void update() {}

void draw(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);

  SDL_RenderPresent(renderer);
}

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) > 0) {
    fprintf(stderr, "Could not initialize SDL!\n");
    exit(1);
  }

  SDL_Window *window;
  SDL_Renderer *renderer;

  if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) > 0) {
    fprintf(stderr, "Could not create window and/or renderer!\n");
    exit(1);
  }

  SDL_SetWindowTitle(window, "");

  uint8_t quit = 0;
  while (!quit) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          quit = 1;
          break;
      }
    }
    if (quit) break;

    update();
    draw(renderer);

    SDL_Delay(1000.0f / 60);
  }

  SDL_Quit();
  
  return 0;
}
