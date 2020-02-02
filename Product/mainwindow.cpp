#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <list>
#include "camera.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    zbuffer(screen_size_x, screen_size_y)
{
    ui->setupUi(this);
    setFixedSize(window_size_x, window_size_y);

    ui->graphicsView->setFixedSize(screen_size_x, screen_size_y);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene.setSceneRect(-screen_size_x / 2, -screen_size_y / 2,
                       screen_size_x, screen_size_y);
    ui->graphicsView->setScene(&scene);

    pixmap = new QPixmap(screen_size_x, screen_size_y);
    QImage image("123.jpg");
    pixmap->convertFromImage(image);
    painter = new QPainter(pixmap);
}

MainWindow::~MainWindow()
{
    delete painter;
    delete pixmap;
    delete ui;
}

void MainWindow::create_model(QString string)
{
    Model m(string);
    add_model(m);
    ui->graphicsView->setFocus();

    for (Model& m: manager.model_list)
    {
        m.setColor();
    }

    ZBufferFunc();
}

void MainWindow::add_model(Model &model)
{
    QString str = QString("Модель ") + QString::number(manager.num_of_models());

    ui->modelList->addItem(str);
    manager.add_model(model);
    ui->modelList->setCurrentRow(ui->modelList->count() - 1);
    manager.active_object = &(manager.model_list[ui->modelList->currentRow()]);
    manager.bg_color = QColor(200, 200, 200);
    ui->background->setScene(&scene_bg_color);
    ui->background->setBackgroundBrush(QColor(200, 200, 200));
}

void MainWindow::visualize_model()
{

    for (Model& m : manager.model_list)
    {
        for (Polygon& pol : m.polygons)
        {
            if (manager.check_visible(m))
            {
                QVector<QPoint> polyvector;

                for (Point& point : pol.points)
                {
                    polyvector.push_back(manager.camera.to_screen(point));
                }

                QPolygon polygon(polyvector);
                scene.addPolygon(polygon,QPen(Qt::black));
            }
        }
    }

}

void MainWindow::on_ModelButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Открыть модель", "", \
                                                        "Wavefront (*.txt)");
    if (filePath.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Не выбран файл");
        return;
    }

    create_model(filePath);
}

void MainWindow::on_clearScr_clicked()
{
    scene.clear();
}



