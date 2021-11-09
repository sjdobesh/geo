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
float distance2(v2 p1, v2 p2);
float distance3(v3 p1, v3 p2);
float distance4(v4 p1, v4 p2);
#define distance(a, b) _Generic ((a), \
  v2: distance2, \
  v3: distance3, \
  v4: distance4  \
) (a, b)

