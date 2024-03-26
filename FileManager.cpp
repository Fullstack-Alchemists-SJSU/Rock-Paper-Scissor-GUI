// FileManager.cpp
#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iostream> // For error logging

bool FileManager::saveFrequencies(const std::string& filename,
                                  const std::map<std::string, int>& frequencies) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return false;
    }

    for (const auto& pair : frequencies) {
        outFile << pair.first << " " << pair.second << '\n';
        if (!outFile) {
            std::cerr << "Failed to write data to file: " << filename << std::endl;
            return false; // Exit if a write error occurs
        }
    }

    return true;
}

bool FileManager::loadFrequencies(const std::string& filename,
                                  std::map<std::string, int>& frequencies) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Failed to open file for reading: " << filename << std::endl;
        return false;
    }

    frequencies.clear();
    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string sequence;
        int freq;

        if (!(iss >> sequence >> freq)) {
            std::cerr << "Invalid data format in file: " << filename << std::endl;
            // Decide whether to return false or continue processing next lines
        } else {
            frequencies[sequence] = freq;
        }
    }

    return true;
}
