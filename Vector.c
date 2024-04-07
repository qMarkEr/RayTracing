#include "Vector.h"

double dot(const vec3 *a, const vec3 *b) {
  return a->x * b->x + a->y * b->y + a->z * b->z;
}

vec3 sub(const vec3 *a, const vec3 *b) {
  vec3 res = {a->x - b->x, a->y - b->y, a->z - b->z};
  return res;
}

vec3 add(const vec3 *a, const vec3 *b) {
  vec3 res = {a->x + b->x, a->y + b->y, a->z + b->z};
  return res;
}

double length(const vec3 *a) {
  return SDL_sqrt(dot(a, a));
}

vec3 norm(vec3 *v) {
  double l = length(v);
  vec3 res = {v->x / l, v->y / l, v->z / l};
  return res;
}

vec3 mul_num(const vec3 *v, const double num) {
  vec3 res = {v->x * num, v->y * num, v->z * num};
  return res;
}

vec3 cross(vec3 *a, vec3 *b) {
  vec3 res = {a->y * b->z - a->z * b->y,
              a->z * b->x - a->x * b->z,
              a->x * b->y - a->y * b->x};
  return res;
}