cmake_minimum_required(VERSION 2.8.11)

project(jtc-tuner-gui)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(YARP REQUIRED)

set(CMAKE_CXX_STANDARD 14)

if(${CMAKE_VERSION} VERSION_LESS 3.0.2)
	message("-- Using cmake < 3.0.2, must wrap ui using QT5_WRAP_UI")
	QT5_WRAP_UI(UI_FORMS mainwindow.ui)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${YARP_INCLUDE_DIRS})


qt5_add_resources(RESOURCE_ADDED resources.qrc)
add_executable(${PROJECT_NAME} main.cpp mainwindow.cpp ${RESOURCE_ADDED} ${UI_FORMS})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets ${YARP_LIBRARIES})
