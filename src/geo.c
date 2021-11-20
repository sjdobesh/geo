#include <math.h>
#include <stdarg.h>

#include "geo.h"

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

// convert axis aligned quad to free quad
quad aaquad_to_quad(aaquad aaq) {
  v2 br = vadd(aaq.pos, aaq.dim); // calc bottom right
  quad q = {
    aaq.pos,
    new_v2(br.x, aaq.pos.y),
    br,
    new_v2(aaq.pos.x, br.y)
  };
  return q;
}

// axis aligned quad functions
aaquad new_aaquad(v2 pos, v2 dim) {
  aaquad aaq = {pos, dim};
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

// polygon functions
polygon new_polygon(int num_points) {
  polygon p = {malloc(num_points * sizeof(v2)), num_points};
  return p;
}
polygon quadtopoly(quad q) {
  polygon p = new_polygon(4);
  p.points[0] = q.p1;
  p.points[1] = q.p2;
  p.points[2] = q.p3;
  p.points[3] = q.p4;
  return p;
}
polygon aaquadtopoly(aaquad aaq) {
  return quadtopoly(aaquad_to_quad(aaq));
}
polygon tritopoly(tri t) {
  polygon p = new_polygon(3);
  p.points[0] = t.p1;
  p.points[1] = t.p2;
  p.points[2] = t.p3;
  return p;
}
void free_polygon(polygon p) {
  free(p.points);
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

// slope (m) = (b.y - a.y)/(b.x - a.x)
float slopef(float x1, float y1, float x2, float y2) {
  return (y2 - y1) / (x2 - x1);
}
float slopev(v2 a, v2 b) {
  return slopef(a.x, a.y, b.x, b.y);
}
func line_to_func(line l) {
  float m = slope(l.p1, l.p2);
  float b = l.p1.y - (m * l.p1.x);
  func f = { m, b };
  return f;
}

v2 solve_linear_system_l(line a, line b) {
  return solve_linear_system_f(line_to_func(a), line_to_func(b));
}

// solve system of two linear equations
v2 solve_linear_system_f(func a, func b) {
  float x = (a.b - b.b) / (b.m - a.m);
  float y = (a.m * x) + a.b;
  v2 soln = {x, y};
  return soln;
}

// create a line perpendicular to l
line perpendicular(line l) {
  // convert p to ray for easier rotation
  ray r = line_to_ray(l); // now p1 is origin, p2 is vector
  r = new_ray(
    r.pos,                    // origin stays in place
    new_v2(-r.vec.y, r.vec.x) // rotate the vector 90 around the origin
  );
  // back to line
  return ray_to_line(r);
}

void gen_sides(polygon p, line** sides) {
  for (int i = 0; i < p.sides; i++) {
    line side = {
      p.points[i],
      p.points[i == p.sides ? 0 : i+1] // if we are the end, wrap around
    };
    *sides[i] = side;
  }
}

// project a point p onto line l using proj function slope
v2 project_point(v2 p, func proj, func line) {
  // adjust b for this point
  proj.b = p.y - (proj.m * p.x);
  return solve_linear_system_f(proj, line);
}

void min_max_projection(polygon poly, func side, func norm, v2* min, v2* max) {
  // for each point
  v2* projected = malloc(sizeof(v2) * poly.sides);
  for (int j = 0; j < poly.sides; j++) {
    // create a new function with the sides slope through p
    v2 p = poly.points[j];
    // slope
    float m = side.m;
    // solve for b -- y = mx + b ; b = y - mx
    float b = p.y - (m * p.x);
    func projection = {m, b};
    // solve for the intersection of the two functions and collect it
    projected[j] = solve_linear_system_f(projection, norm);
  }
  // find min and max vals -- evaluation is always by x then y
  v2 min_v, max_v;
  min_v = max_v = projected[0]; // set first vals
  for (int j = 1; j < poly.sides; j++) {
    if (min_v.x > projected[j].x || min_v.y > projected[j].y) {
      min_v = projected[j];
    }
    if (max_v.x > projected[j].x || max_v.y > projected[j].y) {
      max_v = projected[j];
    }
  }
  // free our projection list
  free(projected);
  // send back via ptr
  *min = min_v;
  *max = max_v;
}

int projection_overlap(polygon a, polygon b,
                       func* a_side_funcs, func* a_normal_funcs,
                       func* b_side_funcs, func* b_normal_funcs) {
  for (int i = 0; i < a.sides; i++) {
    // project all the points and find min and max
    func a_side = a_side_funcs[i];
    func a_norm = a_normal_funcs[i];
    func b_side = b_side_funcs[i];
    func b_norm = b_normal_funcs[i];
    v2 a_min, a_max, b_min, b_max;
    min_max_projection(a, a_side, a_norm, &a_min, &a_max);
    min_max_projection(b, b_side, b_norm, &b_min, &b_max);
    // check for overlap
    if ((a_min.x < b_max.x && a_min.x > b_min.x) ||
        (a_min.y < b_max.y && a_min.y > b_min.y) ||
        (b_min.x < a_max.x && b_min.x > a_min.x) ||
        (b_min.y < a_max.y && b_min.y > a_min.y)) {
      return 1; // INTERSECTION DETECTED
    }
  }
  return 0;
}

int sat(polygon a, polygon b) {
  printf("Called SAT\n");
  // calc normals
  line* a_sides = malloc(a.sides * sizeof(line));
  line* b_sides = malloc(b.sides * sizeof(line));
  gen_sides(a, &a_sides);
  gen_sides(b, &b_sides);
  // convert to functions
  func* a_side_funcs   = malloc(a.sides * sizeof(func));
  func* b_side_funcs   = malloc(b.sides * sizeof(func));
  func* a_normal_funcs = malloc(a.sides * sizeof(func));
  func* b_normal_funcs = malloc(b.sides * sizeof(func));
  // make functions for sides and normals
  for (int i = 0; i < a.sides; i++) {
    a_side_funcs[i]   = line_to_func(a_sides[i]);
    a_normal_funcs[i] = line_to_func(perpendicular(a_sides[i]));
  }
  for (int i = 0; i < b.sides; i++) {
    b_side_funcs[i]   = line_to_func(b_sides[i]);
    b_normal_funcs[i] = line_to_func(perpendicular(b_sides[i]));
  }
  // check each normal of a
  int collision = projection_overlap(
    a, b,
    a_side_funcs, a_normal_funcs,
    b_side_funcs, b_normal_funcs
  );
  // check each normal of b (if it wasnt already an intersection)
  collision = collision == 1 ? 1 : projection_overlap(
    b, a,
    b_side_funcs, b_normal_funcs,
    a_side_funcs, a_normal_funcs
  );
  // free mallocd arrays -- function must hit these before returning
  free(a_side_funcs);
  free(b_side_funcs);
  free(a_normal_funcs);
  free(b_normal_funcs);
  free(a_sides);
  free(b_sides);
  return collision;
}

int pxquad(v2 p, quad q) {
  return 0;
}
int pxaaquad(v2 p, aaquad q) {
  return 0;
}
int rxquad(ray r, quad q, v2* contact, v2* normal, float* hit) {
  return 0;
}
int rxaaquad(ray r, quad q, v2* contact, v2* normal, float* hit) {
  return 0;
}
int linexline(line a, line b, v2* x) {
  return 0;
}

// print functions
void print_line(line l) {
  printf("line [\n");
  printf("  p1:"); printv(l.p1);
  printf("  p2:"); printv(l.p2);
  printf("]\n");
}
void print_ray(ray r) {
  printf("ray [\n");
  printf("  pos:"); printv(r.pos);
  printf("  vec:"); printv(r.vec);
  printf("]\n");
}
void print_quad(quad q) {
  printf("quad [\n");
  printf("  p1:"); printv(q.p1);
  printf("  p2:"); printv(q.p2);
  printf("  p3:"); printv(q.p3);
  printf("  p4:"); printv(q.p4);
  printf("]\n");
}
void print_aaquad(aaquad aaq) {
  printf("aa-quad [\n");
  printf("  pos:"); printv(aaq.pos);
  printf("  dim:"); printv(aaq.dim);
  printf("]\n");
}
void print_tri(tri t) {
  printf("triangle [\n");
  printf("  p1:"); printv(t.p1);
  printf("  p2:"); printv(t.p2);
  printf("  p3:"); printv(t.p3);
  printf("]\n");
}
void print_circle(circle c) {
  printf("circle [\n");
  printf("  pos:"); printv(c.pos);
  printf("  radius:%.2f\n", c.rad);
  printf("]\n");
}
void print_polygon(polygon p) {
  printf("polygon [\n");
  printf("  sides:%d\n", p.sides);
  printf("  points:\n");
  for (int i = 0; i < p.sides; i++) {
    printf("    ");
    printv(p.points[i]);
  }
}

int main() {
  line l = new_line(
    new_v2(1.0, 2.0),
    new_v2(3.0, 4.0)
  );
  ray r = new_ray(
    new_v2(1.0, 2.0),
    new_v2(3.0, 4.0)
  );
  quad q = new_quad(
    new_v2(0.0, 0.0),
    new_v2(1.0, 0.0),
    new_v2(1.0, 1.0),
    new_v2(0.0, 1.0)
  );
  aaquad aaq = new_aaquad(
    new_v2(0.0, 0.0),
    new_v2(2.0, 2.0)
  );
  tri t = new_tri(
    new_v2(0.0, 0.0),
    new_v2(1.0, 1.0),
    new_v2(2.0, 0.0)
  );
  circle c = new_circle(new_v2(0.0, 0.0), 1.0);
  // print everything
  printg(l);
  printg(r);
  printg(q);
  printg(aaq);
  printg(t);
  printg(c);
  // conversion functions
  printf("Conversion functions...\n");
  printf("Converting axis aligned quad to quad...\n");
  printg(aaq);
  printg(aaquad_to_quad(aaq));
  printf("Converting quad to polygon...\n");
  printg(q);
  polygon p =  convert_to_poly(q);
  printg(p);
  free_polygon(p);
  // area functions
  printf("Area functions...\n");
  printg(c);
  printf("area:%.2f\n", circle_area(c));
  printf("perimeter:%.2f\n", circle_perimeter(c));
  // intersect functions
  printf("Intersect functions...\n");
}
