#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QStyle>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    qDebug()<<QStyleFactory::keys();
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion")); // стиль отрисовки делегатов
    MainWindow w;
    w.show();
    return a.exec();
}
