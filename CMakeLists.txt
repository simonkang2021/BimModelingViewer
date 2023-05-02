# cmake min version
cmake_minimum_required(VERSION 3.15)

# project name
project(BimModelingViewer)

# set output directory
set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# set c++ standard 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set current include
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# set qt
set(QT_PATH "D:/Qt/6.2.4/msvc2019_64")
set(CMAKE_PREFIX_PATH ${QT_PATH}/lib/cmake)
find_package(Qt6 COMPONENTS Widgets REQUIRED)
include_directories("${QT_PATH}/include/QtWidgets")  
include_directories("${QT_PATH}/include/QtOpenGLWidgets")  

# qtadvanceddockin
include_directories("./ThirdLib/QtADS/include")
link_directories("./ThirdLib/QtADS/lib")

# vtk
set(VTK_PATH "E:/vtk/install")
set(CMAKE_PREFIX_PATH ${VTK_PATH}/lib/cmake)
find_package(VTK COMPONENTS
  CommonColor
  CommonCore
  IOImport
  CommonDataModel
  FiltersSources
  InteractionStyle
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2
  FiltersSources
  InteractionWidgets
  GUISupportQt
  RenderingQt
  RenderingAnnotation REQUIRED)
  link_directories("${VTK_PATH}/lib")
  include_directories(${VTK_PATH}/include/vtk-9.2)

# set source
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        BimModelingViewer.rc
)

# add exe
add_executable(ModelingViewer WIN32
    ${PROJECT_SOURCES}
)

# link
target_link_libraries(ModelingViewer PRIVATE 
    Qt6::Core 
    Qt6::Gui 
    Qt6::Widgets
    Qt6::OpenGLWidgets
    vtksys-9.2d.lib
    vtkCommonSystem-9.2d.lib
    vtkCommonColor-9.2d.lib
    vtkCommonCore-9.2d.lib
    vtkIOImport-9.2d.lib
    vtkCommonDataModel-9.2d.lib
    vtkFiltersSources-9.2d.lib
    vtkInteractionStyle-9.2d.lib
    vtkRenderingContextOpenGL2-9.2d.lib
    vtkRenderingCore-9.2d.lib
    vtkRenderingFreeType-9.2d.lib
    vtkRenderingGL2PSOpenGL2-9.2d.lib
    vtkRenderingOpenGL2-9.2d.lib
    vtkFiltersSources-9.2d.lib
    vtkInteractionWidgets-9.2d.lib
    vtkGUISupportQt-9.2d.lib
    vtkRenderingQt-9.2d.lib
    vtkRenderingAnnotation-9.2d.lib
    qtadvanceddocking.lib
    qtadvancedcssd.lib
)


file(GLOB dllSrc "${QT_PATH}/bin/*d.dll" "./ThirdLib/QtADS/bin/*.dll" "${QT_PATH}/plugins/platforms" "${VTK_PATH}/bin/*d.dll")
file(COPY ${dllSrc} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CONFIGURATION_TYPES})


