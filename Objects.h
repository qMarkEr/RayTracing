#ifndef RAYTRACINGSDL__OBJECTS_H_
#define RAYTRACINGSDL__OBJECTS_H_

#include <stdlib.h>
#include "list.h"
#include "Vector.h"

typedef struct {
  vec3 v0, v1, v2, n;
} triangle;

typedef struct {
  triangle** trigs;
  vec3 centroid;
  size_t count;
} object;

object* load_data(FILE* fptr);
void CalculateTrigNormal(triangle* a);
bool intersectPlane(const vec3* n, const vec3* p0, const vec3* l0, const vec3* l, double *t);
bool intersectTriangle(const triangle* surface, const vec3* l0, const vec3 *l, double *t);

#endif//RAYTRACINGSDL__OBJECTS_H_
