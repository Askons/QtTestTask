#include "mainwindow.h"

#include <QApplication>

Server::Server(){
    if (this->listen(QHostAddress("localhost"), 6666)){
        qDebug() << "Сервер запущен!";
    }
    else{
        qDebug() << "Произошла какая-то ошибка :)";
    }
}

void Server::incomingConnection(qintptr socketNumber){
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketNumber);
    connect(socket, &QTcpSocket::readyRead, this, &Server::readyToRead);
    connect(socket, &QTcpSocket::disconnected, this, &QTcpSocket::deleteLater);
    qDebug() << "Подключился клиент с номером " << socketNumber;
}

void Server::readyToRead(){
    socket->waitForReadyRead(1);
    message = socket->readAll();
    image.loadFromData(message, "PNG");
    w = new MainWindow();
    w->show();
    connect(this, &Server::mySignal, w, &MainWindow::mySlot);
    emit mySignal(image);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server s;
    return a.exec();
}


