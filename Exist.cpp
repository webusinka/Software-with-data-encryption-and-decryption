#include <iostream>
#include <fstream>
using namespace std;

bool exist(string& filename) {
	ifstream file(filename);
	if (file.is_open()) {
		return true;
    } else {
		return false;
    }
}
