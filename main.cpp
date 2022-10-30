//
// Created by Nathan Fenwick on 30/10/2022.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
bool check_fp(const string& fp);
bool check_op(const string& op);

class csvItem{
    private:
        vector<int> c1, c2, c3;
        string path;
    public:
        explicit csvItem(string aPath){
            setPath(std::move(aPath));
            setColumns();
        }
        void setPath(string aPath){
            path = std::move(aPath);
        }
        string getPath(){
            return path;
        }
        void setColumns(){
            // Open the CSV.
            ifstream currentFile;
            currentFile.open(getPath());
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
        vector<int> getColumn1(){
            return c1;
        }
        vector<int> getColumn2(){
            return c2;
        }
        vector<int> getColumn3(){
            return c3;
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
    // Check to see if file path and operator are valid.
    string path = argv[1];
    string operation = argv[2];
    if (!check_fp(path) || !check_op(operation)){
        cerr << "Please pass valid arguments" << endl;
        return 1;
    }

    csvItem obj1(path);
    vector<int> curr1 = obj1.getColumn1();
    vector<int> curr2 = obj1.getColumn2();
    vector<int> curr3 = obj1.getColumn3();
    for (int i = 0; i < curr1.size(); ++i) {
        cout << curr1[i] << curr2[i] << curr3[i]  << endl;
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

bool check_op(const string& op){
    // Check to see if operation is valid.
    if (op == "print" || op == "sum" || op == "mean" || op == "std"){
        return true;
    }
    return false;
}
