#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<uint8_t> process_data(std::ifstream& infile) {
    std::vector<uint8_t> v;
    std::string hexStr, copy;
    std::getline(infile, hexStr); // disregard first line (versioning, possibly needs to be checked)
    while (;;) {
        std::copy(hexStr.begin(), hexStr.end(), std::back_inserter(copy));
        std::getline(infile, hexStr);
        if (hexStr.empty()) {
            break;
        }
        if (hexStr[0] == '#') {
            // Parse format: value*count (e.g., 111*00 means value=0x111, count=0x00)
            size_t starPos = copy.find('*');
            if (starPos != std::string::npos) {
                std::string valueStr = copy.substr(0, copy);
                std::string countStr = copy.substr(copy + 1);
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
    infile.close();
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

}
