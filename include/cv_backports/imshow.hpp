/**
 * @file /cv_backports/include/cv_backports/imshow.hpp
 * 
 * @brief Short description of this file.
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef cv_backports_IMSHOW_HPP_
#define cv_backports_IMSHOW_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

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

/*****************************************************************************
** High Gui Functions - replicated from highgui.hpp
*****************************************************************************/

//enum {
//    // Flags for namedWindow
//    WINDOW_NORMAL   = CV_WINDOW_NORMAL,   // the user can resize the window (no constraint) / also use to switch a fullscreen window to a normal size
//    WINDOW_AUTOSIZE = CV_WINDOW_AUTOSIZE, // the user cannot resize the window, the size is constrainted by the image displayed
//    WINDOW_OPENGL   = CV_WINDOW_OPENGL,   // window with opengl support
//
//    // Flags for set / getWindowProperty
//    WND_PROP_FULLSCREEN   = CV_WND_PROP_FULLSCREEN,  // fullscreen property
//    WND_PROP_AUTOSIZE     = CV_WND_PROP_AUTOSIZE,    // autosize property
//    WND_PROP_ASPECT_RATIO = CV_WND_PROP_ASPECTRATIO, // window's aspect ration
//    WND_PROP_OPENGL       = CV_WND_PROP_OPENGL       // opengl support
//};

void imshow(const std::string& winname, cv::InputArray mat);

void namedWindow(const std::string& winname, int flags = cv::WINDOW_AUTOSIZE);
void destroyWindow(const std::string& winname);
void destroyAllWindows();

int startWindowThread();

int waitKey(int delay = 0);

void imshow(const std::string& winname, cv::InputArray mat);

void resizeWindow(const std::string& winname, int width, int height);
void moveWindow(const std::string& winname, int x, int y);

void setWindowProperty(const std::string& winname, int prop_id, double prop_value);//YV
double getWindowProperty(const std::string& winname, int prop_id);//YV

typedef void (*MouseCallback)(int event, int x, int y, int flags, void* userdata);
void setMouseCallback(const std::string& winname, MouseCallback onMouse, void* userdata = 0);
int createTrackbar(const std::string& trackbarname, const std::string& winname,
                              int* value, int count,
                              cv::TrackbarCallback onChange = 0,
                              void* userdata = 0);

int getTrackbarPos(const std::string& trackbarname, const std::string& winname);
void setTrackbarPos(const std::string& trackbarname, const std::string& winname, int pos);

// OpenGL support
typedef void (*OpenGlDrawCallback)(void* userdata);
void setOpenGlDrawCallback(const std::string& winname, OpenGlDrawCallback onOpenGlDraw, void* userdata = 0);
void setOpenGlContext(const std::string& winname);

void updateWindow(const std::string& winname);

//Only for Qt
CvFont fontQt(const std::string& nameFont, int pointSize=-1,
                         cv::Scalar color=cv::Scalar::all(0), int weight=CV_FONT_NORMAL,
                         int style=CV_STYLE_NORMAL, int spacing=0);
void addText( const cv::Mat& img, const std::string& text, cv::Point org, CvFont font);

void displayOverlay(const std::string& winname, const std::string& text, int delayms CV_DEFAULT(0));
void displayStatusBar(const std::string& winname, const std::string& text, int delayms CV_DEFAULT(0));

void saveWindowParameters(const std::string& windowName);
void loadWindowParameters(const std::string& windowName);

typedef void (CV_CDECL *ButtonCallback)(int state, void* userdata);
int createButton( const std::string& bar_name, ButtonCallback on_change,
                             void* userdata=NULL, int type=CV_PUSH_BUTTON,
                             bool initial_button_state=0);

} // cv_backports

#endif /* cv_backports_IMSHOW_HPP_ */
