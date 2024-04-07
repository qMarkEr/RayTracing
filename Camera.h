#ifndef RAYTRACINGSDL__CAMERA_H_
#define RAYTRACINGSDL__CAMERA_H_
#include "Vector.h"

typedef struct {
  vec3 direction;
  vec3 origin;
  double FOV;
} camera;

void RotateCamera(camera *c, double angle_x, double angle_y);
void MoveCamera(camera *c, double offset_x, double offset_y, double offset_z);
void Zoom(camera *c, double new_fov);

#endif//RAYTRACINGSDL__CAMERA_H_
