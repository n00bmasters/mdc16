#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::vector<uint8_t> process_data(std::ifstream& infile) {
    std::vector<uint8_t> v;
    std::string hexStr;
    std::getline(infile, hexStr); // disregard first line (versioning, possibly needs to be checked)
    while (std::getline(infile, hexStr)) {
        auto start = hexStr.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) {
            break;
        }
        auto end = hexStr.find_last_not_of(" \t\r\n");
        hexStr = hexStr.substr(start, end - start + 1);
        if (hexStr.empty()) {
            break;
        }
        if (hexStr[0] == '#') {
            continue;
        }
        auto starPos = hexStr.find('*');
        if (starPos != std::string::npos) {
            std::string valueStr = hexStr.substr(0, starPos);
            std::string countStr = hexStr.substr(starPos + 1);
            if (!valueStr.empty() && !countStr.empty()) {
                uint32_t count = std::stoi(valueStr, nullptr, 10);
                uint32_t value = std::stoi(countStr, nullptr, 16);
                for (uint32_t i = 0; i < count; i++) {
                    v.push_back(value & 0xFF);
                }
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
    // for (auto i : data) {
    //     std::cout << std::hex << static_cast<int>(i) << std::endl;
    // }
    // std::cout << std::endl;
    infile.close();

}
