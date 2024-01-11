#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

// Function to read a P2 file (grayscale PPM)
std::vector<std::vector<int>> readP2(const std::string& filename, int& width, int& height) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(1);
    }

    std::string magic;
    file >> magic >> width >> height;

    int maxColor;
    file >> maxColor;

    std::vector<std::vector<int>> image(height, std::vector<int>(width));

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int value;
            file >> value;
            image[i][j] = value;
        }
    }

    file.close();

    return image;
}

// Function to write a P2 file (grayscale PPM)
void writeP2(const std::string& filename, const std::vector<std::vector<int>>& image, int width, int height) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        exit(1);
    }

    file << "P2\n" << width << " " << height << "\n255\n";

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            file << image[i][j] << " ";
        }
        file << "\n";
    }

    file.close();
}

// Function to apply a median filter to a 2D vector (image)
std::vector<std::vector<int>> medianFilter(const std::vector<std::vector<int>>& image, int width, int height, int filterSize) {
    int filterRadius = filterSize / 2;
    std::vector<std::vector<int>> result(height, std::vector<int>(width));

    for (int i = filterRadius; i < height - filterRadius; ++i) {
        for (int j = filterRadius; j < width - filterRadius; ++j) {
            std::vector<int> neighborhood;
            for (int x = -filterRadius; x <= filterRadius; ++x) {
                for (int y = -filterRadius; y <= filterRadius; ++y) {
                    neighborhood.push_back(image[i + x][j + y]);
                }
            }

            std::sort(neighborhood.begin(), neighborhood.end());
            result[i][j] = neighborhood[neighborhood.size() / 2];
        }
    }

    return result;
}

void writeAsciiArt(const std::string& filename, const std::vector<std::vector<int>>& image, int width, int height) {
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
