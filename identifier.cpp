#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <cctype>

using namespace std;

// Set of C++ keywords
set<string> keywords = {
    "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor", "bool", "break",
    "case", "catch", "char", "char16_t", "char32_t", "class", "compl", "const", "constexpr",
    "const_cast", "continue", "decltype", "default", "delete", "do", "double", "dynamic_cast",
    "else", "enum", "explicit", "export", "extern", "false", "float", "for", "friend", "goto",
    "if", "inline", "int", "long", "mutable", "namespace", "new", "noexcept", "not", "not_eq",
    "nullptr", "operator", "or", "or_eq", "private", "protected", "public", "register",
    "reinterpret_cast", "return", "short", "signed", "sizeof", "static", "static_assert",
    "static_cast", "struct", "switch", "template", "this", "thread_local", "throw", "true",
    "try", "typedef", "typeid", "typename", "union", "unsigned", "using", "virtual", "void",
    "volatile", "wchar_t", "while", "xor", "xor_eq"
};

// Function to check if a token is a number
bool isNumber(const string& token) {
    for (char ch : token) {
        if (!isdigit(ch)) return false;
    }
    return true;
}

// Function to tokenize the input string
vector<string> tokenize(const string& code) {
    vector<string> tokens;
    stringstream ss(code);
    string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to check if a token is an identifier
bool isIdentifier(const string& token) {
    if (keywords.count(token) || isNumber(token) || !isalpha(token[0])) {
        return false;
    }
    for (char ch : token) {
        if (!isalnum(ch) && ch != '_') {
            return false;
        }
    }
    return true;
}

int main() {
    // Example code string
    //string code = "int main() { int x = 10; float y = 20.5; x = x + y; return 0; }";
    string code;
    while(getline(cin,code))
    {

    // Tokenize the input code
    vector<string> tokens = tokenize(code);

    // Process and remove identifiers
    vector<string>vv;
    for (const string& token : tokens) {
        if (!isIdentifier(token)) {
             vv.push_back(token);
        }
    }
    for(auto x:vv)
    {
        cout<<x<<endl;
    }
    }

    return 0;
}
