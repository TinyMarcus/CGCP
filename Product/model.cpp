#include "model.h"
#include "camera.h"
#include <ctime>
#include <fstream>
#include <QImage>
#include <iostream>
#include <cmath>
#include "mainwindow.h"
#include <QDebug>

Model::Model(QString string) {
    int cnt_polygons, cnt_dots;
    model_size.W = 1;
    model_size.H = 1;
    model_size.L = 1;
    double x, y, z;
    std::ifstream file;
    file.open(string.toStdString());

    std::getline(file, name_model);
    file >> cnt_polygons;
    Point form_point;

    for (int i = 0; i < cnt_polygons; i++)
    {
        file >> cnt_dots;
        Polygon polygon;
        for (int j = 0; j < cnt_dots; j++)
        {
            file >> x >> y >> z;
            form_point.set(x, y, z);
            polygon.points.push_back(form_point);
        }
        polygons.push_back(polygon);
    }

    for (Polygon& polygon : polygons) {
        polygon.setup_flatness();
    }

    file >> x >> y >> z;
    this->center.set(x, y, z);
}

Model& Model::operator =(const Model &other) {
    if (this == &other) {
        return *this;
    }

    this->model_size.H = other.model_size.H;
    this->model_size.L = other.model_size.L;
    this->model_size.W = other.model_size.W;

    this->center = other.center;
    this->polygons = other.polygons;

    return *this;
}

void Model::setColor()
{
    int cnt = 0;

    for (Polygon &p: polygons)
    {
        Point view(0, 0, -1);

        double angle = view.angle(p.flatness.normal());
        if (angle > M_PI_2)
        {
            angle = M_PI - angle;
        }
        double measure = cos(angle);

        if (name_model.find("hammer") != std::string::npos)
        {
            if (cnt < 30)
            {
                p.polygon_color =  QColor(20 + 100 * measure, 20 + 100 * measure, 20 + 100 * measure);
            }
            else
            {
                p.polygon_color =  QColor(65 + 100 * measure, 42 + 100 * measure, 0 + 100 * measure);
            }
            cnt++;
        }
        else if (name_model.find("nut") != std::string::npos)
        {
            p.polygon_color =  QColor(10 + 100 * measure, 10 + 100 * measure, 10 + 100 * measure);
        }
    }
}

void Model::printModel()
{
    for(Polygon& pol : polygons)
    {
        for (Point& point : pol.points)
        {
            point.print_point();
        }
        pol.setup_flatness();
    }
}
