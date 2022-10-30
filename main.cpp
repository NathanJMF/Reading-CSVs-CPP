//
// Created by Nathan Fenwick on 30/10/2022.
//
#include <iostream>

using namespace std;


int main(int argc, char** argv) {
    cout << "You have entered " << argc << " arguments:" << endl;
    for (int count = 0; count < argc; count++){
        cout << argv[count] << endl;
    }
    return 0;
}