void MainWindow::keyPressEvent(QKeyEvent *e)
{
    scene.clear();
    ui->graphicsView->setFocus();

    if (manager.active_object != nullptr)
    {
        Point zero(manager.model.get_center());
        switch(e->key())
        {
//			move
            case Qt::Key_Q :
                if (ui->cameraButton->isChecked())
                {
                    for (Model& m: manager.model_list)
                    {
                        m.move(0, 0, -move_speed);
                    }
                }
                else
                {
                    if (ui->models->isChecked())
                    {
                        Model curr_model = manager.model_list[ui->modelList->currentRow()];
//                        if (able_to_move(curr_model))
//                        {
                            manager.active_object->move(0, 0, move_speed);
//                        }
                    }
                    else
                    {
                        manager.active_object->move(0, 0, move_speed);
                    }
                }
                break;

            case Qt::Key_E:
                if (ui->cameraButton->isChecked()) {
                    for (Model& m: manager.group_model) {
                        m.move(0, 0, move_speed);
                    }
                } else {
                    if (ui->models->isChecked()) {
                        Model curr_model = manager.model_list[ui->modelList->currentRow()];
                        curr_model.move(0, 0, -move_speed);
//                        if (able_to_move(curr_model)) {
                            manager.active_object->move(0, 0, -move_speed);
//                        }
                    } else {
                        manager.active_object->move(0, 0, -move_speed);
                    }
                }
                break;
            case Qt::Key_W:
                if (ui->cameraButton->isChecked()) {
                    for (Model& m: manager.model_list){
                        m.move(0, move_speed, 0);
                    }
                } else {
                    if (ui->models->isChecked()) {
                        Model curr_model = manager.model_list[ui->modelList->currentRow()];
                        curr_model.move(0, -move_speed, 0);
//                        if (able_to_move(curr_model)) {
                            manager.active_object->move(0, -move_speed, 0);
//                        }
                    } else {
                        manager.active_object->move(0, -move_speed, 0);
                    }

                }
                break;
            case Qt::Key_S:
                if (ui->cameraButton->isChecked()) {
                    for (Model& m: manager.model_list){
                        m.move(0, -move_speed, 0);
                    }
                } else {
                    if (ui->models->isChecked()) {
                        Model curr_model = manager.model_list[ui->modelList->currentRow()];
                        curr_model.move(0, move_speed, 0);
//                        if (able_to_move(curr_model)) {
                            manager.active_object->move(0, move_speed, 0);
//                        }
                    } else {
                        manager.active_object->move(0, move_speed, 0);
                    }
                }
                break;

            case Qt::Key_A :
                if (ui->cameraButton->isChecked()) {
                    for (Model& m: manager.model_list){
                        m.move(move_speed, 0, 0);
                    }
                } else {
                    if (ui->models->isChecked()) {
                        Model curr_model = manager.model_list[ui->modelList->currentRow()];
                        curr_model.move(-move_speed, 0, 0);
//                        if (able_to_move(curr_model)) {
                            manager.active_object->move(-move_speed, 0, 0);
//                        }
                    } else {
                        manager.active_object->move(-move_speed, 0, 0);
                    }
                }
                break;

            case Qt::Key_D:
                if (ui->cameraButton->isChecked()) {
                    for (Model& m: manager.model_list){
                        m.move(-move_speed, 0, 0);
                    }

                } else {
                    if (ui->models->isChecked()) {
                        Model curr_model = manager.model_list[ui->modelList->currentRow()];
                        curr_model.move(move_speed, 0, 0);
//                        if (able_to_move(curr_model)) {
                            manager.active_object->move(move_speed, 0, 0);
//                        }
                    } else {
                        manager.active_object->move(move_speed, 0, 0);
                    }
                }
                break;
//			rotate
            case Qt::Key_K:
                if (ui->cameraButton->isChecked()) {
                    for (Model& m: manager.model_list) {
                        m.rotate(0, -rotate_speed, 0, zero);
                    }
                } else {
                    if (ui->models->isChecked()) {
                        Model curr_model = manager.model_list[ui->modelList->currentRow()];
                        curr_model.rotate(0, rotate_speed, 0);
//                        if (able_to_move(curr_model)) {
                            manager.active_object->rotate(0, rotate_speed, 0);
//                        }
                    } else {
                        manager.active_object->rotate(0, rotate_speed, 0);
                    }
                }
                break;
            case Qt::Key_I:
                if (ui->cameraButton->isChecked()) {
                    for (Model& m: manager.model_list) {
                        m.rotate(0, rotate_speed, 0, zero);
                    }
                    manager.model.rotate(0, rotate_speed, 0, zero);
                } else {
                    if (ui->models->isChecked()) {
                        Model curr_model = manager.model_list[ui->modelList->currentRow()];
                        curr_model.rotate(0, -rotate_speed, 0);
//                        if (able_to_move(curr_model)) {
                            manager.active_object->rotate(0, -rotate_speed, 0);
//                        }
                    } else {
                        manager.active_object->rotate(0, -rotate_speed, 0);
                    }
                }
                break;
            case Qt::Key_L:
                if (ui->cameraButton->isChecked()) {
                    for (Model& m: manager.model_list) {
                        m.rotate(0, 0, -rotate_speed, zero);
                    }
                    manager.model.rotate(0, 0, -rotate_speed, zero);
                } else {
                    if (ui->models->isChecked()) {
                        Model curr_model = manager.model_list[ui->modelList->currentRow()];
                        curr_model.rotate(0, 0, rotate_speed);
//                        if (able_to_move(curr_model)) {
                            manager.active_object->rotate(0, 0, rotate_speed);
//                        }
                    } else {
                        manager.active_object->rotate(0, 0, rotate_speed);
                    }
                }
                break;
            case Qt::Key_J:
                if (ui->cameraButton->isChecked()) {
                    for (Model& m: manager.model_list) {
                        m.rotate(0, 0, rotate_speed, zero);
                    }
                    manager.model.rotate(0, 0, rotate_speed, zero);
                } else {
                    if (ui->models->isChecked()) {
                        Model curr_model = manager.model_list[ui->modelList->currentRow()];
                        curr_model.rotate(0, 0, -rotate_speed);
//                        if (able_to_move(curr_model)) {
                            manager.active_object->rotate(0, 0, -rotate_speed);
//                        }
                    } else {
                        manager.active_object->rotate(0, 0, -rotate_speed);
                    }
                }
                break;
            case Qt::Key_O:
                if (ui->cameraButton->isChecked()) {
                    for (Model& m: manager.model_list) {
                        m.rotate(-rotate_speed, 0, 0, zero);
                    }
                    manager.model.rotate(-rotate_speed, 0, 0, zero);
                } else {
                    if (ui->models->isChecked()) {
                        Model curr_model = manager.model_list[ui->modelList->currentRow()];
                        curr_model.rotate(-rotate_speed, 0, 0);
//                        if (able_to_move(curr_model)) {
                            manager.active_object->rotate(-rotate_speed, 0, 0);
//                        }
                    } else {
                        manager.active_object->rotate(-rotate_speed, 0, 0);
                    }
                }
                break;
            case Qt::Key_U:
                if (ui->cameraButton->isChecked()) {
                    for (Model& m: manager.model_list) {
                        m.rotate(rotate_speed, 0, 0, zero);
                    }

                    manager.model.rotate(rotate_speed, 0, 0, zero);
                } else {
                    if (ui->models->isChecked()) {
                        Model curr_model = manager.model_list[ui->modelList->currentRow()];
                        curr_model.rotate(rotate_speed, 0, 0);
//                        if (able_to_move(curr_model)) {
                            manager.active_object->rotate(rotate_speed, 0, 0);
//                        }
                    } else {
                        manager.active_object->rotate(rotate_speed, 0, 0);
                    }
                }
                break;
//			resize
            case Qt::Key_T:
                manager.active_object->resize(resize_speed);
                break;
            case Qt::Key_Y:
                manager.active_object->resize(1/resize_speed);
                break;
            default:
                break;
        }
    }
    for (Model& m: manager.model_list) {
        m.setColor();
    }
    ZBufferFunc();
}

