// src/FileManager.cpp
#include "FileManager.h"
#include <fstream>
#include <sstream>

bool FileManager::saveFrequencies(const std::string& filename,
                                  const std::map<std::string, int>& frequencies) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        return false;
    }

    // Write each string sequence and frequency to the file
    for (const auto& pair : frequencies) {
        outFile << pair.first << " " << pair.second << '\n';
    }

    outFile.close();
    return true;
}

bool FileManager::loadFrequencies(const std::string& filename,
                                  std::map<std::string, int>& frequencies) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        return false;
    }

    frequencies.clear(); // Clear existing frequencies before loading new ones
    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string sequence;
        int freq;

        // Extract the sequence (up to the space) and the frequency
        if (std::getline(iss, sequence, ' ') && (iss >> freq)) {
            frequencies[sequence] = freq;
        }
    }

    inFile.close();
    return true;
}
