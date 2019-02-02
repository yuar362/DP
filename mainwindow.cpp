#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent)
  ,m_ui(new Ui::MainWindow)
  ,m_picture()
  ,m_picture_transform_matrix(1, 0, 0, 1, 0, 0)
  ,m_rotate_clockwise(0, 1, -1, 0, 0, 0)
  ,m_rotate_counter(0, -1, 1, 0, 0, 0)
  ,m_picture_height(0)
  ,m_picture_scale_ratio(1)
{
    m_ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

double MainWindow::getScaleRatio()
{
    return m_picture_scale_ratio;
}

QMatrix MainWindow::getTransformMatrix()
{
   return m_picture_transform_matrix;
}

void MainWindow::on_actionOpen_picture_triggered()
{
    QString f_name = QFileDialog::getOpenFileName(nullptr, "Open File", "", "*.png; *.bmp; *.jpg" );
    if(!f_name.isNull())
    {
        if(m_picture.load(f_name))
        {
            m_ui->pic->setPixmap(m_picture);
            m_picture_height = m_picture.height();
            m_picture_transform_matrix.reset();
            m_picture_scale_ratio = 1;
            m_minimum_picture_height = m_picture_height / 4;
        }
    }
}

void MainWindow::on_actionZoom_in_triggered()
{
    scalePicture(m_delta_picture_height);
}

void MainWindow::on_actionZoom_out_triggered()
{
    scalePicture(-m_delta_picture_height);
}

void MainWindow::on_actionRotate_clockwise_triggered()
{
    transformPicture(m_rotate_clockwise);
}

void MainWindow::on_actionRotate_counter_triggered()
{
    transformPicture(m_rotate_counter);
}

void MainWindow::transformPicture(const QMatrix& transform_matrix_)
{
    m_picture_transform_matrix = transform_matrix_ * m_picture_transform_matrix;
    if(!m_picture.isNull())
    {
        auto picture = m_picture.transformed(m_picture_transform_matrix);
        m_ui->pic->setPixmap(picture);
    }
}

void MainWindow::scalePicture(int delta_height_)
{
    if(m_picture_height + delta_height_ < m_minimum_picture_height || m_picture_height + delta_height_ > m_maximum_picture_height)
        return;

    m_picture_height += delta_height_;
    auto scale_coef = 1 / m_picture_scale_ratio;        //будет содержать отношение высот текущей картинки и полученной после масштабирования
    m_picture_scale_ratio = static_cast<double>(m_picture_height) / m_picture.height();
    scale_coef *= m_picture_scale_ratio;
    QMatrix scale_matrix(scale_coef, 0, 0, scale_coef, 0, 0);
    transformPicture(scale_matrix);
}


