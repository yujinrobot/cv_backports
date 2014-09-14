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

#ifndef __CV_BACKPORTS_HIGHGUI_H_
#define __CV_BACKPORTS_HIGHGUI_H_

//#include "cvconfig.h"
//
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/highgui/highgui_c.h"
//#include "opencv2/imgproc/imgproc_c.h"
//#include "opencv2/core/internal.hpp"
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <assert.h>

//for QT
double cvGetModeWindow_QT(const char* name);
void cvSetModeWindow_QT(const char* name, double prop_value);

double cvGetPropWindow_QT(const char* name);
void cvSetPropWindow_QT(const char* name,double prop_value);

double cvGetRatioWindow_QT(const char* name);
void cvSetRatioWindow_QT(const char* name,double prop_value);

double cvGetOpenGlProp_QT(const char* name);



/*namespace cv
{

class CV_EXPORTS BaseWindow
{
public:
    BaseWindow(const String& name, int flags=0);
    virtual ~BaseWindow();
    virtual void close();
    virtual void show(const Mat& mat);
    virtual void resize(Size size);
    virtual void move(Point topleft);
    virtual Size size() const;
    virtual Point topLeft() const;
    virtual void setGeometry(Point topLeft, Size size);
    virtual void getGeometry(Point& topLeft, Size& size) const;
    virtual String getTitle() const;
    virtual void setTitle(const String& str);
    virtual String getName() const;
    virtual void setScaleMode(int mode);
    virtual int getScaleMode();
    virtual void setScrollPos(double pos);
    virtual double getScrollPos() const;
    virtual void setScale(double scale);
    virtual double getScale() const;
    virtual Point getImageCoords(Point pos) const;
    virtual Scalar getPixelValue(Point pos, const String& colorspace=String()) const;

    virtual void addTrackbar( const String& trackbar, int low, int high, int step );
};

typedef Ptr<BaseWindow> Window;

}*/

#endif /* __CV_BACKPORTS_HIGHGUI_H_ */
