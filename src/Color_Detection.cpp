#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <vector>
#include <map>
#include <unordered_map>


std::vector<cv::Point> punkter(){

    cv::Mat frame = cv::imread("image.jpg");

    int h = frame.rows; 
    int w = frame.cols;
    int midt_x = w / 2;
    int midt_y = h / 2;
    int afstand = 120;

    std::vector<cv::Point> points;

    int top_left_x = midt_x - afstand;
    int top_left_y = midt_y - afstand;

    int midt_left_x = midt_x - afstand;
    int midt_left_y = midt_y;

    int bot_left_x = midt_x - afstand;
    int bot_left_y = midt_y + afstand;

    int top_midt_x = midt_x;
    int top_midt_y = midt_y - afstand;

    int bot_midt_x = midt_x;
    int bot_midt_y = midt_y + afstand;

    int top_rigtht_x = midt_x + afstand;
    int top_rigtht_y = midt_y - afstand;

    int midt_right_x = midt_x + afstand;
    int midt_right_y = midt_y;

    int bot_right_x = midt_x + afstand;
    int bot_right_y = midt_y + afstand;

    points.push_back(cv::Point(midt_x, midt_y));
    points.push_back(cv::Point(midt_left_x, midt_left_y));
    points.push_back(cv::Point(top_left_x, top_left_y));
    points.push_back(cv::Point(bot_left_x, bot_left_y));
    points.push_back(cv::Point(top_midt_x, top_midt_y));
    points.push_back(cv::Point(bot_midt_x, bot_midt_y));
    points.push_back(cv::Point(top_rigtht_x, top_rigtht_y));
    points.push_back(cv::Point(midt_right_x, midt_right_y));
    points.push_back(cv::Point(bot_right_x, bot_right_y));

    return points;
}

cv::Scalar blue_lower(85, 60, 60);
cv::Scalar blue_upper(130, 255, 255);

// Green
cv::Scalar green_lower(35, 50, 50);
cv::Scalar green_upper(85, 255, 255);

// Yellow
cv::Scalar yellow_lower(18, 80, 80);
cv::Scalar yellow_upper(38, 255, 255);

// Orange
cv::Scalar orange_lower(5, 80, 80);
cv::Scalar orange_upper(17, 255, 255);

// White
cv::Scalar white_lower(0, 0, 140);
cv::Scalar white_upper(179, 80, 255);

// Pink
cv::Scalar pink_lower(135, 60, 60);
cv::Scalar pink_upper(175, 255, 255);
// Blue
std::vector<cv::Scalar> lowers = {blue_lower, green_lower, yellow_lower, orange_lower, white_lower, pink_lower};
std::vector<cv::Scalar> uppers = {blue_upper, green_upper, yellow_upper, orange_upper, white_upper, pink_upper};
std::vector<std::string> letters = {"B", "G", "Y", "O", "W", "R"};

std::string check_colour(cv::Mat hsv, int x, int y){
    cv::Vec3b pixel = hsv.at<cv::Vec3b>(y,x);
    int h = pixel[0];
    int s = pixel[1];
    int v = pixel[2];

    std::string color;

    for (int i = 0; i < lowers.size(); ++i) {
        if (h >= lowers[i][0] && h <= uppers[i][0] &&
        s >= lowers[i][1] && s <= uppers[i][1] &&
        v >= lowers[i][2] && v <= uppers[i][2]) {
            color + letters[i];
        }
    }
    return color;
}



std::string check_color_5_points(cv::Mat hsv, int x, int y, int offset = 5){

    std::vector<std::string> colors = {
        check_colour(hsv, x, y),  //midten
        check_colour(hsv, x - offset, y), // venstre
        check_colour(hsv, x + offset, y), // højre
        check_colour(hsv, x, y - offset), // op
        check_colour(hsv, x, y + offset) // ned
    };
    std::map<std::string, int> counts;
    std::string mest;
    int max_count = 0;
    
    for (const auto& c: colors){
        counts[c]++;
    }
    for (const auto& [color, count] : counts){
        if (count > max_count){
            max_count = count;
            mest = color;
        }
    }
    if (max_count >= 3) {
        return mest;
    }

    return "0";
}


std::string get_string(std::vector<cv::Point>& punkter){
    cv::VideoCapture cap(0);
    cv::Mat frame, hsv;
    cap >> frame;
    
    cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
    std::string x = "";
    for (const auto& p : punkter){
        x += check_color_5_points(hsv, p.x, p.y);
    }
    return x;
}


void align_cube(std::vector<cv::Point>& punkter){
    cv::VideoCapture cap(0);
    cv::Mat frame;
    while (true) {
        cap.read(frame);
        for (const auto& p : punkter){
            cv::circle(frame, p, 3, cv::Scalar(0, 255, 0), -1);
        }
        cv::imshow("Frame", frame);
        char key = (char)cv::waitKey(1);

        if (key == 'q' || key == 'Q') {
            break;
    }
}
}


std::string whole_cube(std::vector<cv::Point>& punkter){
    std::string x = "";
    std::string string = "";
    std::vector<std::string> expected = {"Y", "O", "G", "W", "R", "B"};

    for (int i{}; i < expected.size(); i++){
        while (true) {
            std::cout<< "Du skal vise side: "<< expected[i]<< std::endl;
            align_cube(punkter);  
            std::string string = get_string(punkter);
            std::cout<< string<<std::endl;
            if (string[4] != expected[i][0]){
                std::cout<< "Du skal vise side: "<< expected[i]<< std::endl;
                continue;
            }
            for (char i : x){
                if (i == '0'){
                    std::cout<< "Den har misset en af felterne prøv igen" << std::endl;
                    continue;
                } else  {
                    std::cout<< "Du har detected denne side "<< x << std::endl;
                    string += x;
                    break;
                }
            }

            

        }
    }
    return string;
    
}
std::string rename(std::string){
    std::string finalString;
    std::unordered_map<char, char> convert = {
    {'R', 'L'},
    {'O', 'R'},
    {'G', 'F'},
    {'Y', 'U'},
    {'W', 'D'}
    };
    for (char i : string){
        auto it = convert.find(i);
        if (it != convert.end()){
            finalString += it->second;

        }else {
            finalString += i;
        }
    }
    std::cout<< finalString<< std::endl;

    for (const auto s : finalString){
        counts[s]++;
    }for (const auto [color, count] : counts){
        std::cout<< color << " : " << count<< std::endl;
    }
    return finalString;
    


}

