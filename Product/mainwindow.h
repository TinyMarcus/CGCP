#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QFileDialog>
#include <QTextStream>
#include <QImage>

#include <limits>

#include <QDialog>
#include <QDebug>
#include <QColorDialog>
#include <QGraphicsPixmapItem>

#include <chrono>
#include <iostream>
#include <thread>

#include "model.h"
#include "manager.h"
#include "zbuffer.h"

const double resize_speed = 1.1;

const int window_size_x = 1440;
const int window_size_y = 785;

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void visualize_model();

private slots:
    void create_model(QString string);
    void add_model(Model& model);
    void ZBufferFunc();
    void keyPressEvent(QKeyEvent*);
    void on_clearScr_clicked();
    void on_ModelButton_clicked();
    void on_modelList_currentRowChanged(int currentRow);
    void on_modelList_clicked(const QModelIndex &index);
    void on_models_toggled(bool checked);
    bool Inters(float min1, float max1, float min2, float max2);
    bool able_to_move(Model &model);
    void on_ColorButton_clicked();
    void on_delButton_clicked();

private:
    Ui::MainWindow* ui;

    QGraphicsScene scene;
    QGraphicsScene scene_bg_color;
    QPixmap* pixmap;
    QPainter* painter;

    Manager manager;
    sizes model_s;

    ZBuffer zbuffer;
    double move_speed = 5;
    double rotate_speed = 0.1;

    void transform_points_for_zbuffer(std::list<Polygon> &transformed_polygons);
};

#endif // MAINWINDOW_H
