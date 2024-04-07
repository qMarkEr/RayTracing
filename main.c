#include "Constants.h"
#include "Objects.h"
#include "Other.h"
#include <SDL2/SDL.h>
#include <stdio.h>

int main() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) printf("u suck\n");
  SDL_Window *win = SDL_CreateWindow("backrooms",
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     WIDTH, HEIGHT, 0);
  
  FILE* f = fopen("/home/marker/RayTracingSDL/Assets/cube.obj", "r");
  object* shit = load_data(f);
  fclose(f);
  
  SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, WIDTH, HEIGHT, 32, SDL_PIXELFORMAT_RGBA8888);
  FillSurface(surface, BACKGROUND);
  double focal_length = 1 / SDL_tan(deg_to_rad(40) / 2.0);
  vec3 camera = { 0, 0, -1 };
  vec3 lo = { 0, 1, -1 };
  double z_buffer[WIDTH][HEIGHT];
  for (int i1 = 0; i1 < WIDTH; ++i1)
    memset(z_buffer[i1], 0.0, HEIGHT);

  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      // ray from -1 to 1 in both x and y dimensions
      vec3 ray = {(((double) j / (double) WIDTH) * 2.0 - 1.0) * WIDTH / HEIGHT,
                     ((double) (HEIGHT - i) / (double) HEIGHT) * 2.0 - 1.0,
                     focal_length};
      double coef = 0;
      int closest_hit = -1;
      vec3 intersection = {0, 0, 0};
      for (int k = 0; k < shit->count; ++k) {
        if (intersectTriangle(shit->trigs[k], &camera, &ray, &coef)) {
          vec3 mul_ray = mul_num(&ray, coef);
          intersection = add(&camera, &mul_ray);
          if (closest_hit == -1 || z_buffer[j][i] > intersection.z) {
            z_buffer[j][i] = intersection.z;
            closest_hit = k;
          }
        }
      }
      if (closest_hit != -1) {
        double lightness = dot(&lo, &shit->trigs[closest_hit]->n);
        vec3 v = sub(&intersection, &lo);
        if (lightness >= 0) {
          pnt c = {j, i};
          SetPixel(surface, &c, FOREGROUND, 255);//(int)clamp(0, 255 * lightness / length(&v) * 10, 255));
        }
      }
    }
  }
  SDL_BlitSurface(surface, 0, SDL_GetWindowSurface(win), 0);
  SDL_UpdateWindowSurface(win);


  while (1) {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case SDL_QUIT:
          SDL_FreeSurface(surface);
          SDL_DestroyWindow(win);
          exit(0);
//        case SDL_MOUSEBUTTONDOWN:
//
//          break;
        default:
          break;
      }
    }
  }
  return 0;
}
