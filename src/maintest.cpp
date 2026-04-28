#include "Gripper.h"


int main() {
    GripperConnection gripper;

    if (!gripper.connect_to_esp32()) {
        std::cerr << "Failed to connect" << std::endl;
        return 1;
    }

    while (true) {
     
        char options;
        std::cout << "Enter 1 to open, 2 to close: ";
        
    std::cin >> options;

    if(options == '1'){
        gripper.gripperOpen();
    }

    else if(options == '2'){
        gripper.gripperClose();
    }

    else{
        std::cout << "Invalid option, try again." << std::endl;
    }

    }
}