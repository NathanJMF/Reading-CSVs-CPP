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

class printCsvItem : public csvItem{
    public:
        explicit printCsvItem(string aPath) : csvItem(std::move(aPath)) {
        }
        void objectOperation(){
            vector<int> column1 = getColumn1();
            vector<int> column2 = getColumn2();
            vector<int> column3 = getColumn3();
            cout << "Col1 " << "Col2 " << "Col3" << endl;
            for (int i = 0; i < column1.size(); ++i) {
                cout << column1[i]<< "    " << column2[i] << "    " << column3[i] << endl;
            }
        }
};

class sumCsvItem : public csvItem{
    public:
        explicit sumCsvItem(string aPath) : csvItem(std::move(aPath)) {
        }
        void objectOperation(){
            vector<int> column1 = getColumn1();
            vector<int> column2 = getColumn2();
            vector<int> column3 = getColumn3();
            int count1 = 0, count2 = 0, count3 = 0;
            for (int i = 0; i < column1.size(); ++i) {
                count1 += column1[i];
                count2 += column2[i];
                count3 += column3[i];
            }
            cout << "col1 " << "col2 " << "col3" << endl;
            cout << count1 << "  " << count2 << "  " << count3 << endl;
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
    if (!check_fp(path) || !check_op(operation)){
        cerr << "Please pass valid arguments" << endl;
        return 1;
    }
    printCsvItem obj1(path);
    obj1.objectOperation();

    sumCsvItem obj2(path);
    obj2.objectOperation();


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
