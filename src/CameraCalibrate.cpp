#include "CameraCalibrate.h"
#include <iostream>


CameraCalibrate::CameraCalibrate() {} // constructor to make the object

// Åben Kamera
cv::Mat CameraCalibrate::grabFrame()
{
    camera.RetrieveResult(
        5000,
        ptrGrabResult,
        Pylon::TimeoutHandling_ThrowException
    );

    if (!ptrGrabResult || !ptrGrabResult->GrabSucceeded())
    {
        std::cout << "Grab failed\n";
        return cv::Mat(); // 👈 KRITISK
    }

    converter.Convert(pylonImage, ptrGrabResult);

    cv::Mat img(ptrGrabResult->GetHeight(),
                ptrGrabResult->GetWidth(),
                CV_8UC3,
                (uint8_t*)pylonImage.GetBuffer());

    return img.clone();
}

void CameraCalibrate::InitializeCam()
{
        // Initialize Pylon Basler kamera
    Pylon::PylonInitialize();

    camera.Attach(Pylon::CTlFactory::GetInstance().CreateFirstDevice());
    camera.Open();

    camera.StartGrabbing(Pylon::GrabStrategy_LatestImageOnly);

    converter.OutputPixelFormat = Pylon::PixelType_BGR8packed;

    GenApi::INodeMap& nodemap = camera.GetNodeMap();
    GenApi::CEnumerationPtr(nodemap.GetNode("ExposureAuto"))->FromString("Off");
    GenApi::CEnumerationPtr(nodemap.GetNode("GainAuto"))->FromString("Off");
    GenApi::CEnumerationPtr(nodemap.GetNode("BalanceWhiteAuto"))->FromString("Off");

    GenApi::CFloatPtr(nodemap.GetNode("ExposureTime"))->SetValue(35000.0);
    GenApi::CFloatPtr(nodemap.GetNode("Gain"))->SetValue(0.0);

    GenApi::CFloatPtr(nodemap.GetNode("Gamma"))->SetValue(1.5);

    GenApi::CEnumerationPtr(nodemap.GetNode("BalanceRatioSelector"))->FromString("Red");
    GenApi::CFloatPtr(nodemap.GetNode("BalanceRatio"))->SetValue(2);

    GenApi::CEnumerationPtr(nodemap.GetNode("BalanceRatioSelector"))->FromString("Blue");
    GenApi::CFloatPtr(nodemap.GetNode("BalanceRatio"))->SetValue(2);



}

void CameraCalibrate::Camera_stop()
{
    camera.StopGrabbing();
    camera.Close();
    Pylon::PylonTerminate();
}
