#include <iostream>
#include <opencv2/core.hpp>       // Core data structures (Mat, etc.)
#include <opencv2/imgproc.hpp>    // Image processing
#include <opencv2/highgui.hpp>    // imshow, waitKey, etc.
#include <opencv2/imgcodecs.hpp>  // imread, imwrite
#include <opencv2/videoio.hpp>   // Video capture and writing

int main() {
    // Open the default camera (index 0)
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Could not open camera!" << std::endl;
        return 1;
    }

    cv::Mat image;
    cap >> image; // Capture a frame
    if (image.empty()) {
        std::cerr << "Could not capture a frame!" << std::endl;
        return 1;
    }

    // Convert the image to grayscale
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);

    // Save the processed image
    cv::imwrite("output.jpg", grayImage);

    // Display the original and processed images
    cv::imshow("Original Image", image);
    cv::imshow("Grayscale Image", grayImage);
    cv::waitKey(0); // Wait for a key press

    return 0;
}