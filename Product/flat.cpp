#include "flat.h"
#include "point.h"
#include <cmath>

Flatness::Flatness(double A, double B, double C, double D): a(A), b(B), c(C), d(D) {}

bool Flatness::in_flatness(const Point& check, double acc) const {
    return (fabs(check.get_x() * a + check.get_y() * b + check.get_z() * c + d) < acc);
}

Point Flatness::normal() const {
    Point result(a, b, c);
    return result;
}


Point Flatness::crossline_with_other(const Flatness& other) const {
    return normal() * other.normal();
}


Point Flatness::some_point_with_other(const Flatness& other) const {
    double z = 0;
    if (fabs(b) > 1e-4) {
        double x = (-other.d + other.b / b * d) / (other.a + a * other.b / b);
        double y = (-other.d + a * x) / b;
        Point result(x, y, z);
        return result;
    } else if (fabs(other.b) > 1e-4) {
        double x = (-d + b / other.b * other.d) / (a + other.a * b / other.b);
        double y = (-d + other.a * x) / other.b;
        Point result(x, y, z);
        return result;
    } else {
        double y = 0;
        double x =  -d / a;
        Point result(x, y, z);
        return result;
    }

}
