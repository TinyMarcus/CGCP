#include "object.h"

Point Object::get_center() const
{
    return center;
}

void Object::move(double dx, double dy, double dz)
{
    Point change(dx, dy, dz);

    for(Polygon& pol : polygons)
    {
        for (Point& point : pol.points)
        {
            point += change;
        }
        pol.setup_flatness();
    }

    center += change;
}

void Object::rotate(double dxy, double dyz, double dzx)
{
    for(Polygon& pol : polygons)
    {
        for (Point& point : pol.points)
        {
            if (dxy != 0)
            {
                point.rotate_dxy(dxy, center);
            }
            if (dyz != 0)
            {
                point.rotate_dyz(dyz, center);
            }
            if (dzx != 0)
            {
                point.rotate_dzx(dzx, center);
            }
        }
        pol.setup_flatness();
    }
}

void Object::resize(double k)
{
    for(Polygon& pol : polygons)
    {
        for (Point& point : pol.points)
        {
            point = center + (point - center) * k;
        }
        pol.setup_flatness();
    }
}

void Object::rotate(double dxy, double dyz, double dzx, const Point& center)
{
    for(Polygon& pol : polygons)
    {
        for (Point& point : pol.points)
        {
            if (dxy != 0)
            {
                point.rotate_dxy(dxy, center);
            }
            if (dyz != 0)
            {
                point.rotate_dyz(dyz, center);
            }
            if (dzx != 0)
            {
                point.rotate_dzx(dzx, center);
            }

        }
        pol.setup_flatness();
    }

    if (dxy != 0)
    {
        this->center.rotate_dxy(dxy, center);
    }
    if (dyz != 0)
    {
        this->center.rotate_dyz(dyz, center);
    }
    if (dzx != 0)
    {
        this->center.rotate_dzx(dzx, center);
    }
}

void Object::resize(double k, const Point& center)
{
    for(Polygon& pol : polygons)
    {
        for (Point& point : pol.points)
        {
            point = center + (point - center) * k;
        }
        pol.setup_flatness();
    }

    this->center = center + (this->center - center) * k;
}

bool Object::operator==(const Object& other) const
{

    if (polygons.size() != other.polygons.size() && center != other.center)
    {
        return false;
    }

    auto it1 = polygons.cbegin();
    auto it2 = other.polygons.cbegin();
    while (it1 != polygons.cend())
    {
        if (*it1 != *it2)
        {
            return false;
        }
        ++it1;
        ++it2;
    }

    return true;
}

bool Object::operator!=(const Object& other) const
{
    return !(*this == other);
}

double Object::min_x() const
{
    double min_x = 4096;
    for(const Polygon& pol : polygons)
    {
        for (const Point& point : pol.points)
        {
            if (point.get_x() < min_x)
            {
                min_x = point.get_x();
            }
        }
    }

    return min_x;
}

double Object::min_y() const
{
    double min_y = 4096;
    for(const Polygon& pol : polygons)
    {
        for (const Point& point : pol.points)
        {
            if (point.get_y() < min_y)
            {
                min_y = point.get_y();
            }
        }
    }

    return min_y;
}

double Object::min_z() const
{
    double min_z = 4096;
    for(const Polygon& pol : polygons)
    {
        for (const Point& point : pol.points)
        {
            if (point.get_z() < min_z)
            {
                min_z = point.get_z();
            }
        }
    }

    return min_z;
}

double Object::max_x() const
{
    double max_x = -4096;
    for(const Polygon& pol : polygons)
    {
        for (const Point& point : pol.points)
        {
            if (point.get_x() > max_x)
            {
                max_x = point.get_x();
            }
        }
    }

    return max_x;
}

double Object::max_y() const
{
    double max_y = -4096;
    for(const Polygon& pol : polygons)
    {
        for (const Point& point : pol.points)
        {
            if (point.get_y() > max_y)
            {
                max_y = point.get_y();
            }
        }
    }

    return max_y;
}

double Object::max_z() const
{
    double max_z = -4096;
    for(const Polygon& pol : polygons)
    {
        for (const Point& point : pol.points)
        {
            if (point.get_z() > max_z)
            {
                max_z = point.get_z();
            }
        }
    }

    return max_z;
}

