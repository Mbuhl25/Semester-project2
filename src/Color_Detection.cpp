#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <vector>
#include <map>
#include <unordered_map>

cv::VideoCapture cap(3);
cv::Mat frame;
cv::Mat hsv;


// BLUE
cv::Scalar blue_lower   (85, 60, 60);
cv::Scalar blue_upper   (130, 255, 255);

// GREEN
cv::Scalar green_lower  (35, 50, 50);
cv::Scalar green_upper  (85, 255, 255);

// YELLOW
cv::Scalar yellow_lower (20, 100, 100);
cv::Scalar yellow_upper (32, 255, 255);

// ORANGE
cv::Scalar orange_lower (5, 120, 120);
cv::Scalar orange_upper (15, 255, 255);

// WHITE (low saturation, high value)
cv::Scalar white_lower  (0, 0, 140);
cv::Scalar white_upper  (179, 80, 255);

// RED / PINK  (split avoided by restriction)
cv::Scalar pink_lower   (150, 90, 80);
cv::Scalar pink_upper   (175, 255, 255);


std::vector<cv::Scalar> lowers = {blue_lower, green_lower, yellow_lower, orange_lower, white_lower, pink_lower};
std::vector<cv::Scalar> uppers = {blue_upper, green_upper, yellow_upper, orange_upper, white_upper, pink_upper};
std::vector<std::string> letters = {"B", "G", "Y", "O", "W", "R"};

std::vector<cv::Point> punkter(){

    cap >> frame;

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

    points.push_back(cv::Point(top_left_x, top_left_y));
    points.push_back(cv::Point(top_midt_x, top_midt_y));
    points.push_back(cv::Point(top_rigtht_x, top_rigtht_y));
    points.push_back(cv::Point(midt_left_x, midt_left_y));
    points.push_back(cv::Point(midt_x, midt_y));
    points.push_back(cv::Point(midt_right_x, midt_right_y));
    points.push_back(cv::Point(bot_left_x, bot_left_y));
    points.push_back(cv::Point(bot_midt_x, bot_midt_y));
    points.push_back(cv::Point(bot_right_x, bot_right_y));

    return points;
}

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
            color = letters[i];
        }
    }
    if (color.empty()) {
        return "0";
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
    cap >> frame;
    cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
    std::string x = "";
    for (const auto& p : punkter){
        x += check_colour(hsv, p.x, p.y);//check_color_5_points(hsv, p.x, p.y);
    }
    return x;
}


void align_cube(std::vector<cv::Point>& punkter){
    while (true) {
        cap >> frame;


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


std::string whole_cube(std::vector<cv::Point> punkter){
    std::vector<std::string> expected = {"Y", "O", "G", "W", "R", "B"};
    std::string fullstring = "";
    for (int i = 0; i < expected.size(); i++){
        std::string scanned = "";
        bool fail = false;
        while (true) {
            std::cout<< "Du skal vise side: "<< expected[i]<< std::endl;
            align_cube(punkter);  
            scanned = get_string(punkter);
            std::cout << scanned << std::endl;
            if (scanned[4] != expected[i][0]){
                std::cout<< "Du skal vise side: "<< expected[i]<< std::endl;
                fail = true;
            }
            for (int i = 0; i < scanned.size(); i++){
                std::cout << scanned[i] << std::endl;
                if (scanned[i] == '0'){
                    std::cout<< "Den har misset en af felterne prøv igen" << std::endl;
                    fail = true;
                }
            }
            if (fail) {
                fail = false;
                continue;
            }
            std::cout<< "Du har detected denne side: "<< scanned << std::endl;
            fullstring += scanned;
            break;
        }
    }
    std::cout << "The cube looks like this:" << fullstring << std::endl;
    return fullstring;
    
}


std::string rename(std::string input){
    std::string finalString;
    std::unordered_map<char, char> convert = {
    {'R', 'L'},
    {'O', 'R'},
    {'G', 'F'},
    {'Y', 'U'},
    {'W', 'D'}
    };
    for (char i : input){
        auto it = convert.find(i);
        if (it != convert.end()){
            finalString += it->second;

        }else {
            finalString += i;
        }
    }
    std::cout<< finalString<< std::endl;

    std::map<char, int> counts;
    for (const auto s : finalString){
        counts[s]++;
    }for (const auto [color, count] : counts){
        std::cout<< color << " : " << count<< std::endl;
    }
    return finalString;
    


}


int main(int argc, char *argv[]){
    std::string sixseven = rename(whole_cube(punkter()));
    std::cout << sixseven << std::endl;
}