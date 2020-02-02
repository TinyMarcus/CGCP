#ifndef SCENEOBJ_H
#define SCENEOBJ_H

#include <vector>
#include "polygon.h"
#include "point.h"

class Object
{
public:
    virtual void move(double dx, double dy, double dz);
    virtual ~Object() = default;
    virtual void rotate(double dxy, double dyz, double dzx);
    virtual void resize(double k);

    virtual void rotate(double dxy, double dyz, double dzx, const Point& center);
    virtual void resize(double k, const Point& center);

    bool operator==(const Object& other) const;
    bool operator!=(const Object& other) const;

    double min_x() const;
    double min_y() const;
    double min_z() const;

    double max_x() const;
    double max_y() const;
    double max_z() const;

    Point get_center() const;

    std::vector<Polygon> polygons;
    Point center;
};

#endif // SCENEOBJ_H
