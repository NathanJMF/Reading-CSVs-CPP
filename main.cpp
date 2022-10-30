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
        vector<int> c1, c2, c3;

        explicit csvItem(const string& aPath){
            setColumns(aPath);
        }

        void setColumns(const string& aPath){
            // Open the CSV.
            ifstream currentFile;
            currentFile.open(aPath);
            string currentLine;
            getline(currentFile, currentLine);
            // Parses given CSV and stores data.
            while (getline(currentFile, currentLine)){
                stringstream inputString(currentLine);
                string column1, column2, column3;
                getline(inputString, column1, ',');
                c1.push_back(stoi(column1));
                getline(inputString, column2, ',');
                c2.push_back(stoi(column2));
                getline(inputString, column3);
                c3.push_back(stoi(column3));
            }
            currentFile.close();
        }

        static void printVector(vector<int> col1, vector<int> col2, vector<int> col3){
            cout << "Col1 " << "Col2 " << "Col3" << endl;
            for (int i = 0; i < col1.size(); ++i) {
                cout << col1[i]<< "    " << col2[i] << "    " << col3[i] << endl;
            }
        }

        static void printVal(float val1, float val2, float val3){
            cout << "Col1 " << "Col2 " << "Col3" << endl;
            cout << val1 << "    " << val2 << "    " << val3 << endl;
        }

        vector<int> calcSum(){
            vector<int> sums(3);
            for (int i = 0; i < c1.size(); ++i) {
                sums[0] += c1[i];
                sums[1] += c2[i];
                sums[2] += c3[i];
            }
            return sums;
        }

        vector<float> calcMean(){
            vector<int> sums = calcSum();
            vector<float> means (3);
            float length = c1.size();
            means[0] = float(sums[0])/length;
            means[1] = float(sums[1])/length;
            means[2] = float(sums[2])/length;
            return means;
        }

        vector<float> calcStd(){
            vector<float> means = calcMean();
            vector<float> stds(3);
            int length = c1.size();
            for (int i = 0; i < length; ++i) {
                stds[0] += pow(c1[i] - means[0], 2);
                stds[1] += pow(c2[i] - means[1], 2);
                stds[2] += pow(c3[i] - means[2], 2);
            }
            stds[0] = sqrt(stds[0]/length);
            stds[1] = sqrt(stds[1]/length);
            stds[2] = sqrt(stds[2]/length);
            return stds;
        }

        void print() const{
            printVector(c1, c2, c3);
        }

        void printSum(){
            vector<int> sums = calcSum();
            printVal(float(sums[0]), float(sums[1]), float(sums[2]));
        }

        void printMean(){
            vector<float> item = calcMean();
            printVal(item[0], item[1], item[2]);
        }

        void printStd(){
            vector<float> stds = calcStd();
            printVal(stds[0], stds[1], stds[2]);
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
        obj1.print();
    }
    else if (choice == "sum"){
        obj1.printSum();
    }
    else if (choice == "mean"){
        obj1.printMean();
    }
    else if (choice == "std"){
        obj1.printStd();
    }
    else{
        return false;
    }
    return true;
}

