#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include"mainHeader.h"

using namespace std;
const char* SYSTEM_CLEAR = "cls";

int main() {
    SetConsoleCP(1251);        //для корректного ввода и вывода русских символов в консоли
    SetConsoleOutputCP(1251);
    
    char pick;
    bool exit = true;
    string passenter = "323565", pass1 = "113480", pass2 = "191649", passcheck;

    cout << "Good morning!" << endl;
    cout << "Input password authorization: ";
    cin >> passcheck;
    while (passenter != passcheck){
        cout << "Wrong password authorization" << endl;
        cout << "Input password authorization:";
        cin >> passcheck;
    }

    while (exit) {
        try {
            cout << "Choosing a cipher, input the number:" << endl
                << "<1> Gibberish Cryption" << endl
                << "<2> Polybius square" << endl
                << "<3> Cipher RC6" << endl
                << "<4> Exit" << endl;
            cin >> pick;
            if (cin.peek() != '\n') {
                throw runtime_error("You have entered a string!");
            }
            if (pick != '1' && pick != '2' && pick != '3' && pick != '4') {
                throw runtime_error("You entered the wrong command!");
            }
            switch (pick) {
                case '1': {
                    system(SYSTEM_CLEAR);
                    GibberishCryption(pass1, pass2); //тарабарщина
                    break;
                } case '2': {
                    system(SYSTEM_CLEAR);
                    polibiy(pass1, pass2); //полибий
                    break;
                } case '3': {
                    system(SYSTEM_CLEAR);
                    rc6(pass1, pass2); //rc6
                    break;
                } case '4': {
                    cout << "Goodbye!!";
                    exit = false;
                }
            }
        }
        catch (const runtime_error& ex) {
            cerr << ex.what() << " Enter only one digit (1, 2 or 3)" << endl;
            cin.clear();
            cin.ignore(256, '\n');
        }
    }
}