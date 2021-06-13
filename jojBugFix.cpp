//
// Created by MotherShip on 2021/6/14.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <vector>
#include "jojBugFix.h"

using namespace std;

vector<string> separateALine(const string &inputString) {
    vector<string> separateVec;
    istringstream istrStream(inputString);
    string temp;
    while (getline(istrStream, temp, ',')) {
        separateVec.push_back(temp);
    }
    return separateVec;
}

vector<int> findProblemLength(const vector<string> &items) {
    int problemNum = 0;
    vector<int> posVec;
    for (int i = 0; i < items.size(); i++) {
        if (items[i].find("Seconds") != string::npos) {
            posVec.push_back(i);
            problemNum++;
        }
    }
    vector<int> lenVec;
    lenVec.reserve(posVec.size() - 1);
    for (int i = 0; i < posVec.size() - 1; ++i) {
        lenVec.push_back(posVec[i + 1] - posVec[i]);
    }
    lenVec.erase(lenVec.begin());
    return lenVec;
}

void writeALine(ofstream &outCSV, const vector<string> &useful) {
    for (auto i = useful.begin(); i != useful.end(); i++) {
        outCSV << *i;
        if (i + 1 != useful.end()) {
            outCSV << ',';
        }

    }
    outCSV << "\n";
}

vector<string> findUsefulColumns(const vector<string> &items, const vector<int> &lengthVec) {
    vector<string> usefulColumn;
    usefulColumn.push_back(items[1]);//Name;
    usefulColumn.push_back(items[2]);//ID;
    int pos = 7;
    for (int i : lengthVec) {
        if (items[pos] == "-") {
            pos += 4;
            usefulColumn.emplace_back("0");
        } else {
            usefulColumn.emplace_back(items[pos]);
            pos += i;
        }
    }
    return usefulColumn;
}


void fixBug(const std::string &filename, const std::string &outFilename) {
    ifstream inputCSV(filename);
    ofstream outputCSV(outFilename);
    string temp;
    getline(inputCSV, temp);
    if (!inputCSV.is_open()) {
        cout << "Cannot open the file!" << endl;
        exit(1);
    }
    auto sep = separateALine(temp);
    auto lenVec = findProblemLength(sep);
//    for (const auto& i:lenVec) {
//        cout<<i<<endl;
//    }
    auto useful = findUsefulColumns(sep, lenVec);
    writeALine(outputCSV, useful);
//    for (const auto& i:useful) {
//        cout<<i<<endl;
//    }
    while (getline(inputCSV, temp)) {
        sep = separateALine(temp);
        useful = findUsefulColumns(sep, lenVec);
        writeALine(outputCSV, useful);
//        for (const auto& i:useful) {
//            cout<<i<<endl;
//        }
    }
}
