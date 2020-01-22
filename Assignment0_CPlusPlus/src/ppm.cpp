#include "../include/PPM.h"
#include <fstream>

using namespace std;

// Constructor loads a filename with the .ppm extension
PPM::PPM(string fileName) {

    ifstream inFile;

    inFile.open(fileName);

    if (inFile.is_open()) {
        
        string line;
        int index = 0;
        
        while (getline(inFile, line) && index != 1) {
            index++;
        }

        inFile >> m_width;
        inFile >> m_height;

        unsigned int size = (m_width * m_height * 3) + 1;
        m_PixelData = new unsigned char[size];

        for (unsigned int i = 0; i < size; i++) {
            int number;
            inFile >> number;
            m_PixelData[i] = number;
        }

        inFile.close();
    }

}

// Destructor clears any memory that has been allocated
PPM::~PPM() {
    delete[] m_PixelData;
}

// Saves a PPM Image to a new file.
void PPM::savePPM(string outputFileName) {

    // opens a file to output 
    ofstream outFile;
    outFile.open(outputFileName);
    outFile << "P3" << endl;
    outFile << "# " + outputFileName << endl;
    outFile << m_width << " " << m_height << endl;

    unsigned int size = (m_width * m_height * 3) + 1;
    for (unsigned int i = 0; i < size; i++) {
        outFile << (int) m_PixelData[i] << endl;
    }
    outFile.close();
}


// Darken subtracts 50 from each of the red, green
// and blue color components of all of the pixels
// in the PPM. Note that no values may be less than
// 0 in a ppm.
void PPM::darken() {
    
    for (int i = 0; i < m_width; i++) {
        for (int j = 0; j < m_height; j++) {
            int index = (m_width * j * 3) + (i * 3);

            int r = (int) m_PixelData[index];
            int g = (int) m_PixelData[index + 1];
            int b = (int) m_PixelData[index + 2];

            if (r > 50 && g > 50 && b > 50) {
                setPixel(i, j, r - 50, g - 50, b - 50);
            }
        }
    }
}

// Sets a pixel to a specific R,G,B value 
void PPM::setPixel(int x, int y, int R, int G, int B) {
    int index = (m_width * y * 3) + (x * 3);
    m_PixelData[index] = (char) R;
    m_PixelData[index + 1] = (char) G;
    m_PixelData[index + 2] =  (char) B;
}