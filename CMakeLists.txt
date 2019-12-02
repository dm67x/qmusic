cmake_minimum_required(VERSION 3.5)

project(QMusic)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
set(APPTYPE WIN32)
else()
set(APPTYPE "")
endif ()

find_package(Qt5 COMPONENTS Widgets Multimedia MultimediaWidgets REQUIRED)

add_executable(QMusic ${APPTYPE}
  main.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
  resources.qrc
)

target_link_libraries(QMusic PRIVATE Qt5::Widgets Qt5::Multimedia Qt5::MultimediaWidgets)
