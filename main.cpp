#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "boxfilter.h"
#include "identityfilter.h"
#include "medianfilter.h"

using namespace std;

int main() {
    stringstream filename;
    // Read a PPM image
    int width, height;
    int n;
    int kernelSize = 0;
    string inputFilename;
    //vector<vector<int>> image = readP2PPM(inputFilename, width, height);
    cout << "Please input your file name (ppm file)" << endl;
    cin >> inputFilename;
    vector<unsigned char> inputImage;
    if (!readPPM(inputFilename, inputImage, width, height)) {
        return -1;
    }
   //cout << "Please input your file name (ppm file)" << endl;
    //cin >> inputFilename;
    cout << "Filter system" << endl;
    cout << "1. Boxfilter filter" << endl;
    cout << "2. Identity filter" << endl;
    cout << "3. Median filter" << endl;
    cout << "Please choose the filter ";
    cin >> n;
    switch (n)
    {
    case 1:
        cout << "Please input the size(3, 5, 7, 31)" << endl;
        cin >> kernelSize;
        generate(inputImage, width, height, kernelSize);
        cout << "the image is successfully output" << endl;
        break;
    case 2:
        writeP2PPM("output.ppm",readP2PPM(inputFilename,width,height),width,height);
        writeAsciiArt_I("ascii_art.txt",readP2PPM(inputFilename,width,height),width,height);
        cout << "the image is successfully output"<< endl;
        break;
    case 3:
        cout << "Please input the size(3, 5, 7)" << endl;
        cin >> kernelSize;
        writeP2("output.ppm",medianFilter(readP2(inputFilename,width,height),width,height,kernelSize),width,height);
        writeAsciiArt("ascii_art.txt",medianFilter(readP2(inputFilename,width,height),width,height,kernelSize),width,height);
        //asciiArtToFile("output.ppm",width,height,file)
        cout << "the image is successfully output" << endl;
        break;
    
    default:
        break;
    }


    

    return 0;
}
