#include "camera.h"

Camera::Camera(const Point &coordinates, const Point &direction)
    : coordinates(coordinates), direction(direction) {}

QPoint Camera::to_screen(const Point& p)
{
    double k = 1;
    if (p.get_z() != coordinates.get_z()) {
        k = 1 - p.get_z() / coordinates.get_z();
    }
    QPoint point(p.get_x() / k, p.get_y() / k);
    return point;
}

Point Camera::to_screen_3d(const Point& p)
{

    if (p.get_z() != coordinates.get_z()) {
        double k = 1 - p.get_z() / coordinates.get_z();
        Point point(p.get_x() / k, p.get_y() / k, p.get_z() / k);
        return point;
    }
    return p;

}

Point Camera::from_screen_3d(const Point& p)
{
    if (p.get_z() != coordinates.get_z()) {
        double k = 1 - p.get_z() / (coordinates.get_z() + p.get_z());
        Point point(p.get_x() * k, p.get_y() * k, p.get_z() * k);
        return point;
    }
    return p;
}

bool Camera::point_visible(const Point &p) const
{
    Point check(p - coordinates);

    return (check.get_x() * direction.get_x() + \
            check.get_y() * direction.get_y() + \
            check.get_z() * direction.get_z() > 0);
}
