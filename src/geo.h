#ifndef _GEO_H_
#define _GEO_H_

#include "vec/vec.h"

// GEOMETRIC STRUCTS //---------------------------------------------------------

typedef struct line {
  v2 p1, p2;
} line;

typedef struct ray {
  v2 pos, vec;
} ray;

typedef struct quad {
  v2 p1, p2, p3, p4;
} quad;

typedef struct aaquad {
  v2 pos, dim;
} aaquad;

typedef struct tri {
  v2 p1, p2, p3;
} tri;

typedef struct circle {
  v2 pos;
  float rad;
} circle;

typedef struct polygon {
  v2* points;
  int sides;
} polygon;

typedef struct func {
  float m, b;
} func;

// FUNCTIONS //-----------------------------------------------------------------

// initalization functions
line   new_line(v2 p1, v2 p2);
ray    new_ray(v2 pos, v2 vec);
quad   new_quad(v2 p1, v2 p2, v2 p3, v2 p4);
aaquad new_aaquad(v2 tl, v2 br);
tri    new_tri(v2 p1, v2 p2, v2 p3);
circle new_circle(v2 pos, float rad);
polygon new_polygon(int num_points);
void free_polygon(polygon p);
// conversion functions
void quad_to_tri(quad q, tri* t1, tri* t2);
line ray_to_line(ray r);
quad aaquad_to_quad(aaquad aaq);
#define convert_to_poly(g) _Generic ((g), \
  tri: tritopoly,      \
  quad: quadtopoly,    \
  aaquad: aaquadtopoly \
) (g)
polygon quadtopoly(quad q);
polygon aaquadtopoly(aaquad aaq);
polygon tritopoly(tri t);

// intersect functions
// everything but lines is converted to polygons and solved with sat

float slopef(float x1, float y1, float x2, float y2);
float slopev(v2 a, v2 b);
#define slope(a, ...) _Generic ((a), \
  float : slopef, \
  v2:     slopev  \
) (a, __VA_ARGS__)

int linexline(line a, line b, v2* x);
int solve_linear_system_l(line a, line b, v2* v);
int solve_linear_system_f(func a, func b, v2* v);
#define intersect_poly(a, b) \
  polygon p1 = convert_to_poly(a); \
  polygon p2 = convert_to_poly(b); \
  int intersect = sat(p1, p2);     \
  free_polygon(p1);                \
  free_polygon(p2);                \
  return intersect;

#define intersect(a, b) _Generic ((a), \
  line: solve_linear_system_l,  \
  func: solve_linear_system_f,  \
  default: intersect_poly \
) (a, b)

int sat(polygon a, polygon b);

// point intersect quad
#define point_intersect(a, b) _Generic((a), \
  quad: pxquad, \
  aaquad: pxaaquad\
) (a, b)
int pxquad(v2 p, quad q);
int pxaaquad(v2 p, aaquad q);

// ray intersect quad
#define rayxquad(r, q, c, n, h) _Generic((q), \
  quad: rxquad, \
  aaquad: rxaaquad \
) (r, q, c, n, h)
int rxquad(ray r, quad q, v2* contact, v2* normal, float* hit);
int rxaaquad(ray r, quad q, v2* contact, v2* normal, float* hit);


// geometry functions
// lines
void get_line_fn(line l, float* a, float* b, float* c);
float length(line);
// area
float quad_area(quad q);
float aaquad_area(aaquad aaq);
float triangle_area(tri t);
float circle_area(circle c);
float circle_perimeter(circle c);
// solve line func
float solve_l(line l, ...);
float solve_v2(v2 a, ...);
float solve_f(float x1, ...);
#define solve(p, ...) _Generic ((p), \
  line : solve_l, \
  v2:    solve_v2,\
  float: solve_f  \
)(p, __VA_ARGS__)

// distance
float distance2(v2 p1, v2 p2);
float distance3(v3 p1, v3 p2);
float distance4(v4 p1, v4 p2);
#define distance(a, b) _Generic ((a), \
  v2: distance2, \
  v3: distance3, \
  v4: distance4  \
) (a, b)

// utility functions
// print geometry
#define printg(x) _Generic ((x), \
  line:    print_line,   \
  ray:     print_ray,    \
  quad:    print_quad,   \
  aaquad:  print_aaquad, \
  tri:     print_tri,    \
  circle:  print_circle, \
  polygon: print_polygon \
) (x)
void print_line(line l);
void print_ray(ray r);
void print_quad(quad q);
void print_aaquad(aaquad aaq);
void print_tri(tri t);
void print_circle(circle c);
void print_polygon(polygon p);

#endif
