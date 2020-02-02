#ifndef FLATNESS_H
#define FLATNESS_H

class Point;

class Flatness
{
public:
    Flatness(double A = 0, double B = 0, double C = 0, double D = 0);
    bool in_flatness(const Point& check, double acc = 1e-4) const;
    Point normal() const;
    Point crossline_with_other(const Flatness& other) const;
    Point some_point_with_other(const Flatness& other) const;
    double a;
    double b;
    double c;
    double d;
};

#endif // FLATNESS_H
