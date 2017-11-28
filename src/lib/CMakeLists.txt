##############################################################################
# Sources
##############################################################################

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp) 

##############################################################################
# QT
##############################################################################

if(HAVE_QT_OPENGL)
  set(QT_USE_QTOPENGL TRUE)
endif()
#include(${QT_USE_FILE})

if (Qt5_FOUND)
  QT5_ADD_RESOURCES(_RCC_OUTFILES window_QT.qrc)
  QT5_WRAP_CPP(_MOC_OUTFILES window_QT.h)
else()
  QT4_ADD_RESOURCES(_RCC_OUTFILES window_QT.qrc)
  QT4_WRAP_CPP(_MOC_OUTFILES window_QT.h)
endif()

list(APPEND SOURCES ${_MOC_OUTFILES} ${_RCC_OUTFILES})
#ocv_check_flag_support(CXX -Wno-missing-declarations _have_flag)
#if(${_have_flag})
#  set_source_files_properties(${_RCC_OUTFILES} PROPERTIES COMPILE_FLAGS -Wno-missing-declarations)
#endif()

##############################################################################
# Library
##############################################################################

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME}
                          ${catkin_LIBRARIES}
                          ${OpenCV_LIBRARIES}
                          ${QT_LIBRARIES}
)

##############################################################################
# Installs
##############################################################################

install(TARGETS ${PROJECT_NAME}
   RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)
