#include "mainwindow.h"

#include <QString>
#include <QFile>

#include <QApplication>

#include <QDebug>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("BimModelingViewer");
    a.setQuitOnLastWindowClosed(true);
    //QIcon icon("./Resources/Images/icoBimModeling.ico");
    //a.setWindowIcon(icon);

    MainWindow w;
    w.showMaximized();
    //w.setWindowIcon(icon);

    /*
    QFile StyleSheetFile("./output/qt_material/material.css");
    StyleSheetFile.open(QIODevice::ReadOnly);
    QTextStream StyleSheetStream(&StyleSheetFile);
    a.setStyleSheet(StyleSheetStream.readAll());
    StyleSheetFile.close();
    */

    return a.exec();
}