void MainWindow::ZBufferFunc() {
    scene.clear();

    pixmap->fill(manager.bg_color);
    std::list<Polygon> waiting_polygons;

    transform_points_for_zbuffer(waiting_polygons);
    std::list<Polygon> active_polygons;

//    проходимся по каждой строке экрана
    for (int x = 0; x < screen_size_x; ++x) {
         double real_x = x - screen_size_x_half;
//        здесь нужно посмотреть в список ждущих полигонов и если минимальное значение х меньше или равно текущему
//        нужно убрать данный полигон из списка ждущих и добавить его в список активных
        auto it = waiting_polygons.cbegin();
        while (it != waiting_polygons.cend()) {
            double min_x = (*it).min_x();
            if (min_x <= real_x) {
                active_polygons.push_back(*it);
                it = waiting_polygons.erase(it);
            } else {
                ++it;
            }
        }

        std::list<Polygon> active_polygons_y;
        std::list<Polygon> waiting_polygons_y(active_polygons);

//        если список активных полигонов пуст, скипаем цикл
        if (active_polygons.size() > 0) {
            for (int y = 0; y < screen_size_y; ++y) {
                double real_y = y - screen_size_y_half;

                auto it = waiting_polygons_y.cbegin();
                while (it != waiting_polygons_y.cend()) {
                    double min_y = (*it).min_y();
                    if (min_y <= real_y) {
                        active_polygons_y.push_back(*it);
                        it = waiting_polygons_y.erase(it);
                    } else {
                        ++it;
                    }
                }
    //            проходимся по списку активных полигонов и смотрим глубину пикселя для этого полигона, если она меньше,
    //            чем хранящаяся в -е, записываем ее туда вместе с цветом
                if (active_polygons_y.size() > 0) {
                    double max_depth = std::numeric_limits<double>::lowest();
                    QColor max_color = manager.bg_color;

                    for (const Polygon& polygon : active_polygons_y) {
                        double depth = polygon.depth_of_pixel(real_x, real_y);
                        if (depth > max_depth && polygon.in_polygon(real_x, real_y)) {
                            max_depth = depth;
                            max_color = polygon.polygon_color;
                        }
                    }

                    painter->setPen(max_color);
                    painter->drawPoint(x, y);

                    it = active_polygons_y.cbegin();
                    while (it != active_polygons_y.cend()) {
                        double max_y = (*it).max_y();
                        if (max_y <= real_y) {
                            it = active_polygons_y.erase(it);
                        } else {
                            ++it;
                        }
                    }
                }
            }
        }

//        проходимся по списку активных полигонов и смотрим, если максимальный х для полигона равен текущему, то убираем
//        его из списка активных (в список ждущих НЕ добавляем)
        it = active_polygons.cbegin();
        while (it != active_polygons.cend()) {
            double max_x = (*it).max_x();
            if (max_x <= real_x) {
                it = active_polygons.erase(it);
            } else {
                ++it;
            }
        }
    }


    QGraphicsPixmapItem* it = scene.addPixmap(*pixmap);
    it->setPos(-screen_size_x / 2, -screen_size_y / 2);
}

