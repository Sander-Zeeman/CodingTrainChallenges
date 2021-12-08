#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

typedef struct {
  Vec2 pos;
} Star;

Star createStar() {
  float x = rand() % WIDTH/2 + WIDTH/4;
  float y = rand() % HEIGHT/2 + HEIGHT/4;

  return (Star) {.pos={.x=x, .y=y}};
}

Star *generateStars(uint32_t *number_of_stars) {
  *number_of_stars = 120;
  Star *stars = malloc(*number_of_stars * sizeof(Star));

  for (uint32_t i = 0; i < *number_of_stars; i++)
    stars[i] = createStar();

  return stars;
}

void update(Star *stars, uint32_t size) {
  Vec2 center = {.x = WIDTH / 2, .y = HEIGHT / 2};
  for (uint32_t i = 0; i < size; i++) {
    stars[i].pos = vec2_add(stars[i].pos, vec2_mult(vec2_sub(stars[i].pos, center), 0.02));

    if (
      stars[i].pos.x > WIDTH ||
      stars[i].pos.y > HEIGHT ||
      stars[i].pos.x < 0 ||
      stars[i].pos.y < 0
    )
      stars[i] = createStar();
  }
}

void draw(SDL_Renderer *renderer, Star *stars, uint32_t size) {
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);

  uint32_t maxDist = (WIDTH/2 * WIDTH/2) + (HEIGHT/2 * HEIGHT/2);
  for (uint32_t i = 0; i < size; i++) {
    double x_dist = (stars[i].pos.x - WIDTH/2) * (stars[i].pos.x - WIDTH/2);
    double y_dist = (stars[i].pos.y - HEIGHT/2) * (stars[i].pos.y - HEIGHT/2);
    double dist = x_dist + y_dist;

    int r = 1 + dist * 4 / maxDist;

    filledCircleColor(renderer, stars[i].pos.x, stars[i].pos.y, r, 0xFFFFFFFF);
  }

  SDL_RenderPresent(renderer);
}

int main() {
  time_t t;
  srand((unsigned) time(&t));
 
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

  SDL_SetWindowTitle(window, "Starfield");

  uint32_t size;
  Star *stars = generateStars(&size);

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

    update(stars, size);
    draw(renderer, stars, size);

    SDL_Delay(1000.0f / 60);
  }

  SDL_Quit();
  
  free(stars);
  return 0;
}