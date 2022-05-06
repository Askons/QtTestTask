#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mySlot(QImage image)
{
    image = image.scaledToHeight(ui->label->height(), Qt::SmoothTransformation);
    ui->label->setPixmap(QPixmap::fromImage(image));
}
