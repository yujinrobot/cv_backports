###############################################################################
# Subdirectories
###############################################################################

add_subdirectory(lib)

###############################################################################
# Binaries
###############################################################################

add_executable(imshow imshow.cpp)
target_link_libraries(imshow ${OpenCV_LIBRARIES} ${catkin_LIBRARIES})
install(TARGETS imshow RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(imshow_backports imshow_backports.cpp)
target_link_libraries(imshow_backports ${PROJECT_NAME} ${OpenCV_LIBRARIES} ${catkin_LIBRARIES})
install(TARGETS imshow_backports RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

