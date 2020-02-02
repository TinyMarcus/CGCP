#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include "model.h"
#include "camera.h"
#include "object.h"

const Point p_c(0, 0, 400);
const Point p_d(0, 0, -1);
const double distance = 800;

class Manager
{
public:
    Manager();
    void add_model(const Model& model);
    void delete_model(int index);
    bool check_visible(const Model& model) const;
    int num_of_models();
    Camera camera;
    std::vector<Model> model_list;
    Model model;
    std::vector<Model> group_model;
    Object* active_object = nullptr;
    QColor bg_color;
};

#endif // MANAGER_H
