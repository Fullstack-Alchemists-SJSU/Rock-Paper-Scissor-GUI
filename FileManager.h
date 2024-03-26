// include/FileManager.h
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <map>

class FileManager {
public:
    bool saveFrequencies(const std::string& filename,
                         const std::map<std::string, int>& frequencies);

    bool loadFrequencies(const std::string& filename,
                         std::map<std::string, int>& frequencies);
};

#endif // FILEMANAGER_H
