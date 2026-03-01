#define _CRT_SECURE_NO_WARNINGS
#include "FileManager.hpp"
#include <iostream>
#include <cstring>

bool FileManager::saveGroup(const Group& group, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file for writing: " << filename << "\n";
        return false;
    }

    FileHeader header;

    // Копируем сигнатуру
    memcpy(header.signature, "GRP1", 4);

    header.version = 1;
    header.studentCount = static_cast<uint32_t>(group.getStudentCount());

    // Копируем название группы
    std::string groupName = group.getName();
    size_t copyLength = groupName.length();
    if (copyLength > 49) copyLength = 49;

    memcpy(header.groupName, groupName.c_str(), copyLength);
    header.groupName[copyLength] = '\0';

    // Заполняем остальное нулями
    if (copyLength < 49) {
        memset(header.groupName + copyLength, 0, 49 - copyLength);
    }

    file.write(reinterpret_cast<const char*>(&header), sizeof(header));
    file.close();

    std::cout << "Group saved to " << filename << "\n";
    return true;
}

bool FileManager::loadGroup(Group& group, const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file for reading: " << filename << "\n";
        return false;
    }

    FileHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(header));

    if (memcmp(header.signature, "GRP1", 4) != 0) {
        std::cerr << "Error: Invalid file signature\n";
        return false;
    }

    if (header.version != 1) {
        std::cerr << "Error: Unsupported file version\n";
        return false;
    }

    group.setName(header.groupName);
    file.close();

    std::cout << "Group loaded from " << filename << "\n";
    return true;
}