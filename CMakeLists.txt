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

# qtadvanceddockin
include_directories("./ThirdLib/QtADS/include")
link_directories("./ThirdLib/QtADS/lib")

# set source
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

# add exe
add_executable(ModelingViewer WIN32
    ${PROJECT_SOURCES}
)

# link
target_link_libraries(ModelingViewer PRIVATE 
    Qt6::Widgets
    qtadvanceddocking.lib
)


file(GLOB dllSrc "${QT_PATH}/bin/*d.dll" "./ThirdLib/QtADS/bin/*.dll" "${QT_PATH}/plugins/platforms")
file(COPY ${dllSrc} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CONFIGURATION_TYPES})


