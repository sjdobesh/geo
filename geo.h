#ifndef _GEO_H_
#define _GEO_H_

#include "vec.h"

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
  v2 tl, br;
} aaquad;

typedef struct tri {
  v2 p1, p2, p3;
} tri;

typedef struct circle {
  v2 pos;
  float rad;
} circle;

// FUNCTIONS //-----------------------------------------------------------------

// initalization functions
line   new_line(v2 p1, v2 p2);
ray    new_ray(v2 pos, v2 vec);
quad   new_quad(v2 p1, v2 p2, v2 p3, v2 p4);
aaquad new_aaquad(v2 tl, v2 br);
tri    new_tri(v2 p1, v2 p2, v2 p3);
circle new_circle(v2 pos, float rad);

// conversion functions
void quad_to_tri(quad q, tri* t1, tri* t2);
line ray_to_line(ray r);
quad aaquad_to_quad(aaquad aaq);

// intersect functions
int quadxquad(quad a, quad b);
int pointxquad(v2 p, quad q);
int rayxquad(ray r, quad q, v2* contact, v2* normal, float* hit);
int linexline(line a, line b, v2* x);

// geometry functions
void get_line_fn(line l, float* a, float* b, float* c);
float length(line);
float quad_area(quad q);
float aaquad_area(aaquad aaq);
float triangle_area(tri t);
float circle_area(circle c);
float circle_perimeter(circle c);
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
  line:   print_line,   \
  ray:    print_ray,    \
  quad:   print_quad,   \
  aaquad: print_aaquad, \
  tri:    print_tri,    \
  circle: print_circle  \
) (x)
void print_line(line l);
void print_ray(ray r);
void print_quad(quad q);
void print_aaquad(aaquad aaq);
void print_tri(tri t);
void print_circle(circle c);



/* beginning implementation code */

#include <math.h>

#include "vec.h"

// line functions
line new_line(v2 p1, v2 p2) {
  line l = {p1, p2};
  return l;
}
line ray_to_line(ray r) {
  line l = {r.pos, vadd(r.pos, r.vec)};
  return l;
}
float length(line l) {
  return distance(l.p1, l.p2);
}

// ray functions
ray new_ray(v2 pos, v2 vec) {
  ray r = {pos, vec};
  return r;
}
ray line_to_ray(line l) {
  ray r = {l.p1, vsub(l.p2, l.p1)};
  return r;
}

// quad functions
quad new_quad(v2 p1, v2 p2, v2 p3, v2 p4) {
  quad q = {p1, p2, p3, p4};
  return q;
}

float quad_area(quad q) {
  return 0.5 * ((
    q.p1.x * q.p2.y +
    q.p2.x * q.p3.y +
    q.p3.x * q.p4.y +
    q.p4.x * q.p1.y
  ) - (
    q.p2.x * q.p1.y +
    q.p3.x * q.p2.y +
    q.p4.x * q.p3.y +
    q.p1.x * q.p4.y
  ));
}

quad aaquad_to_quad(aaquad aaq) {
  quad q = {
    aaq.tl,
    new_v2(aaq.tl.x + aaq.br.x, aaq.tl.y),
    aaq.br,
    new_v2(aaq.br.x - aaq.tl.x, aaq.br.y)
  };
  return q;
}

// axis aligned quad functions
aaquad new_aaquad(v2 tl, v2 br) {
  aaquad aaq = {tl, br};
  return aaq;
}

float aaquad_area(aaquad aaq) {
  return quad_area(aaquad_to_quad(aaq));
}

// triangle functions
tri new_tri(v2 p1, v2 p2, v2 p3) {
  tri t = {p1, p2, p3};
  return t;
}
float triangle_area(tri t) {
  return fabs(
           (t.p2.x * t.p1.y - t.p1.x * t.p2.y) +
           (t.p3.x * t.p2.y - t.p2.x * t.p3.y) +
           (t.p1.x * t.p3.y - t.p3.x * t.p1.y)
         ) / 2;
}

// circle functions
circle new_circle(v2 pos, float rad) {
  circle c = {pos, rad};
  return c;
}
float circle_area(circle c) {
  return PI * pow(c.rad, 2);
}
float circle_perimeter(circle c) {
  return 2 * PI * c.rad;
}

// distance between points
float distance2(v2 p1, v2 p2){
  return sqrt(
           pow(p2.x - p1.x, 2) +
           pow(p2.y - p1.y, 2)
         );
}
float distance3(v3 p1, v3 p2){
  return sqrt(
           pow(p2.x - p1.x, 2) +
           pow(p2.y - p1.y, 2) +
           pow(p2.z - p1.z, 2)
         );
}
float distance4(v4 p1, v4 p2){
  return sqrt(
           pow(p2.x - p1.x, 2) +
           pow(p2.y - p1.y, 2) +
           pow(p2.z - p1.z, 2) +
           pow(p2.w - p1.w, 2)
         );
}

// print functions
void print_line(line l) {
  printf("line [\n");
  printf("  "); printv(l.p1);
  printf("  "); printv(l.p2);
  printf("]\n");
}
void print_ray(ray r) {
  printf("ray [\n");
  printf("  "); printv(r.pos);
  printf("  "); printv(r.vec);
  printf("]\n");
}
void print_quad(quad q) {
  printf("quad [\n");
  printf("  "); printv(q.p1);
  printf("  "); printv(q.p2);
  printf("  "); printv(q.p3);
  printf("  "); printv(q.p4);
  printf("]\n");
}
void print_aaquad(aaquad aaq) {
  printf("aa-quad [\n");
  printf("  "); printv(aaq.tl);
  printf("  "); printv(aaq.br);
  printf("]\n");
}
void print_tri(tri t) {
  printf("triangle [\n");
  printf("  "); printv(t.p1);
  printf("  "); printv(t.p2);
  printf("  "); printv(t.p3);
  printf("]\n");
}
void print_circle(circle c) {
  printf("circle [\n");
  printf("  "); printv(c.pos);
  printf("  "); printf("radius = %.2f\n", c.rad);
  printf("]\n");
}

#endif
