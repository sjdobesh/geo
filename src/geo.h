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

typedef struct poly {
  v2* points;
  int sides;
} poly;

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
poly new_poly(int num_points);
void free_poly(poly p);

// conversion functions
func line_to_func(line l);
func ray_to_func(ray r);
#define to_func(g) _Generic ((g), \
  line: line_to_func, \
  ray:  ray_to_func   \
) (g)

void quad_to_tri(quad q, tri* t1, tri* t2);
line ray_to_line(ray r);
quad aaquad_to_quad(aaquad aaq);


poly pointtopoly(v2 p);
poly raytopoly(ray r);
poly linetopoly(line l);
poly tritopoly(tri t);
poly quadtopoly(quad q);
poly aaquadtopoly(aaquad aaq);
poly circletopoly(circle c);
#define to_poly(g) _Generic ((g), \
  point:  pointtopoly,  \
  ray:    raytopoly,    \
  line:   linetopoly,   \
  tri:    tritopoly,    \
  quad:   quadtopoly,   \
  aaquad: aaquadtopoly, \
  circle: circletopoly  \
) (g)

// intersect functions
// everything but lines is converted to polygons and solved with sat

float slopef(float x1, float y1, float x2, float y2);
float slopev(v2 a, v2 b);
float slopel(line l);
#define slope(a, ...) _Generic ((a), \
  float: slopef,                     \
  v2:    slopev,                     \
  line:  slopel                      \
) (a __VA_OPT__(,) __VA_ARGS__)

// truly generic lets do it, we need to switch on both
// so that input matter doesn't matter

// true intersect functions //--------------
int linexpoint(line l, v2 p, v2* x);
int linexray(line l, ray r, v2* x);
int linexline(line a, line b, v2* x);
int linexfunc(line l, func f, v2* x);
int linexpoly(line l, poly p, v2* x);
#define linexgeo(l, g, x)         \
  poly p = to_poly(g); \
  int x = linexpoly(l, p, x);     \
  free_poly(p);                \
  return x;
int rayxpoint(ray r, v2 p, v2* x);
int rayxray(ray a, ray b, v2* x);
int rayxline(ray r, line l, v2* x);
int rayxfunc(ray r, func f, v2* x);
int rayxpoly(ray r, poly p, v2* x);
#define rayxgeo(l, r, x)          \
  poly p = to_poly(r); \
  int x = rayxpoly(l, p, x);      \
  free_poly(p);                \
  return x;
int funcxpoint(func f, v2 p, v2* x);
int funcxray(func f, ray r, v2* x);
int funcxline(func f, line l, v2* x);
int funcxfunc(func a, func b, v2* x);
int funcxpoly(func f, poly p, v2* x);
#define funcxgeo(f, g, x)         \
  poly p = to_poly(g); \
  int x = funcxpoly(l, p, x);     \
  free_poly(p);                \
  return x;
int pointxpoint(v2 a, v2 b, v2* x);
int pointxray(v2 p, ray r, v2* x);
int pointxline(v2 p, line l, v2* x);
int pointxfunc(v2 p, func f, v2* x);
int pointxpoly(v2 p, poly ply, v2* x);
#define pointxgeo(p, g, x)           \
  poly poly = to_poly(g); \
  int x = pointxpoly(p, poly, x);    \
  free_poly(p);                   \
  return x;
int polyxpoint(poly ply, v2 p, v2* x);
int polyxray(poly p, ray r, v2* x);
int polyxline(poly p, line l, v2* x);
int polyxfunc(poly p, func f, v2* x);
int polyxpoly(poly p, poly ply, v2* x);
#define polyxgeo(p, g, x)        \
  poly poly = to_poly(g);        \
  int x = polyxpoly(p, poly, x); \
  free_poly(p);                  \
  return x;
