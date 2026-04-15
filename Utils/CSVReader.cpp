#include "CSVReader.h"
#include <fstream>
#include <sstream>
#include <iostream>

// ===== DOC CSV CHUAN, CO XU LY BOM + DONG RONG =====
std::vector<std::vector<std::string>>
CSVReader::readCSV(const std::string& filePath) {

    std::vector<std::vector<std::string>> data;
    std::ifstream file(filePath);

    // ❌ KHONG MO DUOC FILE
    if (!file.is_open()) {
        std::cout << "[ERROR] Khong mo duoc file: " << filePath << "\n";
        return data;
    }

    std::string line;
    bool skipHeader = true;

    while (std::getline(file, line)) {

        // ✅ BO DONG RONG
        if (line.empty())
            continue;

        // ✅ BO BOM UTF-8 NEU CO (THUONG GAP KHI CSV TU EXCEL)
        if (skipHeader) {
            if (line.size() >= 3 &&
                static_cast<unsigned char>(line[0]) == 0xEF &&
                static_cast<unsigned char>(line[1]) == 0xBB &&
                static_cast<unsigned char>(line[2]) == 0xBF) {
                line = line.substr(3);
                }
            skipHeader = false;
            continue; // bo header
        }

        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;

        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        // ✅ CHI NHAN DONG HOP LE
        if (!row.empty()) {
            data.push_back(row);
        }
    }

    return data;
}