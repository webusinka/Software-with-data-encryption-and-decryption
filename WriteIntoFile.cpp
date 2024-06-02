#include <iostream>
#include <string>
#include <fstream>
using namespace std;

bool WriteIntoFile(const string& fname, const string& text) {
    try {
        ofstream file(fname);
        if (file.is_open())
            file << text;
        file.close();
        cout << "The file is recorded." << endl;
        return true;
    }
    catch (const exception& ex) {
        cout << ex.what() << endl;
    }
    return 0;
}
