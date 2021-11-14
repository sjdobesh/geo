#include <math.h>

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

// intersect functions

// quadxquad macro
// each of these converts all args to quads and feeds
// them to the seperate axis theorem solver
int qxq(quad a, quad b) {
  polygon p1 = convert_to_poly(a);
  polygon p2 = convert_to_poly(b);
  int intersect = sat(p1, p2);
  free_polygon(p1);
  free_polygon(p2);
  return 0;
}
int qxaaq(quad a, aaquad b) {
  return qxq(a, aaquad_to_quad(b));
}
int aaqxq(aaquad a, quad b) {
  return qxq(aaquad_to_quad(a), b);
}
int aaqxaaq(aaquad a, aaquad b) {
  return qxq(aaquad_to_quad(a), aaquad_to_quad(b));
}
int sat(polygon a, polygon b) {
  v2* a_normals = malloc(a.sides * sizeof(v2));
  v2* b_normals = malloc(b.sides * sizeof(v2));
  for (int i = 0; i < a.sides; i++) {
    // calc a normal
    a_normals[i] = new_v2(-a.points[i].y, a.points[i].x);
    // check for seperating axis
  }
  for (int i = 0; i < b.sides; i++)
    b_normals[i] = new_v2(-b.points[i].y, b.points[i].x);
  return 0;
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
}
