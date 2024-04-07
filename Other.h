#ifndef RAYTRACINGSDL__OTHER_H_
#define RAYTRACINGSDL__OTHER_H_

#include <SDL.h>

typedef struct {
  double x, y;
} pnt;

double deg_to_rad(double d);
void SetNormPixel(SDL_Surface* surfc, pnt *c, int rgb, int a);
void SetPixel(SDL_Surface* surfc, pnt *c, int rgb, int a);
void FillSurface(SDL_Surface * surfc, int rgb);
double clamp(double min, double val, double max);

#endif//RAYTRACINGSDL__OTHER_H_
