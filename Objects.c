#include "Objects.h"

void CalculateTrigNormal(triangle* a) {
  vec3 v01 = sub(&a->v0, &a->v1);
  vec3 v02 = sub(&a->v0, &a->v2);
  vec3 crs = cross(&v01, &v02);
  a->n = norm(&crs);
}

vec3* ToVecArray(list* lst) {
  vec3* res = malloc(sizeof (vec3) * lst->length);
  for (int i = 0; i < lst->length; ++i)
    res[i] = *(vec3*)atIndex(lst, i);
  return res;
}

triangle* ToTrigArray(list* lst) {
  triangle *res = malloc(sizeof (triangle) * lst->length);
  for (int i = 0; i < lst->length; ++i)
    res[i] = *(triangle *)atIndex(lst, i);
  return res;
}

object* load_data(FILE* fptr) {
  list* vertices = init_lst();
  char* data = NULL;
  vec3 *vertices_array = NULL;
  list *triangles = init_lst();
  object* model = malloc(sizeof(object));
  model->count = 0;
  vec3 centroid = { 0, 0, 0 };
  size_t len = 0;

  while (getline(&data, &len, fptr) != -1) {
    if (data[0] == 'v') {
      vec3 vert = {0, 0, 0};
      char *str = NULL;
      char *endptr = NULL;

      str = data + 2;
      char *token = strtok(str, " ");
      vert.x = strtod(token, &endptr);

      token = strtok(NULL, " ");
      vert.z = strtod(token, &endptr);

      token = strtok(NULL, " ");
      vert.y = -strtod(token, &endptr);

      append(vertices, &vert, sizeof(vec3));
    }
    else if (data[0] == 'f') {
      if (model->count == 0) vertices_array = ToVecArray(vertices);
      triangle current_face;
      char *str;
      char *endptr;

      str = data + 2;
      char *token = strtok(str, " ");
      current_face.v0 = vertices_array[strtol(token, &endptr, 10) - 1];

      token = strtok(NULL, " ");
      current_face.v1 = vertices_array[strtol(token, &endptr, 10) - 1];

      token = strtok(NULL, " ");
      current_face.v2 = vertices_array[strtol(token, &endptr, 10) - 1];

      CalculateTrigNormal(&current_face);
      append(triangles, &current_face, sizeof(triangle));
      ++model->count;
    }
  }
  model->faces = ToTrigArray(triangles);
  model->centroid = centroid;
  destroy(vertices);
  destroy(triangles);
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