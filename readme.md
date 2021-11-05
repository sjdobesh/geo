# **Geo**
2D geometry module in C.

## **Usage**
```
#include "geo.h"
```

## **Objects**

### _Line_
struct line {
  v2 p1, p2;
};

### _Ray_
struct ray {
  v2 pos, vec;
};

### _Quad_
struct quad {
  v2 p1, p2, p3, p4;
};

### _Axis-Aligned Quad_
struct aaquad {
  v2 tl, br;
};

### _Tri_
struct tri {
  v2 p1, p2, p3;
};

### _Circle_
struct circle {
  v2 pos;
  float rad;
};

## **Functions**
