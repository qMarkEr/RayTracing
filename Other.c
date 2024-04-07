#include "Other.h"
#include "SDL.h"
#include "Constants.h"

double deg_to_rad(double d) { return d * M_PI / 180.0; }

pnt Normalize(pnt *cords) {
  pnt new = {(double) (cords->x / WIDTH) * 2 - 1,
             (double) ((cords->y / HEIGHT) * 2 - 1) * ASPECT };
  return new;
}
void SetNormPixel(SDL_Surface* surfc, pnt *c, int rgb, int a) {
  int res_x = (int) (c->x + 1) / 2 * WIDTH;
  int res_y = (int) ((c->x + 1) / 2 * HEIGHT / ASPECT);
  uint32_t* pihel = (uint32_t*) surfc->pixels + res_y * WIDTH + res_x;
  *pihel =  rgb << 8 | a;
}

void SetPixel(SDL_Surface* surfc, pnt *c, int rgb, int a) {
  uint32_t* pihel = (uint32_t*) surfc->pixels + (int)c->y * WIDTH + (int)c->x;
  *pihel =  rgb << 8 | a;
}

void FillSurface(SDL_Surface *surfc, int rgb) {
  for (int i = 0; i < WIDTH; ++i) {
    for (int j = 0; j < HEIGHT; ++j) {
      pnt c = {i, j};
      SetPixel(surfc,
               &c,
               rgb, 255);
    }
  }
}

double clamp(double min, double val, double max) {
  return SDL_max(min, SDL_min(val, max));
}