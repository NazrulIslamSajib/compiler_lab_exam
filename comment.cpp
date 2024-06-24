#include <iostream>
#include <string>

using namespace std;

// Function to remove comments from C++ code
string removeComments(const string& code) {
    string result;
    bool inSingleLineComment = false;
    bool inMultiLineComment = false;
    for (size_t i = 0; i < code.size(); ++i) {
        if (inSingleLineComment) {
            if (code[i] == '\n') {
                inSingleLineComment = false;
                result += code[i]; // Keep the newline character
            }
        } else if (inMultiLineComment) {
            if (code[i] == '*' && i + 1 < code.size() && code[i + 1] == '/') {
                inMultiLineComment = false;
                ++i; // Skip the '/' character
            }
        } else {
            if (code[i] == '/' && i + 1 < code.size() && code[i + 1] == '/') {
                inSingleLineComment = true;
                ++i; // Skip the second '/' character
            } else if (code[i] == '/' && i + 1 < code.size() && code[i + 1] == '*') {
                inMultiLineComment = true;
                ++i; // Skip the '*' character
            } else {
                result += code[i];
            }
        }
    }
    return result;
}

int main() {
    // Example code with comments
    string code;
    while(getline(cin,code))
    {
    string cleanedCode = removeComments(code);
    cout << "Cleaned Code:\n" << cleanedCode << endl;
    }

    return 0;
}
