#ifndef MODEL_H
#define MODEL_H

#include "point.h"
#include "polygon.h"
#include "object.h"
#include <fstream>

struct sizes
{
    int L;
    int H;
    int W;
};

class Model : public Object
{
public:
    Model() = default;
    virtual ~Model() = default;
    Model(QString string);
    Model(const Model& other) = default;
    Model& operator =(const Model& other);
    void setColor();
    void printModel();
    std::string name_model;
    int cnt_colors;
    std::vector<QColor> colors;
private:
    sizes model_size;
};


#endif // MODEL_H
