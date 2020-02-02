#ifndef MODELIO_H
#define MODELIO_H
#include <fstream>
#include <model.h>

class BaseIO
{
public:
    BaseIO() = default;
    virtual ~BaseIO() = default;

    std::vector<Model> io_model;
    virtual void open_file() = 0;
    virtual void close_file() = 0;
};

class ModelIO : public BaseIO
{
public:
    explicit ModelIO(const std::string& file_name);
    ~ModelIO() = default;

    std::shared_ptr<Model> io_model(BaseBuilder &build) override;

    void open_file() override;
    void close_file() override;

private:
    std::string file_name;
    std::ifstream file;
};


#endif // MODELIO_H
