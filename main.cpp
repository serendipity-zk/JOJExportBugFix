#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <vector>
#include "jojBugFix.h"

using namespace std;

int main(int argc, char *argv[]) {
    string filename;
    switch (argc) {
        case 1:
            cin >> filename;
            fixBug(filename);
            break;
        case 2:
            filename = argv[1];
            fixBug(filename);
            break;
        case 3:
            filename = argv[1];
            fixBug(filename, argv[2]);
        default:
            cout << "wrong input!" << endl;
    }
    return 0;
}
