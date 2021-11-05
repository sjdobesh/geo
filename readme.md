# **Geo**
2D geometry module in C.

## **Usage**
```
#include "geo.h"
```

## **Objects**

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

### _Axis-Aligned Quad_
```c
struct aaquad {
  v2 tl, br;
};
```

### _Tri_
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

## **Functions**
