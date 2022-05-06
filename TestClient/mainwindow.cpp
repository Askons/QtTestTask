#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket;
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readyToRead);
    connect(socket, &QTcpSocket::disconnected, this, &QTcpSocket::deleteLater);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    socket->connectToHost("localhost", 6666);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString imagename = QFileDialog::getOpenFileName(this, "Выберите изображение", "", "Изображения (*.png)");
    if (imagename != ""){
        bool test = image.load(imagename);
        if (test){
            image = image.scaledToHeight(ui->label->height(), Qt::SmoothTransformation);
            ui->label->setPixmap(QPixmap::fromImage(image));
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    message.clear();
    QBuffer buffer(&message);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    socket->write(message);
    qDebug() << message;
}
