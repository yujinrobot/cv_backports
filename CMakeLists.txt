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
find_package(Qt4 REQUIRED)
find_package(OpenCV REQUIRED)

##############################################################################
# Project Configuration
##############################################################################

add_definitions(${Qt4_DEFINITIONS})
add_definitions(${OpenCV_DEFINITIONS})
include_directories(include ${catkin_INCLUDE_DIRS})
include_directories(${QT_INCLUDE_DIR})
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

#add_subdirectory(include)
add_subdirectory(src)

##############################################################################
# Installs
##############################################################################

install(DIRECTORY resources DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
