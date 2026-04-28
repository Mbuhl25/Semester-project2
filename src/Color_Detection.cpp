#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <vector>
#include <map>
#include <unordered_map>
#include <stdexcept>
#include "Color_Detection.h"

Color_Detection::Color_Detection() {}

    // constructor to make the object
Color_Detection::Color_Detection(std::string cubeType, int videoPort) {
    cap = cv::VideoCapture(videoPort);
    cap >> frame;

    int midt_x = frame.cols / 2;
    int midt_y = frame.rows / 2;
    int afstand = 120;

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

    if (cubeType == "Lucas") {
        // YELLOW
        yellow_lower = cv::Scalar(22, 193, 100);
        yellow_upper = cv::Scalar(37, 246, 255);
        // ORANGE
        orange_lower = cv::Scalar(6, 223, 100);
        orange_upper = cv::Scalar(21, 255, 255);
        // GREEN
        green_lower = cv::Scalar(36, 186, 100);
        green_upper = cv::Scalar(51, 237, 255);
        // WHITE
        white_lower = cv::Scalar(29, 5, 100);
        white_upper = cv::Scalar(89, 41, 255);
        // RED / PINK
        red_lower = cv::Scalar(167, 138, 100);
        red_upper = cv::Scalar(184, 163, 255);
        // BLUE
        blue_lower = cv::Scalar(93, 139, 100);
        blue_upper = cv::Scalar(109, 174, 255);
    } else if (cubeType == "Mathi") {
        // YELLOW
        yellow_lower = cv::Scalar(22, 100, 120);
        yellow_upper = cv::Scalar(35, 255, 255);
        // ORANGE
        orange_lower = cv::Scalar(10, 130, 120);
        orange_upper = cv::Scalar(21, 255, 255);
        // GREEN
        green_lower = cv::Scalar(40,  60,  70);
        green_upper = cv::Scalar(85,  255, 255);
        // WHITE
        white_lower = cv::Scalar  (0,   0,   150);
        white_upper = cv::Scalar  (179, 55,  255);
        // RED
        red_lower = cv::Scalar  (0,  140,  80);
        red_upper = cv::Scalar  (8,  255, 255);
        // BLUE
        blue_lower = cv::Scalar(90,  60,  80);
        blue_upper = cv::Scalar(120, 255, 255);
    } else if (cubeType == "Gammel") {
        // YELLOW
        yellow_lower = cv::Scalar(30, 120, 190);
        yellow_upper = cv::Scalar(40, 255, 255);

        // ORANGE
        orange_lower = cv::Scalar(5, 150, 200);
        orange_upper = cv::Scalar(15, 255, 255);

        // GREEN
        green_lower = cv::Scalar(60, 120, 140);
        green_upper = cv::Scalar(75, 255, 200);

        // WHITE
        white_lower = cv::Scalar(0, 0, 190);
        white_upper = cv::Scalar(179, 30, 255);

        // RED
        red_lower = cv::Scalar(0, 150, 90);
        red_upper = cv::Scalar(4, 255, 180);

        // BLUE
        blue_lower = cv::Scalar(95, 180, 130);
        blue_upper = cv::Scalar(110, 255, 200);
    } else {
        throw std::invalid_argument("Unknown Cubetype. Pls insert which cube you are using");
    }
    lowers = {blue_lower, green_lower, yellow_lower, orange_lower, white_lower, red_lower};
    uppers = {blue_upper, green_upper, yellow_upper, orange_upper, white_upper, red_upper};

    letters = {"B", "G", "Y", "O", "W", "R"};
}

std::string Color_Detection::get_color(cv::Mat hsv, int x, int y){
    cv::Vec3b pixel = hsv.at<cv::Vec3b>(y,x);
    int h = pixel[0];
    int s = pixel[1];
    int v = pixel[2];

    std::string color;

    for (int i = 0; i < lowers.size(); ++i) {
        if (h >= lowers[i][0] && h <= uppers[i][0] &&
            s >= lowers[i][1] && s <= uppers[i][1] &&
            v >= lowers[i][2] && v <= uppers[i][2])
            {
            color = letters[i];
        }
    }
    if (color.empty()) {
        return "0";
    }
    return color;
}



