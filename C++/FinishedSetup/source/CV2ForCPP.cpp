#include "CV2ForCPP.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

void CV::useCamera() {
    cv::VideoCapture cap(2); // 0 = default camera

    if (!cap.isOpened()) {
        std::cerr << "Error: Cannot open camera" << std::endl;
        return;
    }

    cv::Mat frame;

    std::cout << "Press ESC to exit." << std::endl;

    while (true) {
        cap >> frame;              // capture a frame
        if (frame.empty()) break;  // check if frame is valid

        cv::imshow("Camera Feed", frame); // show live video

        int key = cv::waitKey(1);
        if (key == 27) break; // ESC key exits
    }

    cap.release();
    cv::destroyAllWindows();
}