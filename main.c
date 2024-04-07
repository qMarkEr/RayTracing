#include "Constants.h"
#include "Objects.h"
#include "Other.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include "Camera.h"

int main() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) printf("u suck\n");
  SDL_Window *win = SDL_CreateWindow("backrooms",
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     WIDTH, HEIGHT, 0);
  SDL_Renderer *main_render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawBlendMode(main_render, SDL_BLENDMODE_BLEND);
  FILE* f = fopen("/home/marker/RayTracingSDL/Assets/cube.obj", "r");
  object* shit = load_data(f);
  fclose(f);
  double focal_length = 1 / SDL_tan(deg_to_rad(30) / 2.0);
  camera c;
  c.origin.x = 0;
  c.origin.y = 0;
  c.origin.z = -1;
  vec3 lo = { 0, 1, -1 };
  int mouse_start_x = 0;
  int mouse_start_y = 0;
  int mouse_move_x = 0;
  int mouse_move_y = 0;
  bool is_pressed = false;
  while (1) {
    // SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, WIDTH, HEIGHT, 32, SDL_PIXELFORMAT_RGBA8888);
    // FillSurface(surface, BACKGROUND);
    double z_buffer[WIDTH][HEIGHT];
    for (int i1 = 0; i1 < WIDTH; ++i1)
      memset(z_buffer[i1], 0.0, HEIGHT);

    uint64_t start = SDL_GetTicks64();
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
          if (intersectTriangle(&shit->faces[k], &c.origin, &ray, &coef)) {
            vec3 mul_ray = mul_num(&ray, coef);
            intersection = add(&c.origin, &mul_ray);
            if (closest_hit == -1 || z_buffer[j][i] > intersection.z) {
              z_buffer[j][i] = intersection.z;
              closest_hit = k;
            }
          }
        }
        if (closest_hit != -1) {
          double lightness = dot(&lo, &shit->faces[closest_hit].n);
          vec3 v = sub(&intersection, &lo);
          if (lightness >= 0) {
            //pnt intersec = {j, i};
           // SetPixel(surface, &intersec, FOREGROUND, );
            SDL_SetRenderDrawColor(main_render, FOREGROUND, (uint8_t)clamp(0, 255 * lightness / length(&v) * 5, 255));
            SDL_RenderDrawPoint(main_render, j, i);
          }
        }
      }
    }
    SDL_RenderPresent(main_render);
    SDL_SetRenderDrawColor(main_render, 0, 0, 0, 255);
    SDL_RenderClear(main_render);
   // SDL_BlitSurface(surface, 0, SDL_GetWindowSurface(win), 0);
   // SDL_UpdateWindowSurface(win);
    uint64_t end = SDL_GetTicks64();

    printf("%ld\n", end - start);

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case SDL_QUIT:
          //SDL_FreeSurface(surface);
          SDL_DestroyWindow(win);
          exit(0);
        case SDL_MOUSEBUTTONDOWN:
          SDL_GetMouseState(&mouse_start_x, &mouse_start_y);
          is_pressed = true;
          break;
        case SDL_MOUSEMOTION:
          if (is_pressed) {
            SDL_GetMouseState(&mouse_move_x, &mouse_move_y);
            //RotateCamera(&c);
          }
          break;
        case SDL_MOUSEBUTTONUP:
          is_pressed = false;
        default:
          break;
      }
    }
   // SDL_FreeSurface(surface);
  }
  return 0;
}
