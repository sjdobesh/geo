#include "vec.h"
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
quad aaquad_to_quad(aaquad aaq) {
  quad q = {
    aaq.tl,
    newv2(aaq.tl.x + aaq.br.x, aaq.tl.y),
    aaq.br,
    newv2(aaq.br.x - aaq.tl.x, aaq.br.y)
  };
  return q;
}

// axis aligned quad functions
aaquad new_aaquad(v2 tl, v2 br) {
  aaquad aaq = {tl, br};
  return aaq;
}

// triangle functions
tri new_tri(v2 p1, v2 p2, v2 p3) {
  tri t = {p1, p2, p3};
  return t;
}
float triangle_area(tri t) {
  return abs(
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
