#include "manager.h"

Manager::Manager():
    camera(p_c, p_d),
    active_object(nullptr){}

void Manager::add_model(const Model &model)
{
    this->model_list.push_back(model);
}

void Manager::delete_model(int index)
{
    for (int i = index; i < int(model_list.size()) - 1; ++i)
    {
        model_list[i] = model_list[i + 1];
    }
    model_list.pop_back();
}

bool Manager::check_visible(const Model &model) const
{
    for(const Polygon& pol : model.polygons)
    {
        for (const Point& point : pol.points)
        {
            if (!camera.point_visible(point))
            {
                return false;
            }
        }
    }
    return true;
}

int Manager::num_of_models()
{
    return this->model_list.size();
}
