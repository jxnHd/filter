#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

// Function to read P2 (grayscale) PPM file
std::vector<std::vector<int>> readP2PPM(const std::string& filename, int& width, int& height) {
    std::ifstream file(filename);
    std::string magicNumber;
    file >> magicNumber >> width >> height;
    
    int maxValue;
    file >> maxValue;

    std::vector<std::vector<int>> image(height, std::vector<int>(width, 0));

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            file >> image[i][j];
        }
    }

    file.close();
    return image;
}

// Function to write P2 (grayscale) PPM file
void writeP2PPM(const std::string& filename, const std::vector<std::vector<int>>& image, int width, int height) {
    std::ofstream file(filename);
    file << "P2\n" << width << " " << height << "\n255\n";

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            file << image[i][j] << " ";
        }
        file << "\n";
    }

    file.close();
}

void writeAsciiArt_I(const std::string& filename, const std::vector<std::vector<int>>& image, int width, int height) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        exit(1);
    }

    // ASCII characters representing different intensity levels
    const std::string asciiChars = "@%#*+=-:. ";

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            // Map the pixel intensity to the corresponding ASCII character
            int intensity = image[i][j] * (asciiChars.size() - 1) / 255;
            file << asciiChars[intensity];
        }
        file << "\n";
    }

    file.close();
}