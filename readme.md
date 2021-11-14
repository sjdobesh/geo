# **Geo**
A 2D geometry module in C.

## Usage
### _Header Only_
```c
#include "geo.h"
```
### _Compile_
```
git clone https://github.com/sjdobesh/vec.git
cd vec/src
make
./vec
```

## Dependencies
**vec** - https://github.com/sjdobesh/vec.git

## Structures

### _Line_
```c
struct line {
  v2 p1, p2;
};
```
### _Ray_
```c
struct ray {
  v2 pos, vec;
};
```
### _Quad_
```c
struct quad {
  v2 p1, p2, p3, p4;
};
```
### _Axis Aligned Quad_
```c
struct aaquad {
  v2 pos, dim;
};
```
### _Triangle_
```c
struct tri {
  v2 p1, p2, p3;
};
```
### _Circle_
```c
struct circle {
  v2 pos;
  float rad;
};
```

## Functions

### _Allocation_
```c
line   new_line(v2 p1, v2 p2);
ray    new_ray(v2 pos, v2 vec);
quad   new_quad(v2 p1, v2 p2, v2 p3, v2 p4);
aaquad new_aaquad(v2 tl, v2 br);
tri    new_tri(v2 p1, v2 p2, v2 p3);
circle new_circle(v2 pos, float rad);
```

### _Conversions_
```c
void quad_to_tri(quad q, tri* t1, tri* t2);
line ray_to_line(ray r);
quad aaquad_to_quad(aaquad aaq);
```

### _Intersections_
```c
int quadx(quad | aaquad, quad | aaquad);
int pointxq(v2, quad | aaquad);
int rayxq(ray r, quad q, v2* contact, v2* normal, float* hit);
int linexline(line a, line b, v2* x);
```

### _Utility_
```c
void printg(line | ray | quad | aaquad | tri | circle);
float length(line);
float circle_area(circle c);
float circle_perimeter(circle c);
float distance(vX p1, vX p2);
void get_line_fn(line l, float* a, float* b, float* c);
```
