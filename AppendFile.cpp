#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

void reversal(const char* inputFile, const char* outputFile) {
    // Opening the file
    ifstream readFile(inputFile, ios::in | ios::ate);
    if (readFile.is_open()) {
        // Finding the file size
        streamsize fileSize = readFile.tellg();
        readFile.seekg(0, ios::beg);
        // No maximum file size check required since it's enforced in the first file
        char* fileCharacters = (char*)malloc(static_cast<size_t>(fileSize));
        if (fileCharacters) {
            // Creating an array comprised of the file characters
            readFile.read(fileCharacters, fileSize);
            // Getting the number of bytes
            streamsize bytesRead = readFile.gcount();
            // Closing readFile immediately after it's been used
            readFile.close();
            if (bytesRead < fileSize) {
                // Making the file size equal to only the number bytes that were read
                fileSize = bytesRead;
            }
            // Reverse the content
            char* fileStart = fileCharacters;
            char* fileEnd = fileCharacters + fileSize - 1;
            while (fileStart < fileEnd) {
                char tempVariable = *fileStart;
                *fileStart = *fileEnd;
                *fileEnd = tempVariable;
                ++fileStart;
                --fileEnd;
            }
            // Outputting the reversed file
            ofstream reversedFile(outputFile, ios::out | ios::trunc);
            if (reversedFile.is_open()) {
                reversedFile.write(fileCharacters, fileSize);
                reversedFile.close();
                cout << "File reversal complete!" << endl;
            } else {
                cout << "A problem occurred, could not reverse file!" << endl;
            }
        } else {
            cout << "Could not allocate memory!" << endl;
        }
        // Freeing memory
        free(fileCharacters);
    } else {
        cout << "A problem occurred while opening the file for reversal!" << endl;
    }
}

int main() {
    // Specifying the file name. The file is assumed to be in the same directory as this program
    ofstream file("CSC450_CT5_mod5.txt", ios::app);

    if (file.is_open()) {
        // Creating a large maximum buffer size to avoid vulnerabilities due to large inputs
        const std::streamsize maxSize = 512 * 512;
        // Starting buffer size before scaling up based on input size
        std::streamsize size = 128;
        // Dynamic memory allocation
        char* textInput = (char*)malloc(static_cast<size_t>(size));
        cout << "Text Input Storage\nType 'save_changes' and press ENTER to exit program\n'save_changes' will not appear in the file\nEnter text input:" << endl;
        while (true) {
            // Using maxSize - 1 to allow room for the null terminator
            cin.getline(textInput, (size > maxSize ? maxSize - 1 : size));
            // Checking to see whether the input is larger than the current buffer size
            if (cin.fail() && !cin.eof()) {
                // Clearing the error state if the input is larger than the buffer size
                cin.clear();
                // Increasing the current buffer size. An integer overflow is also prevented due to the maximum allowed size
                size *= 2;
                // Enforcing the absolute maximum buffer size
                if (size > maxSize) {
                    cout << "Maximum input length exceeded!" << endl;
                    size = maxSize;
                }
                // Reallocating memory to support the increased buffer size
                textInput = (char*)realloc(textInput, static_cast<size_t>(size));
            }
            // The special input for the user to exit the program
            if (strcmp(textInput, "save_changes") == 0) {
                break;
            }
            // Placing the user input in the file
            file << textInput << endl;
        }
        // Deallocating memory and closing the file
        free(textInput);
        file.close();
        cout << "Changes saved!" << endl;
        // Calling the reversal method
        reversal("CSC450_CT5_mod5.txt", "CSC450-mod5-reverse.txt");
    } else {
        // Simple error message
        cout << "A problem occurred while opening the file!" << endl;
    }
    cout << "Exiting..." << endl;
    return 0;
}