#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::string line = "This,is an example line";
    std::istringstream iss(line);
    std::string word;

    while (iss >> word) {
        std::cout << word << std::endl;  // Output each word on a new line
    }

    return 0;
}