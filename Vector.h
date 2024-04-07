#ifndef RAYTRACINGSDL__VECTOR_H_
#define RAYTRACINGSDL__VECTOR_H_

#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>

typedef struct {
  double x, y, z;
} vec3 ;

double dot(const vec3 *a, const vec3 *b);
vec3 sub(const vec3 *a, const vec3 *b);
vec3 add(const vec3 *a, const vec3 *b);
double length(const vec3 *a);
vec3 norm(vec3 *v);
vec3 mul_num(const vec3 *v, const double num);
vec3 cross(vec3 *a, vec3 *b);

#endif//RAYTRACINGSDL__VECTOR_H_
