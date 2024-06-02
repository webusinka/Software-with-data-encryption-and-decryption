#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string ReadFromFile(const string& fname) {
    try {
        string text;
        ifstream file(fname);
        string line;
        while (getline(file, line)) {
            text += line + "\n";
        }
        file.close();
        cout << "The file has been read." << endl;
        return text;
    }
    catch (const exception& ex) {
        cout << ex.what() << endl;
    }
    return 0;
}
