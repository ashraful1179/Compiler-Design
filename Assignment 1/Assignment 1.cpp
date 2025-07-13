#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream in("input1.c");
    ofstream out("output.txt");

    if (!in || !out) {
        cout << "Error opening files!" << endl;
        return 1;
    }

    char ch;

    while (in.get(ch)) {
        if (ch == '/') {
            char next = in.peek();
            if (next == '/') {
                while (in.get(ch) && ch != '\n');
                continue;
            } else if (next == '*') {
                in.get();
                while (in.get(ch)) {
                    if (ch == '*' && in.peek() == '/') {
                        in.get();
                        break;
                    }
                }
                continue;
            } else {
                out.put(ch);
                continue;
            }
        } else if (ch == '\n' || ch == '\t') {
            continue;
        } else {
            out.put(ch);
        }
    }

    cout << "Filtered file created successfully." << endl;
    return 0;
}
