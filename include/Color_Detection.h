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
    void cube();
    void side(std::string color);
private:
    std::string whole_cube(std::vector<cv::Point> punkter);
    std::string one_side(std::vector<cv::Point> punkter, std::string color);
    std::string rename(std::string input);
    std::vector<cv::Scalar> lowers;
    std::vector<cv::Scalar> uppers;
    std::vector<std::string> letters;
    std::vector<cv::Point> punkter();
    std::string check_colour(cv::Mat hsv, int x, int y);
    std::string check_color_5_points(cv::Mat hsv, int x, int y, int offset = 5);
    std::string get_string(std::vector<cv::Point>& punkter);
    void align_cube(std::vector<cv::Point>& punkter);
    cv::VideoCapture cap(3);
    cv::Mat frame;
    cv::Mat hsv;



};

#endif