#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <DockWidget.h>
#include <QLabel>
#include <QPlainTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  m_DockManager = new ads::CDockManager(this);


  QLabel *l = new QLabel();
  l->setWordWrap(true);
  l->setAlignment(Qt::AlignTop | Qt::AlignLeft);
  l->setText("Lorem ipsum dolor sit amet, consectetuer adipiscing elit. ");

  ads::CDockWidget *leftDockWidget = new ads::CDockWidget("视图");
  leftDockWidget->setWidget(l);
  leftDockWidget->toggleViewAction();
  m_DockManager->addDockWidget(ads::CenterDockWidgetArea, leftDockWidget);

}

MainWindow::~MainWindow() {
  delete ui;
  delete m_DockManager;
}
