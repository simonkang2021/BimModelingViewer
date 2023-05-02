#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <DockWidget.h>
#include <QLabel>
#include <QPlainTextEdit>
#include <QTableWidget>
#include <QMenu>
#include <QToolButton>
#include <QToolBar>
#include <QStyle>
#include <QAction>
#include <QFileDialog>


#include "DockAreaWidget.h"
#include "AutoHideDockContainer.h"

//VTK
#include <vtkCamera.h>
#include <vtkGLTFImporter.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkLight.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>
#include <vtkViewport.h>
#include <vtkAnnotatedCubeActor.h>
#include <vtkProperty.h>
#include <vtkContextView.h>
#include <vtkGenericOpenGLRenderWindow.h>


#include <vtkActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkMinimalStandardRandomSequence.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkObjectFactory.h>
#include <vtkPolyDataMapper.h>
#include <vtkPropPicker.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <QOpenGLWidget>
#include <QVTKOpenGLNativeWidget.h>



using namespace ads;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QIcon icon("E:/Qt+VTK+OCC/BimModelingViewer/Resources/Images/open.png");
    ui->actionOpen->setIcon(icon);

    // before initializing QApplication, set the default surface format.
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());

    setWindowTitle(QApplication::instance()->applicationName());

    m_dockManager = new ads::CDockManager(this);

    // Set central widget
    m_nativeWidget = new QVTKOpenGLNativeWidget();
    CDockWidget* CentralDockWidget = new CDockWidget("CentralWidget");
    vtkNew<vtkGenericOpenGLRenderWindow> window;
    m_nativeWidget->setRenderWindow(window.Get());

    //³õÊ¼»¯±³¾°É«
    vtkColor3d backgroundColor{ 232, 232, 232 };
    vtkNew<vtkRenderer> renderer;
    renderer->SetBackground(backgroundColor.GetData());
    m_nativeWidget->renderWindow()->AddRenderer(renderer);

    CentralDockWidget->setWidget(m_nativeWidget);
    auto* centralDockArea = m_dockManager->setCentralWidget(CentralDockWidget);
    centralDockArea->setAllowedAreas(DockWidgetArea::OuterDockAreas);

    // create other dock widgets
    QTableWidget* table = new QTableWidget();
    CDockWidget* TableDockWidget = new CDockWidget("Table 1");
    TableDockWidget->setWidget(table);
    TableDockWidget->setMinimumSizeHintMode(CDockWidget::MinimumSizeHintFromDockWidget);
    TableDockWidget->setMinimumSize(200, 150);
    auto autoHideContainer = m_dockManager->addDockWidgetTab(DockWidgetArea::LeftDockWidgetArea, TableDockWidget);

    QTableWidget* propertiesTable = new QTableWidget();
    CDockWidget* PropertiesDockWidget = new CDockWidget("Properties");
    PropertiesDockWidget->setWidget(propertiesTable);
    PropertiesDockWidget->setMinimumSizeHintMode(CDockWidget::MinimumSizeHintFromDockWidget);
    PropertiesDockWidget->resize(250, 150);
    PropertiesDockWidget->setMinimumSize(200, 150);
    m_dockManager->addDockWidget(DockWidgetArea::RightDockWidgetArea, PropertiesDockWidget, centralDockArea);

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onOpen);
}

MainWindow::~MainWindow() {
    delete ui;
    delete m_dockManager;
    //delete m_nativeWidget;
}

void MainWindow::onOpen()
{
    QString fileName = QFileDialog::getOpenFileName();
    if (fileName.isEmpty() || !fileName.endsWith(".gltf")) {
        return;
    }
    ui->statusbar->showMessage(fileName);

    vtkNew<vtkGLTFImporter> importer;
    importer->SetFileName(fileName.toStdString().c_str());

    // An interactor
    vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
    renderWindowInteractor->SetRenderWindow(m_nativeWidget->renderWindow());

    // Set the custom stype to use for interaction.
    vtkNew<vtkInteractorStyleTrackballCamera> style;
    renderWindowInteractor->SetInteractorStyle(style);

    //set render window and update
    importer->SetRenderWindow(m_nativeWidget->renderWindow());
    importer->Update();

    m_nativeWidget->renderWindow()->Render();
    renderWindowInteractor->Start();
}
