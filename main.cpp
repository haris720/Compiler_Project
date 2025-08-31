//main.cpp:
#include "Lexer.h"
#include <iostream>
#include <vector>
using namespace std;

void printTokens(const vector<Token> &tokens) {
    for (auto &tok : tokens) {
        cout << "[" << tok.type;
        if (!tok.value.empty())
            cout << "(\"" << tok.value << "\")";
        cout << "]";
    }
    cout << "\n";
}

// Function to test bubble sort code
void testBubbleSort(Lexer &lexer) {
    string code =
        "fn void bubbleSort(int arr[], int n) {\n"
        "    for (int i = 0; i < n-1; i++) {\n"
        "        for (int j = 0; j < n-i-1; j++) {\n"
        "            if (arr[j] > arr[j+1]) {\n"
        "                int temp = arr[j];\n"
        "                arr[j] = arr[j+1];\n"
        "                arr[j+1] = temp;\n"
        "            }\n"
        "        }\n"
        "    }\n"
        "}\n";

    cout << "\n--- Bubble Sort Test ---\n";
    printTokens(lexer.tokenize(code));
}

// Function to test escaped strings
void testEscapedStrings(Lexer &lexer) {
    string code = "string s = \"Line1\\nLine2\\tTabbed\\\"Quote\\\"\";";
    cout << "\n--- Escaped String Test ---\n";
    printTokens(lexer.tokenize(code));
}

// Function to test invalid identifiers
void testInvalidIdentifier(Lexer &lexer) {
    string code = "int 123abc = 5;";
    cout << "\n--- Invalid Identifier Test ---\n";
    printTokens(lexer.tokenize(code));
}

// Function to test comments
void testComments(Lexer &lexer) {
    string code =
        "// This is a single-line comment\n"
        "int x = 10; /* This is a\n"
        "multi-line comment */ x = x + 1;";
    cout << "\n--- Comments Test ---\n";
    printTokens(lexer.tokenize(code));
}


void testFunctionWithComments(Lexer &lexer) {
    string code =
        "fn int my_fn(int x, float y) { /* do stuff */\n"
        "    string my_str = \"hmm\"; // assign string\n"
        "    bool my_bool = x == 40;\n"
        "    return x;\n"
        "}\n";
    cout << "\n--- Function With Comments Test ---\n";
    printTokens(lexer.tokenize(code));
}

int main() {
    Lexer lexer;

    testBubbleSort(lexer);
    testEscapedStrings(lexer);
    testInvalidIdentifier(lexer);
    testComments(lexer);
    testFunctionWithComments(lexer); 

    return 0;
}
