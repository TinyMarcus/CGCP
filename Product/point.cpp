#include "point.h"
#include <cmath>


Point::Point(const double x, const double y, const double z): x(x), y(y), z(z){}


double Point::distance(const Point& other) const {
    double dx = get_dx(other);
    double dy = get_dy(other);
    double dz = get_dz(other);

    return sqrt(dx * dx + dy * dy + dz * dz);
}


double Point::distance_zero() const {
    return sqrt(x * x + y * y + z * z);
}


double Point::get_dx(const Point& other) const {
    return other.x - x;
}


double Point::get_dy(const Point& other) const {
    return other.y - y;
}


double Point::get_dz(const Point& other) const {
    return other.z - z;
}


void Point::set_x(const double x) {
    this->x = x;
}


void Point::set_y(const double y) {
    this->y = y;
}


void Point::set_z(const double z) {
    this->z = z;
}


Point& Point::set(const double x, const double y, const double z) {
    this->x = x;
    this->y = y;
    this->z = z;

    return *this;
}


Point& Point::set_color(QColor color)
{
    this->point_color = color;
}


double Point::get_x() const {
    return x;
}


double Point::get_y() const {
    return y;
}


double Point::get_z() const {
    return z;
}


Point Point::operator*(const double k) const {

    Point result(*this);

    result.x *= k;
    result.y *= k;
    result.z *= k;

    return result;
}


Point& Point::operator*=(const double k) {
    x *= k;
    y *= k;
    z *= k;

    return *this;
}


Point& Point::operator+=(const Point& other) {
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}


Point& Point::operator-=(const Point& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}


Point Point::operator+(const Point& other) const {
    Point result(*this);
    result += other;
    return result;
}


Point Point::operator-(const Point& other) const {
    Point result(*this);
    result -= other;
    return result;
}


Point Point::operator-() const {
    Point result(-x, -y, -z);
    return result;
}


bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y && z == other.z;
}


bool Point::operator!=(const Point& other) const {
    return !(*this == other);
}


double Point::scalar(const Point& other) const {
    return x * other.x + y * other.y + z * other.z;
}


double Point::angle(const Point& other) const {
    double cos_angle = scalar(other) / (distance_zero() * other.distance_zero());
    return acos(cos_angle);
}


void Point::rotate_dxy(const double dxy, const Point& center) {
    double dx = center.get_dx(*this);
    double dy = center.get_dy(*this);

    x = center.get_x() + dx * cos(dxy) + dy * sin(dxy);
    y = center.get_y() - dx * sin(dxy) + dy * cos(dxy);
}


void Point::rotate_dyz(const double dyz, const Point& center) {
    double dy = center.get_dy(*this);
    double dz = center.get_dz(*this);

    y = center.get_y() + dy * cos(dyz) + dz * sin(dyz);
    z = center.get_z() - dy * sin(dyz) + dz * cos(dyz);
}


void Point::rotate_dzx(const double dzx, const Point& center) {
    double dz = center.get_dz(*this);
    double dx = center.get_dx(*this);

    z = center.get_z() - dx * sin(dzx) + dz * cos(dzx);
    x = center.get_x() + dx * cos(dzx) + dz * sin(dzx);
}

Point Point::operator*(const Point& other) const {
    Point p(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    return p;
}

void Point::print_point() {
    std::cout << x << " " << y << " " << z << std::endl;
}

void Point::print_color() {
    std::cout << this->point_color.red() << " " << this->point_color.green() << " " << this->point_color.blue() << std::endl;
}
