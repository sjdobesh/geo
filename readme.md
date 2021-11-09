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

```c
// line - 2 points
struct line {
  v2 p1, p2;
};
// ray - poition, vector
struct ray {
  v2 pos, vec;
};
// quad - 4 points
struct quad {
  v2 p1, p2, p3, p4;
};
// axis aligned quad - 2 points, top left, bottom right
struct aaquad {
  v2 tl, br;
};
// triangle - 3 points
struct tri {
  v2 p1, p2, p3;
};
// cirlce - position, radius
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
tri* quad_to_tri(quad q, tri* t1, tri* t2);

### _Utility_
float distance(vX p1, vX p2);
