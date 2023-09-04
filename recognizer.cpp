#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

std::string RecognizeString() {
    // Define the terminal command as a string
    std::string command = "tesseract screenshot.bmp -";

    // Open a pipe to capture the command's output
    FILE* pipe = popen(command.c_str(), "r");

    // Read the output from the pipe into a string
    std::string result;
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

    // Close the pipe
    pclose(pipe);

    // Print or use the captured output
    return result;
}