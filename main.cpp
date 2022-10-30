//
// Created by Nathan Fenwick on 30/10/2022.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <cmath>

using namespace std;
bool check_fp(const string& fp);
bool selection(const string& choice, const string& path);

class csvItem{
public:
    int numCols;
    vector<vector<int> > columns;
    vector<string> names;
    explicit csvItem(const string& aPath){
        setColumns(aPath);
    }

    void setColumns(const string& aPath){
        // Open the CSV.
        ifstream currentFile;
        currentFile.open(aPath);
        string currentLine;

        // Get the names and number of columns
        getline(currentFile, currentLine);
        int count = 0;
        stringstream colNames(currentLine);
        while (colNames.good()){
            string sub;
            getline(colNames, sub, ',');
            names.push_back(sub);
            count++;
        }
        numCols = count;
        vector< vector<int> >values(count);
        // Parses given CSV and stores data.
        while (getline(currentFile, currentLine)){
            int i = 0;
            stringstream inputString(currentLine);
            while (inputString.good()){
                string currentVal;
                getline(inputString, currentVal, ',');
                values[i].push_back(stoi(currentVal));
                i++;
            }

        }
        columns = values;
        currentFile.close();
    }

    void printFloat(vector<float> values){
        for (int i = 0; i < numCols; ++i) {
            cout << names[i] << endl;
            cout << values[i] << endl;
        }
    }

    void printInt(vector<int> values){
        for (int i = 0; i < numCols; ++i) {
            cout << names[i] << endl;
            cout << values[i] << endl;
        }
    }

    void printAll(){
        for (size_t j = 0; j < columns.size(); j++) {
            cout << names[j] << endl;
            for (size_t i = 0; i < columns[0].size(); i++) {
                cout << columns[j][i] << endl;
            }
        }
    }

    vector<int> calcSums(){
        vector<int> sums;
        for (int i = 0; i < numCols; ++i) {
            int count = 0;
            for (int j = 0; j < columns[i].size(); ++j) {
                count += columns[i][j];
            }
            sums.push_back(count);
        }
        return sums;
    }

    vector<float> calcMeans(){
        vector<float> means;
        vector<int> sums = calcSums();
        for (int i = 0; i < numCols; ++i) {
            means.push_back(float(sums[i]) / float(columns[i].size()));
        }
        return means;
    }

    vector<float> calcStds(){
        vector<float> stds(numCols);
        vector<float> means = calcMeans();
        for (int i = 0; i < numCols; ++i) {
            int length = columns[i].size();
            for (int j = 0; j < length; ++j) {
                stds[i] += pow(columns[i][j] - means[i], 2);
            }
            stds[i] = sqrt(stds[i]/length);
        }
        return stds;
    }

    void printSums(){
        vector<int> sumsValues = calcSums();
        printInt(sumsValues);
    }

    void printMeans(){
        vector<float> meansValues = calcMeans();
        printFloat(meansValues);
    }

    void printStds(){
        vector<float> stdsValues = calcStds();
        printFloat(stdsValues);
    }

};

/**
How to run:
g++ main.cpp -o main
./main file_path operation_name
**/
int main(int argc, char** argv) {
    // Check if valid number of arguments passed.
    if (argc > 3){
        cerr << "Please pass a valid number of arguments" << endl;
        return 1;
    }

    string path = argv[1];
    string operation = argv[2];
    // Check to see if file path and operator are valid.
    if (!check_fp(path)){
        cerr << "Please pass a valid file path" << endl;
        return 1;
    }
    if (!selection(operation, path)){
        cerr << "Please pass a valid operation" << endl;
        return 1;
    }
    return 0;
}

bool check_fp(const string& fp){
    // Check to see if file exists.
    ifstream check(fp);
    if (!check){
        return false;
    }
    check.close();
    return true;
}

bool selection(const string& choice, const string& path){
    csvItem obj1(path);
    if (choice == "print"){
        obj1.printAll();
    }
    else if (choice == "sum"){
        obj1.printSums();
    }
    else if (choice == "mean"){
        obj1.printMeans();
    }
    else if (choice == "std"){
        obj1.printStds();
    }
    else{
        return false;
    }
    return true;
}

