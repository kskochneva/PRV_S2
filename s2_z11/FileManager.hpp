#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <string>
#include <fstream>
#include "Group.hpp"

#pragma pack(push, 1)
struct FileHeader {
    char signature[4];
    uint32_t version;
    uint32_t studentCount;
    char groupName[50];
};
#pragma pack(pop)

class FileManager {
public:
    static bool saveGroup(const Group& group, const std::string& filename);
    static bool loadGroup(Group& group, const std::string& filename);

private:
    static bool writeString(std::ofstream& file, const std::string& str);
    static bool readString(std::ifstream& file, std::string& str);
};

#endif