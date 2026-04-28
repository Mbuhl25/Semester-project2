# Guide to talk with robot

## prerequisite
It is only possible on ubuntu, but should also work in a virtual machine:

First run this in the terminal:
```
sudo apt-get install libboost-all-dev
```

Then go to any folder folder and run this in the terminal:
```
git clone https://gitlab.com/sdurobotics/ur_rtde.git
cd ur_rtde
git submodule update --init --recursive
mkdir build
cd build
cmake ..
make
sudo make install
```
This will create a folder in your current folder called "*ur_rtde*", and install the package system-wide in some folder like: 
"/usr/local/lib/cmake/ur_rtde"

> **NOTE:**  Later you can reference this library in c++ with this include, and you the functions of the class:
> ```
> #include <ur_rtde/rtde_receive_interface.h>
> //example:
> ur_rtde::RTDEControlInterface rtde_control("192.168.1.11");
> ```
# Connecting to the robot
The robot has a static IP and a subnet-mask:
```
IP:          192.168.1.11
subnet-mask: 255.255.255.0
```
You have to give your own computer a static IP. On Ubuntu that is very simple, but I don't know if it is the same way in the virtual machine, since the virtual machine is connected to the same network as the windows computer:

## Ubuntu:
1. Connect the robot to your laptop with a LAN-cable.
2. Click the top right corner, and click the arrow next to the *Wired* box. And click "*Wired settings*"
3. Settings should open up, and click on the cog symbol
4. Under IPv4 Change your IPv4 method to manual and type in an IP-adress like: ```192.168.1.X```, but the X cannot be the same as the robot IP ```(11)```, and write the subnet-mask as ```255.255.255.0```
5. Press apply and enter your password.

## Windows:
Windows 11:

1. Connect the robot to your computer using a LAN cable.
2. Open the Windows Start Menu and search for “Settings”, then open it.
3. Go to: Settings → Network & Internet → Ethernet.
4. Click on your active Ethernet connection.
5. Scroll down to the section called IP assignment.
6. Click the Edit button next to IP assignment.
7. In the dialog that appears: Change Edit IP settings from Automatic (DHCP) to Manual. Enable IPv4.
8. Enter a static IP that matches the robot’s subnet. Type in an IP-adress like: ```192.168.1.X```, but the X cannot be the same as the robot IP ```(11)```, and write the subnet-mask as ```255.255.255.0```
9. Click Save.

# How to build OUR project with cmake
When the steps above are done you can start making a .cpp file. The default structure should be like this:

```
// Include the correct header for the control interface:
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>

int main() {
//YOUR CODE
}
```
## First time
Then when you want to compile it do like this in the terminal. Start in the root of the semesterproject, so the file ends with 
```Semester-project2/RTDE_controls```

Do the following
```
mkdir build
cd build
cmake ..
make -j
    #Run the program with
./ur_rtde_cmake_example  
```

## After first time
Whenever you make changes to the .cpp files, then you just have to run in the build folder:
```
make -j
```

# Example scripts:

Get current joint rotations:
Du modtager koordinaterne i radianer som rotationer {base, Shoulder, Elbow, Wrist1, Wrist2, Wrist3}
```
// C++
RTDEReceiveInterface rtde_receive("192.168.1.11");
std::vector<double> joint_positions = rtde_receive.getActualQ();
```

Move robot to position:
Funktionen tager som input i radianer som rotationer {base, Shoulder, Elbow, Wrist1, Wrist2, Wrist3}
```
// C++
RTDEControlInterface rtde_control("192.168.1.11");
rtde_control.moveL({-0.143, -0.435, 0.20, -0.001, 3.12, 0.04}, 0.5, 0.2);
```


# references
[SDU_Robotics_UR_RTDE](https://sdurobotics.gitlab.io/ur_rtde/installation/installation.html)