std::string Color_Detection::get_color_from_5_points(cv::Mat hsv, int x, int y, int offset = 3) {
    std::vector<std::string> colors = {
        get_color(hsv, x, y),  //midten
        get_color(hsv, x - offset, y), // venstre
        get_color(hsv, x + offset, y), // højre
        get_color(hsv, x, y - offset), // op
        get_color(hsv, x, y + offset) // ned
    };
    cv::Vec3b pixel_1 = hsv.at<cv::Vec3b>(y, x);
    cv::Vec3b pixel_2 = hsv.at<cv::Vec3b>(y, x - offset);
    cv::Vec3b pixel_3 = hsv.at<cv::Vec3b>(y, x + offset);
    cv::Vec3b pixel_4 = hsv.at<cv::Vec3b>(y - offset, x);
    cv::Vec3b pixel_5 = hsv.at<cv::Vec3b>(y + offset, x);
    std::vector<std::string> hsv_values = {
        
    };
    std::map<std::string, int> counts;
    std::string mest;
    int max_count = 0;
    
    for (const auto& c : colors){
        counts[c]++; // Går igennem colors og genner det i maps counts (lavet ovenover) som genner string, og tælelr hvor mange gange den kommer    }
        for (const auto& [color, count] : counts){
            if (count > max_count){
                max_count = count;
                mest = color;
            }
        }
    }
    if (max_count >= 3) {
        return mest;
    }

    return "0";
}


std::string Color_Detection::getOneSide(){
    // Returns 9 letter sequence for one side as a string
    cap >> frame;
    cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
    std::string oneSideLetters = "";
    for (int i = 0; i < points.size(); ++i){
        oneSideLetters += get_color(hsv, points[i].x, points[i].y);//check_color_5_points(hsv, p.x, p.y);
    }
    return oneSideLetters;
}


void Color_Detection::align_cube(){
    // Create the dots on the screen
    // And wait for keypress
    while (true) {
        cap >> frame;
        for (int i = 0; i < points.size(); ++i){
            cv::circle(frame, points[i], 3, cv::Scalar(0, 255, 0), -1);
        }
        cv::imshow("Frame", frame);

        char key = (char)cv::waitKey(1);
        if (key == 'q' || key == 'Q') {
            print_hsv_values();
            break;
        }
        if (key == 'p'){   
            print_hsv_values();
        }
}
}


std::string Color_Detection::scan_whole_cube(){
    std::vector<std::string> expected = {"Y", "O", "G", "W", "R", "B"};
    std::string fullstring = "";
    for (int i = 0; i < expected.size(); i++){
        std::string scanned = "";
        bool fail = false;
        while (true) {
            std::cout<< "Du skal vise side: "<< expected[i]<< std::endl;
            align_cube();  
            scanned = getOneSide();
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


std::string Color_Detection::rename(std::string input){
    std::string finalString;
    std::unordered_map<char, char> convert = {
    {'R', 'L'},
    {'O', 'R'},
    {'G', 'F'},
    {'Y', 'U'},
    {'W', 'D'}
    };
    for (char i : input){
        auto it = convert.find(i)
        if (it != convert.end()){ // hvis it ikke rammer conver.end hvilket betyder at den har ramt noget i convert, skal den tilføje den converterede string til finalstring
            finalString += it->second;

        }else { // hvis i ( en string fra input) ikke findes i convert skal den tilføje i til finalstring
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
    

std::string Color_Detection::one_side(std::vector<cv::Point> punkter, std::string color){
std::string fullstring = "";
    std::string scanned = "";
    bool fail = false;
    while (true) {
        std::cout<< "Du skal vise side: "<< color << std::endl;
        align_cube();  
        scanned = getOneSide();
        std::cout << scanned << std::endl;
        if (scanned[4] != color[0]){
            std::cout<< "Du skal vise side: "<< color << std::endl;
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
    
    return fullstring;
}

std::string Color_Detection::rename_colors_to_orientations(std::string input){
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
        if (it != convert.end()) { // hvis it ikke rammer conver.end hvilket betyder at den har ramt noget i convert, skal den tilføje den converterede string til finalstring
            finalString += it->second;

        }else { // hvis i ( en string fra input) ikke findes i convert skal den tilføje i til finalstring
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

void Color_Detection::print_cube(){
    std::cout<< rename_colors_to_orientations(scan_whole_cube())<< std::endl;

}

void Color_Detection::print_side(std::string color){
    std::cout<< rename_colors_to_orientations(scan_one_side(color))<< std::endl;
}

void Color_Detection::print_hsv_values(){
    cap >> frame;
    cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

    for(int i = 0; i < points.size(); i++){
        cv::Vec3b pixel = hsv.at<cv::Vec3b>(points[i].y,points[i].x);

        int h = pixel[0];
        int s = pixel[1];
        int v = pixel[2];    

        // std::cout << "point : " << i+1 << std::endl;
        std::cout << h << ", " << s << ", " << v << std::endl;
    }
}
