##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 2.8.3)
project(cv_backports)

##############################################################################
# Find Packages
##############################################################################

find_package(catkin REQUIRED COMPONENTS
    roslib
)

find_package(Qt5 QUIET COMPONENTS 
  Core 
  Widgets 
  Xml 
  OpenGL 
  PrintSupport 
  Concurrent 
  Test)

if (Qt5_FOUND)
  set(QT_INCLUDES 
    ${Qt5Core_INCLUDE_DIRS} 
    ${Qt5Widgets_INCLUDE_DIRS} 
    ${Qt5Xml_INCLUDE_DIRS} 
    ${Qt5OpenGL_INCLUDE_DIRS} 
    ${Qt5PrintSupport_INCLUDE_DIRS} 
    ${Qt5Concurrent_INCLUDE_DIRS} 
    ${Qt5Test_INCLUDE_DIRS})
  set(QT_LIBRARIES 
    Qt5::Core 
    Qt5::Widgets 
    Qt5::Xml 
    Qt5::OpenGL 
    Qt5::PrintSupport 
    Qt5::Concurrent 
    Qt5::Test)
  add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0)
else()
  find_package(Qt4 REQUIRED)
  include(${QT_USE_FILE})
  set(CMAKE_AUTOMOC ON)
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
  set(QT_INCLUDES ${QT_INCLUDE_DIR} ${QT_INCLUDE_DIR}/QtCore ${QT_INCLUDE_DIR}/QtGui)
  set(QT_LIBRARIES ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTTEST_LIBRARY})
  add_definitions(${Qt4_DEFINITIONS})
endif()

find_package(OpenCV 2 REQUIRED)

##############################################################################
# Project Configuration
##############################################################################

add_definitions(${OpenCV_DEFINITIONS})
include_directories(include ${catkin_INCLUDE_DIRS})
include_directories(${QT_INCLUDES})
include_directories(${OpenCV_INCLUDE_DIRS})

##############################################################################
# Catkin
##############################################################################

catkin_package(
    INCLUDE_DIRS include
    LIBRARIES ${PROJECT_NAME}
    DEPENDS OpenCV
)

##############################################################################
# Sources
##############################################################################

add_subdirectory(include)
add_subdirectory(src)

##############################################################################
# Installs
##############################################################################

install(DIRECTORY resources DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
