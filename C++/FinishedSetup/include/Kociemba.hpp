#ifndef KOCIEMBACLASS_H
#define KOCIEMBACLASS_H

#include <string>

class Kociemba {
public:
    Kociemba();                  // constructor
    ~Kociemba();                 // destructor

    std::string solve(const std::string &cube);  // main function
    void func();                 // simple test function
};

#endif // KOCIEMBACLASS_H