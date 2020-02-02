#include "zbuffer.h"
#include <limits>

ZBufferCell::ZBufferCell(): depth(std::numeric_limits<double>::min()), color(Qt::white){}

void ZBufferCell::initialize() {
    depth = std::numeric_limits<double>::min();
    color = Qt::white;
}

ZBuffer::ZBuffer(const unsigned size_x, const unsigned size_y): size_x(size_x), size_y(size_y) {
    cells = new ZBufferCell*[size_x];
    for (unsigned i = 0; i < size_x; ++i) {
        cells[i] = new ZBufferCell[size_y];
    }
}

ZBuffer::~ZBuffer() {
    for (unsigned i = 0 ; i < size_x; ++i) {
        delete[] cells[i];
    }
    delete[] cells;
}


void ZBuffer::initialize() {
    for (unsigned i = 0; i < size_x; ++i) {
        for (unsigned j = 0; j < size_y; ++j) {
            cells[i][j].initialize();
        }
    }
}
