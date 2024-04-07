#include "Camera.h"
void Zoom(camera *c, double new_fov) { c->FOV = new_fov; }
void RotateCamera(camera *c, double angle_x, double angle_y) {
  double cos_x = SDL_cos(angle_x);
  double sin_x = SDL_sin(angle_x);
  double cos_y = SDL_cos(angle_y);
  double sin_y = SDL_sin(angle_y);
  // direction rotated by x
  vec3 new_dir = {c->direction.x,
                  c->direction.y * cos_x + c->direction.z * sin_x,
                  -sin_x * c->direction.y + c->direction.z * cos_x};
  // rotate by y
  new_dir.x = cos_y * new_dir.x - sin_y * new_dir.z;
  new_dir.z = sin_y * new_dir.x + cos_y * new_dir.z;

  c->direction = new_dir;
}
