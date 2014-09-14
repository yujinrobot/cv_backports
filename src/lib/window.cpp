/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                        Intel License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2000, Intel Corporation, all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of Intel Corporation may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

#include "precomp.hpp"
#include <map>
#include <opencv2/core/opengl_interop.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/highgui/highgui.hpp>
#include "../../include/cv_backports/imshow.hpp"

using namespace cv;

void cvSetWindowProperty(const char* name, int prop_id, double prop_value)
{
    switch(prop_id)
    {
    //change between fullscreen or not.
    case CV_WND_PROP_FULLSCREEN:
        if (!name || (prop_value!=CV_WINDOW_NORMAL && prop_value!=CV_WINDOW_FULLSCREEN))//bad argument
            break;
        cvSetModeWindow_QT(name,prop_value);
    break;

    case CV_WND_PROP_AUTOSIZE:
        cvSetPropWindow_QT(name,prop_value);
    break;

    case CV_WND_PROP_ASPECTRATIO:
        cvSetRatioWindow_QT(name,prop_value);
    break;

    default:;
    }
}

/* return -1 if error */
double cvGetWindowProperty(const char* name, int prop_id)
{
    if (!name)
        return -1;

    switch(prop_id)
    {
    case CV_WND_PROP_FULLSCREEN:
        return cvGetModeWindow_QT(name);
    break;

    case CV_WND_PROP_AUTOSIZE:
        return cvGetPropWindow_QT(name);
    break;

    case CV_WND_PROP_ASPECTRATIO:
        return cvGetRatioWindow_QT(name);
    break;

    case CV_WND_PROP_OPENGL:
        return cvGetOpenGlProp_QT(name);
    break;

    default:
        return -1;
    }
}

void cv_backports::namedWindow( const std::string& winname, int flags )
{
    cvNamedWindow( winname.c_str(), flags );
}

void cv_backports::destroyWindow( const std::string& winname )
{
    cvDestroyWindow( winname.c_str() );
}

void cv_backports::destroyAllWindows()
{
    cvDestroyAllWindows();
}

void cv_backports::resizeWindow( const std::string& winname, int width, int height )
{
    cvResizeWindow( winname.c_str(), width, height );
}

void cv_backports::moveWindow( const std::string& winname, int x, int y )
{
    cvMoveWindow( winname.c_str(), x, y );
}

void cv_backports::setWindowProperty(const std::string& winname, int prop_id, double prop_value)
{
    cvSetWindowProperty( winname.c_str(), prop_id, prop_value);
}

double cv_backports::getWindowProperty(const std::string& winname, int prop_id)
{
    return cvGetWindowProperty(winname.c_str(), prop_id);
}

int cv_backports::waitKey(int delay)
{
    return cv_backports::cvWaitKey(delay);
}

int cv_backports::createTrackbar(const std::string& trackbarName, const std::string& winName,
                   int* value, int count, TrackbarCallback callback,
                   void* userdata)
{
    return cvCreateTrackbar2(trackbarName.c_str(), winName.c_str(),
                             value, count, callback, userdata);
}

void cv_backports::setTrackbarPos( const std::string& trackbarName, const std::string& winName, int value )
{
    cvSetTrackbarPos(trackbarName.c_str(), winName.c_str(), value );
}

int cv_backports::getTrackbarPos( const std::string& trackbarName, const std::string& winName )
{
    return cvGetTrackbarPos(trackbarName.c_str(), winName.c_str());
}

void cv_backports::setMouseCallback( const std::string& windowName, MouseCallback onMouse, void* param)
{
    cvSetMouseCallback(windowName.c_str(), onMouse, param);
}

int cv_backports::startWindowThread()
{
    return cvStartWindowThread();
}

// OpenGL support

void cv_backports::setOpenGlDrawCallback(const std::string& name, OpenGlDrawCallback callback, void* userdata)
{
    cvSetOpenGlDrawCallback(name.c_str(), callback, userdata);
}

void cv_backports::setOpenGlContext(const std::string& windowName)
{
    cvSetOpenGlContext(windowName.c_str());
}

void cv_backports::updateWindow(const std::string& windowName)
{
    cvUpdateWindow(windowName.c_str());
}

