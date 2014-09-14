/**
 * @file /cv_backports/src/imshow.cpp
 * 
 * @brief Short description of this file.
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <iostream>
//#include <opencv2/core/core.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
#include "../include/cv_backports/imshow.hpp"
#include <ros/package.h>
#include <string>

/*****************************************************************************
** Main
*****************************************************************************/


int main(int argc, char **argv)
{
  std::string path = ros::package::getPath("cv_backports");
  // could use boost here
  std::string image_filename = path + std::string("/resources/middle-earth.jpg");
  std::cout << "Image filename: " << image_filename << std::endl;
  cv::Mat image;
  image = cv::imread(image_filename, CV_LOAD_IMAGE_COLOR);
  cv_backports::namedWindow("Display window", cv::WINDOW_AUTOSIZE);
  cv_backports::imshow("Display window", image);
  cv_backports::waitKey(0);
  return 0;
}

