//main.cpp:
#include "Leexer.h"
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
int main(){

  return 0;
}
