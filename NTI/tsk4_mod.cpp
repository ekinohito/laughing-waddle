#include <cmath>
#include <iostream>

#define RIGHT 1.0
#define LEFT -1.0
#define K M_PI / 180.0

using namespace std;


const double radius = 100.0;
const double k = M_PI / 180.0;

double bound(double a) {
  while (a < -180.0) {
    a += 360.0;
  }
  while (a > 180.0) {
    a -= 360.0;
  }
  return a;
}

struct vector {
  double x;
  double y;
  vector(double px = 0, double py = 0) {
    x = px;
    y = py;
  }
  vector operator +(vector o) {
    return vector(x + o.x, y + o.y);
  }
  vector operator -(vector o) {
    return vector(x - o.x, y - o.y);
  }
  vector operator *(double a) {
    return vector(x * a, y * a);
  }
  double sqr_magn() {
    return x * x + y * y;
  }
  double magn() {
    return sqrt(sqr_magn());
  }
  double angle(vector p) {
    vector d = p - *this;
    double a = acos(d.y / d.magn()) / k;
    if(d.x < 0) {
      a = - a;
    }
    return a;
  }
  void out() {
    std::cout << "(" << x << ", " << y << ")";
  }
};

struct circle {
  vector c;
  vector s;
  double r;
  double d;
  circle(double px = 0, double py = 0, double pr = 0, double pd = RIGHT) {
    c = vector(px, py);
    r = pr;
    d = pd;
  }
  void out() {
    std::cout << "{ center: ";
    c.out();
    std::cout << ", radius: " << r << ", direction: " << ((d < 0)? "left" : "right") << " }";
  }
};

struct orient {
  vector p;
  double angle;
  void init() {
    std::cin >> p.y >> p.x >> angle;
  }
  vector get_orthogonal() {
    double n = bound(angle);
    return vector(sin((angle + 90.0) * k), cos((angle + 90.0) * k));
  }
  void get_circles(circle & left, circle & right) {
    vector offset = get_orthogonal();
    left.d = LEFT;
    right.d = RIGHT;
    left.s = p;
    right.s = p;
    left.c = p - offset * left.r;
    right.c = p + offset * right.r;
  }
  void out() {
    std::cout << "{ point: ";
    p.out();
    std::cout << ", angle: " << angle << " }";
  }
};

void intersect(circle & c1, circle & c2, vector & p1, vector & p2) {
  double a, b, c, d, e, f;
  if(abs(c1.c.x - c2.c.x) < abs(c1.c.y - c2.c.y)) {
    e = (c1.c.x - c2.c.x) / (c2.c.y - c1.c.y);
    f = (c2.c.x * c2.c.x - c1.c.x * c1.c.x + c2.c.y * c2.c.y  - c1.c.y * c1.c.y + c1.r * c1.r - c2.r * c2.r) / 2 / (c2.c.y - c1.c.y);
    a = 1 + e * e;
    b = - 2 * c1.c.x + 2 * e * f - 2 * e * c1.c.y;
    c = c1.c.x * c1.c.x + f * f - 2 * f * c1.c.y + c1.c.y * c1.c.y - c1.r * c1.r;
    d = sqrt(b * b - 4 * a * c);
    p1.x = (- b - d) / (2 * a);
    p1.y = e * p1.x + f;
    p2.x = (- b + d) / (2 * a);
    p2.y = e * p2.x + f;
  } else {
    e = (c1.c.y - c2.c.y) / (c2.c.x - c1.c.x);
    f = (c2.c.x * c2.c.x - c1.c.x * c1.c.x + c2.c.y * c2.c.y  - c1.c.y * c1.c.y + c1.r * c1.r - c2.r * c2.r) / 2 / (c2.c.x - c1.c.x);
    a = 1 + e * e;
    b = - 2 * c1.c.y + 2 * e * f - 2 * e * c1.c.x;
    c = c1.c.y * c1.c.y + f * f - 2 * f * c1.c.x + c1.c.x * c1.c.x - c1.r * c1.r;
    d = sqrt(b * b - 4 * a * c);
    p1.y = (- b - d) / (2 * a);
    p1.x = e * p1.y + f;
    p2.y = (- b + d) / (2 * a);
    p2.x = e * p2.y + f;
  }
}

double dist(circle start, circle end) {
  vector med = (start.c + end.c) * 0.5;
  double mag = (end.c - start.c).magn();
  double t;
  if(start.d !=/*== &??*/ end.d) {
    t = sqrt(mag * mag / 4 - start.r * end.r);
  } else {
    t = sqrt(mag * mag / 4 + start.r * end.r);
  }
  vector a, b;
  vector p1, p2;
  double diff, ang1, ang2;
  circle tem(med.x, med.y, t, 0);
  intersect(start, tem, a, b);
  diff = bound(start.c.angle(a) - start.c.angle(end.c));
  if(start.d == RIGHT) {
    if(diff > 0) {
      p1 = b;
    } else {
      p1 = a;
    }
    ang1 = start.c.angle(start.s) - start.c.angle(p1);
  } else {
    if(diff > 0) {
      p1 = a;
    } else {
      p1 = b;
    }
    ang1 = start.c.angle(p1) - start.c.angle(start.s);
  }
  if(ang1 < 0) {
    ang1 += 360.0;
  }
  intersect(end, tem, a, b);
  diff = bound(end.c.angle(a) - end.c.angle(start.c));
  if(end.d == LEFT) {
    if(diff > 0) {
      p2 = b;
    } else {
      p2 = a;
    }
    ang2 = end.c.angle(p2) - end.c.angle(end.s);
  } else {
    if(diff > 0) {
      p2 = a;
    } else {
      p2 = b;
    }
    ang2 = end.c.angle(end.s) - end.c.angle(p2);
  }
  if(ang2 < 0) {
    ang2 += 360.0;
  }
  std::cout << "points: " << '\n';
  p1.out();
  std::cout << '\n';
  p2.out();
  std::cout << '\n';
  return (p2 - p1).magn() + ang1 * k * start.r + ang2 * k * end.r;
}

int main(int argc, char const *argv[]) {
  orient
    drone,
    target;
  circle
    drone_circle_right,
    drone_circle_left,
    target_circle_right,
    target_circle_left;

  drone_circle_right.r  = 100.0;
  drone_circle_left.r   = 100.0;
  target_circle_right.r = 100.0;
  target_circle_left.r  = 100.0;

  drone.init();
  target.init();

  drone.get_circles(drone_circle_left, drone_circle_right);
  target.get_circles(target_circle_left, target_circle_right);

  std::cout << "dists:" << '\n' <<
  dist(drone_circle_left, target_circle_left) << '\n' <<
  dist(drone_circle_left, target_circle_right) << '\n' <<
  dist(drone_circle_right, target_circle_left) << '\n' <<
  dist(drone_circle_right, target_circle_right) << '\n';

  return 0;
}
