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

int main() {
  int64_t x, y;
  std::cin >> x >> y;
  Point point_c(x, y);
  std::cin >> x >> y;
  Point point_a(x, y);
  std::cin >> x >> y;
  Point point_b(x, y);
  Vector vector_ab = Vector(point_a, point_b);
  Vector vector_ac = Vector(point_a, point_c);
  Vector vector_cb = Vector(point_c, point_b);
  if (vector_ab.VectorProduct(vector_ac) == 0) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
  if (vector_ab.ScalarProduct(vector_ac) >= 0 && vector_ab.VectorProduct(vector_ac) == 0) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
  if (vector_ac.ScalarProduct(vector_cb) >= 0 && vector_ac.VectorProduct(vector_cb) == 0) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
  return 0;
}