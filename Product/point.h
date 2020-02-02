#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <QColor>

class Point
{
    public:
        QColor point_color;
        Point(const double x=0, const double y=0, const double z=0);
        Point(const Point& other) = default;

        double distance(const Point& other) const;
        double distance_zero() const;

        double get_dx(const Point& other) const;
        double get_dy(const Point& other) const;
        double get_dz(const Point& other) const;

        void set_x(const double x);
        void set_y(const double y);
        void set_z(const double z);

        Point& set(const double x, const double y, const double z);
        Point& set_color(QColor color);

        double get_x() const;
        double get_y() const;
        double get_z() const;

        Point operator*(const double k) const;
        Point& operator*=(const double k);

        Point& operator+=(const Point& other);
        Point& operator-=(const Point& other);

        Point operator+(const Point& other) const;
        Point operator-(const Point& other) const;

        Point operator-() const;
        bool operator==(const Point& other) const;
        bool operator!=(const Point& other) const;

        double scalar(const Point& other) const;
        double angle(const Point& other) const;

        Point operator*(const Point& other) const;

        void rotate_dxy(const double dxy, const Point& center);
        void rotate_dyz(const double dyz, const Point& center);
        void rotate_dzx(const double dzx, const Point& center);

        void print_point();
        void print_color();

    private:
        double x;
        double y;
        double z;
};






#endif // POINT_H
