cmake_minimum_required(VERSION 3.16.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(TARGET utext)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(SOURCES main.cpp src/mainwindow.cpp src/textArea.cpp src/myTab.cpp src/myTree.cpp src/finder.cpp)
set(HEADERS src/mainwindow.h src/textArea.h src/myTab.h src/myTree.h)
set(UI Forms/mainwindow.ui)

qt5_add_resources(SOURCES resources/resources.qrc)

add_executable(${TARGET} ${SOURCES} ${HEADERS} ${UI})

add_subdirectory(src)
include_directories(./src)

target_link_libraries(${TARGET} Qt5::Core Qt5::Widgets)

set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../..)
