#ifndef COLOR_DETECTION_H
#define COLOR_DETECTION_H
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <vector>
#include <map>
#include <unordered_map>

class Color_Detection {
public:
    Color_Detection();
    Color_Detection(std::string, int);

    std::string get_color(cv::Mat, int, int);
    std::string get_color_from_5_points(cv::Mat, int, int, int);
    std::string getOneSide();
    std::string scan_whole_cube();
    std::string scan_one_side(std::string);
    void align_cube();
    std::string rename_colors_to_orientations(std::string input);

    void print_cube();
    void print_side(std::string color);
    
private:
    cv::Mat frame;
    cv::Mat hsv;
    cv::VideoCapture cap;
    std::vector<cv::Point> points;
    std::vector<std::string> letters;
    std::vector<cv::Scalar> lowers;
    std::vector<cv::Scalar> uppers;
    // Blue
    cv::Scalar blue_lower;
    cv::Scalar blue_upper;
    // Green
    cv::Scalar green_lower;
    cv::Scalar green_upper;
    // Yellow
    cv::Scalar yellow_lower;
    cv::Scalar yellow_upper;
    // Orange
    cv::Scalar orange_lower;
    cv::Scalar orange_upper;
    // Red
    cv::Scalar red_lower;
    cv::Scalar red_upper;
    // White
    cv::Scalar white_lower;
    cv::Scalar white_upper;
};

#endif