/**
 * @file /cv_backports/include/cv_backports/impl/imshow.hpp
 * 
 * @brief Short description of this file.
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef cv_backports_IMPL_IMSHOW_HPP_
#define cv_backports_IMPL_IMSHOW_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace cv_backports {

/*****************************************************************************
** Basic Gui Functions - replicated from highgui_c.h
*****************************************************************************/

CvFont cvFontQt(const char* nameFont, int pointSize CV_DEFAULT(-1), cv::Scalar color CV_DEFAULT(cvScalarAll(0)), int weight CV_DEFAULT(CV_FONT_NORMAL),  int style CV_DEFAULT(CV_STYLE_NORMAL), int spacing CV_DEFAULT(0));

void cvAddText(const CvArr* img, const char* text, CvPoint org, CvFont *arg2);

void cvDisplayOverlay(const char* name, const char* text, int delayms CV_DEFAULT(0));
void cvDisplayStatusBar(const char* name, const char* text, int delayms CV_DEFAULT(0));

void cvSaveWindowParameters(const char* name);
void cvLoadWindowParameters(const char* name);

typedef void (CV_CDECL *CvButtonCallback)(int state, void* userdata);
enum {CV_PUSH_BUTTON = 0, CV_CHECKBOX = 1, CV_RADIOBOX = 2};
int cvCreateButton( const char* button_name CV_DEFAULT(NULL),CvButtonCallback on_change CV_DEFAULT(NULL), void* userdata CV_DEFAULT(NULL) , int button_type CV_DEFAULT(CV_PUSH_BUTTON), int initial_button_state CV_DEFAULT(0));

int cvWaitKey(int delay);

} // cv_backports

#endif /* cv_backports_IMSHOW_HPP_ */
