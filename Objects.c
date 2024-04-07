#include "Objects.h"

void CalculateTrigNormal(triangle* a) {
  vec3 v01 = sub(&a->v0, &a->v1);
  vec3 v02 = sub(&a->v0, &a->v2);
  vec3 crs = cross(&v01, &v02);
  a->n = norm(&crs);
}

object* load_data(FILE* fptr) {
  list* vertex = init_lst();
  char* data = NULL;
  object* model = NULL;
  vec3 centroid = { 0, 0, 0 };
  size_t len = 0;
  while (getline(&data, &len, fptr) != -1) {
    if (data[0] == 'v') {
      vec3 vert = { 0, 0, 0 };
      char* str = NULL;
      char *endptr = NULL;

      str = data + 2;
      char *token = strtok(str, " ");
      vert.x = strtod(token, &endptr);

      token = strtok(NULL, " ");
      vert.z = strtod(token, &endptr);

      token = strtok(NULL, " ");
      vert.y = -strtod(token, &endptr);

      append(vertex, &vert, sizeof(vec3));
    }
    else if (data[0] == 'f') {
      if (model == NULL) {
        model = malloc(sizeof(model));
        model->trigs = malloc(sizeof (triangle) * vertex->length);
        model->count = 0;
      }
      char* str;
      char *endptr;
      model->trigs[model->count] = malloc(sizeof(triangle));

      str = data + 2;
      char *token = strtok(str, " ");
      vec3 temp_trig[3];
      int j = 0;
      while (token != NULL) {
        temp_trig[j++] = *(vec3 *) atIndex(vertex, strtol(token, &endptr, 10) - 1);
        token = strtok(NULL, " ");
      }
      model->trigs[model->count]->v0 = temp_trig[0];
      model->trigs[model->count]->v1 = temp_trig[1];
      model->trigs[model->count]->v2 = temp_trig[2];
      CalculateTrigNormal(model->trigs[model->count]);
      ++model->count;
    }
  }
  model->centroid = centroid;
  destroy(vertex);
  return model;
}

bool intersectPlane(const vec3* n, const vec3* p0, const vec3* l0, const vec3* l, double *t)
{
  double denom = dot(n, l);
  if (denom < 1e-6) {
    vec3 p0l0 = sub(p0, l0);
    *t = dot(&p0l0, n) / denom;
    return (*t >= 0);
  }
  return false;
}

bool intersectTriangle(const triangle* surface, const vec3* l0, const vec3 *l, double *t) {
  bool plane_intersected = intersectPlane(&surface->n, &surface->v0, l0, l, t);
  if (!plane_intersected) return false;
  vec3 ray = mul_num(l, *t);
  vec3 intersection = add(l0, &ray);
  
  vec3 edge0 = sub(&surface->v1, &surface->v0);
  vec3 edge1 = sub(&surface->v2, &surface->v1);
  vec3 edge2 = sub(&surface->v0, &surface->v2);

  vec3 C0 = sub(&intersection, &surface->v0);
  vec3 C1 = sub(&intersection, &surface->v1);
  vec3 C2 = sub(&intersection, &surface->v2);

  vec3 cross_c_edge0 = cross(&edge0, &C0);
  vec3 cross_c_edge1 = cross(&edge1, &C1);
  vec3 cross_c_edge2 = cross(&edge2, &C2);
  return (dot(&surface->n, &cross_c_edge0) > 0 &&
          dot(&surface->n, &cross_c_edge1) > 0 &&
          dot(&surface->n, &cross_c_edge2) > 0);
}