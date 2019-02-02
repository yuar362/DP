#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent_ = nullptr);
    ~MainWindow();
    double getScaleRatio();
    QMatrix getTransformMatrix();

    static const int m_delta_picture_height = 10;
    static const int m_maximum_picture_height = 32000;
private slots:
    void on_actionOpen_picture_triggered();

    void on_actionZoom_in_triggered();

    void on_actionZoom_out_triggered();

    void on_actionRotate_clockwise_triggered();

    void on_actionRotate_counter_triggered();

private:
    void transformPicture(const QMatrix& transform_matrix_);
    void scalePicture(int delta_height_);

    Ui::MainWindow* m_ui;
    QPixmap m_picture;
    QMatrix m_picture_transform_matrix;
    const QMatrix m_rotate_clockwise;       //поворот по часовой стрелки
    const QMatrix m_rotate_counter;         //поворот против часовой стрелки
    int m_picture_height;                   //высота картинки в текущем масштабе
    int m_minimum_picture_height;
    double m_picture_scale_ratio;           //отношение высот текущей картинки и исходной
};

#endif // MAINWINDOW_H
