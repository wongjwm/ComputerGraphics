// Include our custom library
#include "../include/PPM.h"
#include <iostream>
#include <fstream>
#include "ppm.cpp"

using namespace std;

// to compile: g++ main.cpp -o main -std=c++11
// run: ./main file_path
// ex. "./main ../textures/test.ppm"
int main(int argc, char** argv) {

    if (argc != 2) {
        std::cout << "Oops, 2  arguments needed.\n";
        std::cout << "file_path\n";
        return 0;
    }
    
    string fileName = argv[1];
    string outputFile = "../textures/" + fileName.substr(0, fileName.size() - 4) + "_darken.ppm";

    PPM myPPM(argv[1]);
    myPPM.darken();
    myPPM.savePPM(outputFile);
    return 0;
}