void MainWindow::transform_points_for_zbuffer(std::list<Polygon>& transformed_polygons) {
    for (Model& m: manager.model_list) {
        for (Polygon& polygon : m.polygons) {
            for (unsigned i = 2; i < polygon.points.size(); ++i) {
                Polygon transformed_polygon;
                transformed_polygon.polygon_color = polygon.polygon_color;

                transformed_polygon.points.push_back(polygon.points[0]);
                transformed_polygon.points.push_back(polygon.points[i - 1]);
                transformed_polygon.points.push_back(polygon.points[i]);

                for (Point& point : transformed_polygon.points) {
                    point = manager.camera.to_screen_3d(point);
                }

                transformed_polygon.setup_flatness();

                transformed_polygons.push_back(transformed_polygon);
            }
        }
    }
}

void MainWindow::on_modelList_currentRowChanged(int currentRow)
{
    manager.active_object = &(manager.model_list[currentRow]);
    ui->graphicsView->setFocus();

    ui->models->setChecked(true);
}

void MainWindow::on_modelList_clicked(const QModelIndex &index)
{
    manager.active_object = &(manager.model_list[index.row()]);
    ui->graphicsView->setFocus();

    ui->models->setChecked(true);
}

void MainWindow::on_models_toggled(bool checked)
{
    if (checked) {
        if (manager.model_list.empty()) {
            manager.active_object = nullptr;
        } else {
            manager.active_object = &(manager.model_list[ui->modelList->currentRow()]);
        }
    }
}

bool MainWindow::Inters(float min1, float max1, float min2, float max2) {
    if (min1 > max2)
        return false;
    if (max1 < min2)
        return false;
    return true;
}


bool MainWindow::able_to_move(Model &model) {
    for (unsigned i = 0; i < manager.model_list.size(); i++) {
        if ((int) i != ui->modelList->currentRow()) {

            if (Inters(model.min_x(), model.max_x(), manager.model_list[i].min_x(), manager.model_list[i].max_x())
                    && Inters(model.min_y(), model.max_y(), manager.model_list[i].min_y(), manager.model_list[i].max_y())
                    && Inters(model.min_z(), model.max_z(), manager.model_list[i].min_z(), manager.model_list[i].max_z())
                    && Inters(manager.model_list[i].min_x(), manager.model_list[i].max_x(), model.min_x(), model.max_x())
                    && Inters(manager.model_list[i].min_y(), manager.model_list[i].max_y(), model.min_y(), model.max_y())
                    && Inters(manager.model_list[i].min_z(), manager.model_list[i].max_z(), model.min_z(), model.max_z())) {
                return false;
            }
        }
    }
    return true;
}

void MainWindow::on_ColorButton_clicked()
{
    QColorDialog* color = new QColorDialog();
    color->open();
    manager.bg_color = color->getColor();

    ui->background->setScene(&scene_bg_color);
    ui->background->setBackgroundBrush(manager.bg_color);
    ZBufferFunc();
}

void MainWindow::on_delButton_clicked()
{
    if (ui->modelList->currentItem()) {
        manager.delete_model(ui->modelList->currentRow());
        delete ui->modelList->takeItem(ui->modelList->currentRow());
    }
    ui->graphicsView->setFocus();
    if (manager.model_list.empty()) {
        manager.active_object = nullptr;
    }
    else {
        manager.active_object = &(manager.model_list[ui->modelList->currentRow()]);
    }

    scene.clear();

    ui->models->toggle();
    for (Model& m: manager.model_list) {
        m.setColor();
    }
    ZBufferFunc();
}
