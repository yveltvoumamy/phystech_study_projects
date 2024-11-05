#include <iostream>
#include <cmath>
#include <iomanip>

class Point {
public:
  double x;
  double y;
  Point(double x1, double y2) {
    x = x1;
    y = y2;
  }
  double Distance(Point p2) const {
    return sqrt(pow(p2.x - x, 2) + pow(p2.y - y, 2));
  }
};

class Vector {
public:
  double coordx;
  double coordy;

  Vector(Point start, Point finish) {
    coordx = -start.x + finish.x;
    coordy = -start.y + finish.y;
  }
  Vector(double x1, double y1) {
    coordx = x1;
    coordy = y1;
  }
  double Len() {
    return std::sqrt(std::pow(coordx, 2) + std::pow(coordy, 2));
  }
  double ScalarProduct(Vector second) {
    return second.coordx * coordx + second.coordy * coordy;
  }
  double VectorProduct(Vector second) {
    return -second.coordx * coordy + second.coordy * coordx;
  }
};

class Line {
public:
  int64_t a;
  int64_t b;
  int64_t c;

  Line(int64_t a1, int64_t b1, int64_t c1) {
    a = a1;
    b = b1;
    c = c1;
  }

  Vector DirectionVector() {
    Vector direction_vector(static_cast<double>(b), static_cast<double>(-a));
    return direction_vector;
  }
  Point IntersectionPoint(Line line2) {
    double det = a * line2.b - line2.a * b;
    double x = (b * line2.c - line2.b * c) / det;
    double y = (line2.a * c - a * line2.c) / det;
    Point intersection_point(x, y);
    return intersection_point;
  }
};

class Segment {
public:
  Point start = Point(0, 0);
  Point finish = Point(0, 0);

  Segment(Point a, Point b) {
    start = a;
    finish = b;
  }
};

bool OnSegment(Point p, Point q, Point r);
bool CheckIntersection(Segment segment_a, Segment segment_b, double first, double second, double third, double fourth);
bool IsIntersection(Segment segment_a, Segment segment_b);
double DistanceBetweenPointAndSegment(Point pivot_point, Segment segment);

int main() {
  int64_t a, b, c, d;
  std::cin >> a >> b >> c >> d;
  Point point_a(a, b);
  Point point_b(c, d);
  Segment segment_a(point_a, point_b);
  std::cin >> a >> b >> c >> d;
  Point point_c(a, b);
  Point point_d(c, d);
  Segment segment_b(point_c, point_d);
  std::cout << std::fixed << std::setprecision(6);
  if (IsIntersection(segment_a, segment_b)) {
    std::cout << static_cast<double>(0);
  } else {
    double d1 = DistanceBetweenPointAndSegment(segment_a.start, segment_b);
    double d2 = DistanceBetweenPointAndSegment(segment_a.finish, segment_b);
    double d3 = DistanceBetweenPointAndSegment(segment_b.start, segment_a);
    double d4 = DistanceBetweenPointAndSegment(segment_b.finish, segment_a);
    std::cout << std::min(std::min(d1, d2), std::min(d3, d4));
  }
  return 0;
}

bool IsIntersection(Segment segment_a, Segment segment_b) {
  Point point_a = segment_a.start;
  Point point_b = segment_a.finish;
  Point point_c = segment_b.start;
  Point point_d = segment_b.finish;
  Vector vector_ab(point_a, point_b);
  Vector vector_ac(point_a, point_c);
  Vector vector_ad(point_a, point_d);
  Vector vector_ca(point_c, point_a);
  Vector vector_cb(point_c, point_b);
  Vector vector_cd(point_c, point_d);
  double first = vector_ab.VectorProduct(vector_ac);
  double second = vector_ab.VectorProduct(vector_ad);
  double third = vector_cd.VectorProduct(vector_ca);
  double fourth = vector_cd.VectorProduct(vector_cb);
  return CheckIntersection(segment_a, segment_b, first, second, third, fourth);
}

bool CheckIntersection(Segment segment_a, Segment segment_b, double first, double second, double third, double fourth) {
  Point point_a = segment_a.start;
  Point point_b = segment_a.finish;
  Point point_c = segment_b.start;
  Point point_d = segment_b.finish;
  if (first * second < 0 && third * fourth < 0) {
    return true;
  }
  if (first == 0 && OnSegment(point_a, point_c, point_b)) {
    return true;
  }
  if (second == 0 && OnSegment(point_a, point_d, point_b)) {
    return true;
  }
  if (third == 0 && OnSegment(point_c, point_a, point_d)) {
    return true;
  }
  if (fourth == 0 && OnSegment(point_c, point_b, point_d)) {
    return true;
  }
  return false;
}

bool OnSegment(Point p, Point q, Point r) {
  return (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) && q.y <= std::max(p.y, r.y) &&
          q.y >= std::min(p.y, r.y));
}

double DistanceBetweenPointAndSegment(Point pivot_point, Segment segment) {
  Point point_a = segment.start;
  Point point_b = segment.finish;
  double len = point_a.Distance(point_b);
  if (len == 0) {
    return pivot_point.Distance(point_a);
  }
  double t =
    ((pivot_point.x - point_a.x) * (point_b.x - point_a.x) + (pivot_point.y - point_a.y) * (point_b.y - point_a.y)) /
    (len * len);
  if (t < 0) {
    return pivot_point.Distance(point_a);
  }
  if (t > 1) {
    return pivot_point.Distance(point_b);
  }
  Point projection(point_a.x + t * (point_b.x - point_a.x), point_a.y + t * (point_b.y - point_a.y));
  return pivot_point.Distance(projection);
}