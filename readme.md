# **Geo**
A 2D geometry module in C.
Supports basic geometric objects, conversions, and SAT intersection detection.

## Usage
### _Header Only_
```c
#include "geo.h"
```
### _Compile_
Only necessary for manual testing.
```
git clone https://github.com/sjdobesh/geo.git
cd geo/src
make
./geo
```

## Dependencies

### vec 
- https://github.com/sjdobesh/vec.git
- Included as a git submodule.

## Structures

### _Line_
A line is two points.
```c
struct line {
  v2 p1, p2;
};
```
### _Ray_
A ray is a position and vector direction.
```c
struct ray {
  v2 pos, vec;
};
```
### _Quad_
A quad is a set of four points.
```c
struct quad {
  v2 p1, p2, p3, p4;
};
```
### _Axis Aligned Quad_
An axis aligned quad is a quad that can't rotate.
It is represented by a position vector indicating the top left corner
and a dimension vector, storing its width and height as x and y respectively.
```c
struct aaquad {
  v2 pos, dim;
};
```
### _Triangle_
Triangle is a set of three points.
```c
struct tri {
  v2 p1, p2, p3;
};
```
### _Circle_
A circle is a position and radius.
```c
struct circle {
  v2 pos;
  float rad;
};
```
### _Polygon_
A polygon is an arbitrarily sized list of points It contains a side count which equals the point count.
```c
struct polygon {
  int sides;
  v2* points;
};
```
### _Linear Function_
A linear function is defined by a slope and intercept.
```c
typedef struct lfunc {
  float m, b;
} lfunc;
```

## Functions

### _Allocation_
```c
line    new_line(v2 p1, v2 p2);
ray     new_ray(v2 pos, v2 vec);
quad    new_quad(v2 p1, v2 p2, v2 p3, v2 p4);
aaquad  new_aaquad(v2 tl, v2 br);
tri     new_tri(v2 p1, v2 p2, v2 p3);
circle  new_circle(v2 pos, float rad);
polygon new_polygon(int sides);
void    free_polygon(polygon p); // polygon must be freed
```

### _Conversions_
```c
void quad_to_tri(quad q, tri* t1, tri* t2);
line ray_to_line(ray r);
ray line_to_ray(line l);
polygon to_polygon(quad | aaquad | tri);
quad aaquad_to_quad(aaquad aaq);
```

### _Intersections_

#### _Intersect_
Find the intersection between two objects. Intersection returned via ptr.
Geo is not a struct, but represents that the function accepts any geometric primative we've defined.
```c
int intersect(geo a, geo b, v2* x); 
```
#### _Hit_
A special intersection for rays that not only calcs the intersection, but also the contact normal.
```c
int hit(ray r, quad q, v2* contact, v2* normal, float* hit);
```

### _Utility_
```c
void printg(geo g);
float area(geo g);
float perimeter(geo g);
float length(line);
float distance(vX p1, vX p2);
void get_line_fn(line l, float* a, float* b, float* c);
```
