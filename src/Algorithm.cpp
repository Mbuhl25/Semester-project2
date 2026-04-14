#include "Algorithm.h"
#include <iostream>
#include <sstream>
#include <algorithm>

//Sætter L F R B i ring
enum Faces { L = 0, F = 1, R = 2, B = 3 };

//Constructor
Algorithm::Algorithm() {
    ring[0] = L;
    ring[1] = F;
    ring[2] = R;
    ring[3] = B;
}

//Rotation
void Algorithm::rotateD() {
    int temp = ring[3];
    for (int i = 3; i > 0; i--)
        ring[i] = ring[i - 1];
    ring[0] = temp;
}

void Algorithm::rotateDPrime() {
    int temp = ring[0];
    for (int i = 0; i < 3; i++)
        ring[i] = ring[i + 1];
    ring[3] = temp;
}

//Flot move resolver
char Algorithm::resolve(char face) {
    static const char faces[] = {'L','F','R','B'};

    if (face == 'L') return faces[ring[0]];
    if (face == 'F') return faces[ring[1]];
    if (face == 'R') return faces[ring[2]];
    if (face == 'B') return faces[ring[3]];

    return face;
}

//Fjerner whitespace og normaliserer apostroffer
static std::string sanitizeMove(std::string m) {
    
    m.erase(std::remove(m.begin(), m.end(), '\r'), m.end());
    m.erase(std::remove(m.begin(), m.end(), '\n'), m.end());
    m.erase(std::remove(m.begin(), m.end(), ' '), m.end());

    for (char &c : m) {
        if (c == '’') c = '\'';  //normalization
    }

    return m;
}

//Hovedefunktion
std::string Algorithm::switchpoints() {

    std::string result;

    for (auto raw : moves) {

        std::string m = sanitizeMove(raw);

        if (m.empty()) continue;

        if (m == "D") {
            rotateD();
            result += "D ";
            continue;
        }

        if (m == "D'") {
            rotateDPrime();
            result += "D' ";
            continue;
        }

        char face = m[0];
        char out = resolve(face);

        std::string moveOut;
        moveOut += out;

        if (m.size() > 1)
            moveOut += m.substr(1);

        result += moveOut + " ";
    }

    return result;
}

//Laver fra string til vector
std::vector<std::string> Algorithm::FromStringToVec(const std::string& input) {

    std::vector<std::string> result;
    std::stringstream ss(input);
    std::string move;

    while (ss >> move)
        result.push_back(move);

    return result;
}