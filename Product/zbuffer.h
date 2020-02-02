#ifndef ZBUFFER_H
#define ZBUFFER_H

#include <QColor>

struct ZBufferCell
{
    double depth;
    QColor color;

    ZBufferCell();
    void initialize();
};

struct ZBuffer
{
    ZBuffer(const unsigned size_x, const unsigned size_y);
    ~ZBuffer();

    void initialize();

    unsigned size_x;
    unsigned size_y;
    ZBufferCell** cells;
};

#endif // ZBUFFER_H
