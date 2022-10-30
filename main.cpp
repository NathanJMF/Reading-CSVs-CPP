//
// Created by Nathan Fenwick on 30/10/2022.
//
#include <iostream>
#include <fstream>

using namespace std;
bool check_fp(const string& fp);
bool check_op(const string& op);
/**
How to run:
g++ main.cpp -o main
./main file_path operation_name
**/
int main(int argc, char** argv) {
    // Check if valid number of arguments passed.
    if (argc > 3){
        cout << "Please pass a valid number of arguments" << endl;
        return 0;
    }

    // Check to see if arg1 and arg2 are valid.
    string path = argv[1];
    string operation = argv[2];
    if (!check_fp(path) || !check_op(operation)){
        cout << "Please pass valid arguments" << endl;
        return 0;
    }
    return 0;
}

bool check_fp(const string& fp){
    ifstream check(fp);
    if (!check){
        return false;
    }
    return true;
}

bool check_op(const string& op){
    if (op == "print" || op == "sum" || op == "mean" || op == "std"){
        return true;
    }
    return false;
}