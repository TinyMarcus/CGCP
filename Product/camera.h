#ifndef CAMERA_H
#define CAMERA_H

#include "point.h"
#include <QPoint>
#include <QColor>

//const double screen_distance = 1000;
const int screen_size_x = 1150;
const int screen_size_y = 780;
const int screen_size_x_half = screen_size_x / 2;
const int screen_size_y_half = screen_size_y / 2;


class Camera
{
public:
    Camera(const Point& coordinates, const Point& direction);
    QPoint to_screen(const Point& p);
    Point to_screen_3d(const Point& point);

	Point from_screen_3d(const Point& p);
    bool point_visible(const Point& p) const;

    Point coordinates;
    Point direction;
};

#endif // CAMERA_H