// secondary generic switches //---------------
#define linex(b) _Generic((b), \
  v2:      linexpoint, \
  ray:     linexray,   \
  line:    linexline,  \
  func:    linexfunc,  \
  poly: linexpoly,  \
  default: linexgeo   \
)
#define rayx(b) _Generic((b), \
  v2:      rayxpoint, \
  ray:     rayxray,   \
  line:    rayxline,  \
  func:    rayxfunc,  \
  poly: rayxpoly,  \
  default: rayxgeo   \
)
#define funcx(b) _Generic((b), \
  v2:      funcxpoint, \
  ray:     funcxray,   \
  line:    funcxline,  \
  func:    funcxfunc,  \
  polgon:  funcxpoly,  \
  default: funcxgeo   \
)
#define pointx(b) _Generic((b), \
  v2:      pointxpoint, \
  ray:     pointxray,   \
  line:    pointxline,  \
  func:    pointxfunc,  \
  poly: pointxpoly,  \
  default: pointxgeo    \
)
#define polyx(b) _Generic((b), \
  v2:      polyxpoint, \
  ray:     polyxray,   \
  line:    polyxline,  \
  func:    polyxfunc,  \
  poly: polyxpoly,  \
  default: polyxgeo    \
)
#define geox(b) _Generic((b), \
  v2:      geoxpoint, \
  ray:     geoxray,   \
  line:    geoxline,  \
  func:    geoxfunc,  \
  poly:    geoxpoly,  \
  default: geoxgeo,   \
)
// main intersect generic switch
#define intersect(a, b, v) _Generic ((a), \
  line:    linex(b),  \
  ray:     rayx(b),   \
  func:    funcx(b),  \
  v2:      pointx(b), \
  poly: polyx(b),  \
  default: geox(b)    \
) (a, b, v)
int sat(poly a, poly b, v2* v);


// ray intersect quad
int hitpoly(ray r, poly p, v2* contact, v2* normal, float* hit);
#define hitgeo(r, g, c, n, h)          \
  poly p = to_poly(g);                 \
  int result = hitpoly(r, p, c, n, h); \
  free_poly(p);                        \
  return result;
// just convert to poly first if necessary
#define hit(r, g, c, n, h) _Generic((g), \
  poly: hitpoly,                         \
  default: hitgeo                        \
) (r, q, c, n, h)


// geometry functions
// lines
float lengthl(line);
float lengthr(ray);
#define length(g) _Generic((g), \
  line: lengthl,                \
  ray:  lengthr                 \
) (g)
// area
float poly_area();
#define geo_area(g)       \
  poly p = to_poly(g);    \
  float a = poly_area(p); \
  free_poly(p);           \
  return a;
#define area(g) _Generic((g), \
  poly:    poly_area,         \
  default: geo_area           \
) (g)
// perimeter
float poly_perim();
#define geo_perim(g)       \
  poly p = to_poly(g);     \
  float p = poly_perim(p); \
  free_poly(p);            \
  return p;
#define perimeter(g) _Generic((g), \
  poly:    poly_perim,             \
  default: geo_perim               \
) (g)
// solve line func
float solve_l(line l, ...);
float solve_v2(v2 a, ...);
float solve_f(float x1, ...);
#define solve(p, ...) _Generic ((p), \
  line : solve_l,                    \
  v2:    solve_v2,                   \
  float: solve_f                     \
)(p, __VA_ARGS__)

// distance
float distance2(v2 p1, v2 p2);
float distance3(v3 p1, v3 p2);
float distance4(v4 p1, v4 p2);
#define distance(a, b) _Generic ((a), \
  v2: distance2,                      \
  v3: distance3,                      \
  v4: distance4                       \
) (a, b)

// utility functions
// print geometry
#define printg(x) _Generic ((x), \
  line:    print_line,           \
  ray:     print_ray,            \
  quad:    print_quad,           \
  aaquad:  print_aaquad,         \
  tri:     print_tri,            \
  circle:  print_circle,         \
  poly:    print_poly            \
) (x)
void print_line(line l);
void print_ray(ray r);
void print_quad(quad q);
void print_aaquad(aaquad aaq);
void print_tri(tri t);
void print_circle(circle c);
void print_poly(poly p);

#endif
