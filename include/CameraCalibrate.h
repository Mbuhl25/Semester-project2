#ifndef CAMERACALIBRATE_H
#define CAMERACALIBRATE_H
#include <pylon/PylonIncludes.h>
#include <opencv2/opencv.hpp>




class CameraCalibrate {
public:
    CameraCalibrate(); 
    cv::Mat grabFrame();
    void Camera_stop();
    void InitializeCam();
    
private:
    cv::Mat frame;
    Pylon::CInstantCamera camera;
    Pylon::CImageFormatConverter converter;
    Pylon::CPylonImage pylonImage;
    Pylon::CGrabResultPtr ptrGrabResult;
};



#endif