#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// Function to read a PPM file in P2 format
bool readPPM(const string& filename, vector<unsigned char>& data, int& width, int& height) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open the file." << endl;
        return false;
    }

    string format;
    int maxColor;

    file >> format >> width >> height >> maxColor;

    // Check if the file is in P2 (ASCII grayscale) format
    if (format != "P2") {
        cerr << "Error: Unsupported PPM format. Only P2 (ASCII) format is supported." << endl;
        return false;
    }

    data.resize(width * height);

    for (unsigned char& pixel : data) {
        int value;
        file >> value;
        pixel = static_cast<unsigned char>(value);
    }

    file.close();

    return true;
}

// Function to write a PPM file in P2 format
bool writePPM(const string& filename, const vector<unsigned char>& data, int width, int height) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open the file for writing." << endl;
        return false;
    }

    // Write the P2 header
    file << "P2\n";
    file << width << " " << height << "\n255\n";

    // Write the pixel data
    for (size_t i = 0; i < data.size(); ++i) {
        file << static_cast<int>(data[i]) << " ";
        if ((i + 1) % 10 == 0) {
            file << "\n";
        }
    }

    file.close();

    return true;
}

// Function to apply a box filter to an image with variable kernel size
void boxFilter(const vector<unsigned char>& input, vector<unsigned char>& output, int width, int height, int kernelSize) {
    output.resize(input.size());

    int halfKernelSize = kernelSize / 2;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int startY = max(0, y - halfKernelSize);
            int endY = min(height - 1, y + halfKernelSize);
            int startX = max(0, x - halfKernelSize);
            int endX = min(width - 1, x + halfKernelSize);

            int sum = 0;
            int count = 0;

            for (int i = startY; i <= endY; ++i) {
                for (int j = startX; j <= endX; ++j) {
                    sum += input[i * width + j];
                    count++;
                }
            }

            output[y * width + x] = static_cast<unsigned char>(sum / count);
        }
    }
}

// Function to convert pixel values to ASCII characters for grayscale images and write to a text file
void asciiArtToFile(const vector<unsigned char>& data, int width, int height, const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open the file for writing." << endl;
        return;
    }

    const string asciiChars = "@%#*+=-:. ";

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int pixelValue = data[i * width + j];

            // Map pixel intensity to ASCII character
            char asciiChar = asciiChars[pixelValue * (asciiChars.size() - 1) / 255];
            file << asciiChar;
        }
        file << '\n';
    }

    file.close();
}

// Function to generate high-resolution ASCII art with a single kernel size
void generate(const vector<unsigned char>& input, int width, int height, int kernelSize) {
    // Apply the box filter
    vector<unsigned char> outputImage;
    boxFilter(input, outputImage, width, height, kernelSize);

    // Convert pixel values to ASCII characters and save to a text file
    stringstream filename;
    filename << "output_ascii_art_kernel_" << kernelSize << ".txt";
    asciiArtToFile(outputImage, width, height, filename.str());

    // Write the filtered image to a new PPM file
    stringstream ppmFilename;
    ppmFilename << "output_image_kernel_" << kernelSize << ".ppm";
    writePPM(ppmFilename.str(), outputImage, width, height);
}