#ifdef HAVE_OPENGL
namespace
{
    std::map<std::string, ogl::Texture2D> wndTexs;
    std::map<std::string, ogl::Texture2D> ownWndTexs;
    std::map<std::string, ogl::Buffer> ownWndBufs;

    void glDrawTextureCallback(void* userdata)
    {
        ogl::Texture2D* texObj = static_cast<ogl::Texture2D*>(userdata);

        ogl::render(*texObj);
    }
}
#endif // HAVE_OPENGL

void cv_backports::imshow( const std::string& winname, InputArray _img )
{
    const Size size = _img.size();
#ifndef HAVE_OPENGL
    CV_Assert(size.width>0 && size.height>0);
    {
        Mat img = _img.getMat();
        CvMat c_img = img;
        cvShowImage(winname.c_str(), &c_img);
    }
#else
    const double useGl = getWindowProperty(winname, WND_PROP_OPENGL);
    CV_Assert(size.width>0 && size.height>0);

    if (useGl <= 0)
    {
        Mat img = _img.getMat();
        CvMat c_img = img;
        cvShowImage(winname.c_str(), &c_img);
    }
    else
    {
        const double autoSize = getWindowProperty(winname, WND_PROP_AUTOSIZE);

        if (autoSize > 0)
        {
            resizeWindow(winname, size.width, size.height);
        }

        setOpenGlContext(winname);

        if (_img.kind() == _InputArray::OPENGL_TEXTURE)
        {
            ogl::Texture2D& tex = wndTexs[winname];

            tex = _img.getOGlTexture2D();

            tex.setAutoRelease(false);

            setOpenGlDrawCallback(winname, glDrawTextureCallback, &tex);
        }
        else
        {
            ogl::Texture2D& tex = ownWndTexs[winname];

            if (_img.kind() == _InputArray::GPU_MAT)
            {
                ogl::Buffer& buf = ownWndBufs[winname];
                buf.copyFrom(_img);
                buf.setAutoRelease(false);

                tex.copyFrom(buf);
                tex.setAutoRelease(false);
            }
            else
            {
                tex.copyFrom(_img);
            }

            tex.setAutoRelease(false);

            setOpenGlDrawCallback(winname, glDrawTextureCallback, &tex);
        }

        updateWindow(winname);
    }
#endif
}

// Without OpenGL

#ifndef HAVE_OPENGL

void cvSetOpenGlDrawCallback(const char*, CvOpenGlDrawCallback, void*)
{
    CV_Error(CV_OpenGlNotSupported, "The library is compiled without OpenGL support");
}

void cvSetOpenGlContext(const char*)
{
    CV_Error(CV_OpenGlNotSupported, "The library is compiled without OpenGL support");
}

void cvUpdateWindow(const char*)
{
    CV_Error(CV_OpenGlNotSupported, "The library is compiled without OpenGL support");
}

#endif // !HAVE_OPENGL

CvFont cv_backports::fontQt(const std::string& nameFont, int pointSize, Scalar color, int weight,  int style, int /*spacing*/)
{
return cv_backports::cvFontQt(nameFont.c_str(), pointSize,color,weight, style);
}

void cv_backports::addText( const Mat& img, const std::string& text, Point org, CvFont font)
{
    CvMat _img = img;
    cv_backports::cvAddText( &_img, text.c_str(), org,&font);
}

void cv_backports::displayStatusBar(const std::string& name,  const std::string& text, int delayms)
{
  cv_backports::cvDisplayStatusBar(name.c_str(),text.c_str(), delayms);
}

void cv_backports::displayOverlay(const std::string& name,  const std::string& text, int delayms)
{
  cv_backports::cvDisplayOverlay(name.c_str(),text.c_str(), delayms);
}
void cv_backports::saveWindowParameters(const std::string& windowName)
{
  cv_backports::cvSaveWindowParameters(windowName.c_str());
}

void cv_backports::loadWindowParameters(const std::string& windowName)
{
  cv_backports::cvLoadWindowParameters(windowName.c_str());
}

int cv_backports::createButton(const std::string& button_name, ButtonCallback on_change, void* userdata, int button_type , bool initial_button_state  )
{
    return cv_backports::cvCreateButton(button_name.c_str(), on_change, userdata, button_type , initial_button_state );
}


/* End of file. */
