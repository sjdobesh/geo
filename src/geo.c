#include <math.h>

#include "vec.h"
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
    new_v2(1.0, 1.0)
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
}
