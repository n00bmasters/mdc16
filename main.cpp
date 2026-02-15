#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::vector<uint8_t> process_data(std::ifstream& infile) {
    std::vector<uint8_t> v;
    std::string hexStr, copy;
    std::getline(infile, hexStr); // disregard first line (versioning, possibly needs to be checked)
    while (1) {
        std::copy(hexStr.begin(), hexStr.end(), std::back_inserter(copy));
        std::getline(infile, hexStr);
        if (hexStr.empty()) {
            break;
        }
        if (hexStr[0] == '#') {
            // Parse format: value*count (e.g., 111*00 means value=0x111, count=0x00)
            std::istringstream iss(copy);
            std::string valueStr, countStr;
            if (std::getline(iss, valueStr, '*') && std::getline(iss, countStr)) {
                uint32_t value = std::stoi(valueStr, nullptr, 10);
                uint32_t count = std::stoi(countStr, nullptr, 16);
                for (uint32_t i = 0; i < count; i++) {
                    v.push_back(value & 0xFF);
                }
                continue;
            }
            continue;
        }
        if (hexStr.length() == 2) {
            uint8_t value = std::stoi(hexStr, nullptr, 16);
            v.push_back(value);
        }
    }
    return v;

}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }
    std::ifstream infile(argv[1]);
    if (!infile) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }
    std::vector<uint8_t> data = process_data(infile);
    infile.close();

}
