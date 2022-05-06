#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void mySlot(QImage image);

private:
    Ui::MainWindow *ui;
};


class Server: public QTcpServer{
    Q_OBJECT

public:
    Server();
    QTcpSocket* socket;
    QByteArray message;
    QImage image;
    MainWindow* w;

public slots:
    void readyToRead();
    void incomingConnection(qintptr socketNumber);

signals:
    void mySignal(QImage image);
};



#endif // MAINWINDOW_H
