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

Vector operator+(Vector first_vector, Vector second_vector) {
  Vector sum(second_vector.coordx + first_vector.coordx, second_vector.coordy + first_vector.coordy);
  return sum;
}

int main() {
  double x1_start, y1_start, x1_finish, y1_finish;
  double x2_start, y2_start, x2_finish, y2_finish;
  std::cin >> x1_start >> y1_start >> x1_finish >> y1_finish >> x2_start >> y2_start >> x2_finish >> y2_finish;

  Point finish_point1(x1_finish, y1_finish);
  Point start_point1(x1_start, y1_start);
  Vector vector1(start_point1, finish_point1);

  Point finish_point2(x2_finish, y2_finish);
  Point start_point2(x2_start, y2_start);
  Vector vector2(start_point2, finish_point2);

  Vector sum_vector = vector2 + vector1;
  std::cout << std::fixed << std::setprecision(6) << vector1.Len() << ' ' << vector2.Len() << '\n'
            << sum_vector.coordx << ' ' << sum_vector.coordy << '\n'
            << vector1.ScalarProduct(vector2) << ' ' << vector1.VectorProduct(vector2) << '\n'
            << fabs(vector1.VectorProduct(vector2) / 2) << '\n';
}