###############################################################################
# Subdirectories
###############################################################################

#add_subdirectory(lib)

###############################################################################
# Binaries
###############################################################################

add_executable(imshow imshow.cpp)
target_link_libraries(imshow ${OpenCV_LIBRARIES} ${catkin_LIBRARIES})
#target_link_libraries(imshow ${PROJECT_NAME} ${OpenCV_LIBRARIES})
install(TARGETS imshow RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
