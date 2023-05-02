#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "DockManager.h"
#include "QVTKOpenGLNativeWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    QVTKOpenGLNativeWidget* m_nativeWidget;

    void onOpen();

    // The main container for docking
    ads::CDockManager* m_dockManager;
};
#endif // MAINWINDOW_H
