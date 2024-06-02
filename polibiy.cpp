#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include "mainHeader.h"

using namespace std;
extern const char* SYSTEM_CLEAR;

struct Matrix{
    map <char, pair<int,int>> matrix;
};

void Polybius_square(Matrix& Polybius){
    int ch = 33;
    int ch2 = -64;

    for (int i = 1; i <= 9; i++) { // Заполняем квадрат Полибия, с помощью которого будем шифровать
        for (int j = 1; j <= 17; j++) {
            if (j <= 10) {
                Polybius.matrix[char(ch)].first = i;
                Polybius.matrix[char(ch)].second = j;
                ch++;
            } else {
                Polybius.matrix[char(ch2)].first = i;
                Polybius.matrix[char(ch2)].second = j;
                ch2++;
            }
        }
    }

    ch = 33;
    ch2 = -64;
    for (const auto& element: Polybius.matrix){
            cout << " " << element.first << " "<< element.second.first << " " << element.second.second << endl;
        }
    cout << endl;
}

string Polybius_square_Code(string text) {
    Matrix Polybius;
    Polybius_square(Polybius);
    string ctf; //зашифрованное сообщение

    for (char element: text) {
        if (element == '\n'){
            break;
        }
        if ((element >= '!' && element <= 'z') || (element >= -64 && element <=-1)) {
            auto code = Polybius.matrix.find(element);
            if(code == Polybius.matrix.end()) {
                continue;
            }
                ctf += to_string(code->second.first) + to_string(code->second.second) + ' ';
            
            if (element == -1) ctf += to_string(918) + ' ';
        } else {
            if (element == 32) {
                ctf += ' ';
            }
            else throw element; 
        }
    }
    return ctf;
}

string Polybius_square_Decode (string text) { 
    char polybius[9][17];
    int ch = 33;
    int ch2 = -64;

    for (int i = 0; i < 9; i++) { // Заполняем квадрат Полибия, с помощью которого будем шифровать
        for (int j = 0; j < 17; j++) {
            if (j < 10) {
                polybius[i][j] = char(ch);
                ch++;
            } else {
                polybius[i][j] = char(ch2);
                ch2++;
            }
        }
    }

    for (int y = 0; y < 9; y++) { // Выводим матрицу
        for (int r = 0; r < 17; r++) {
            cout << polybius[y][r] << " ";
        }
        cout << endl;
    }

    text += " ";
    string decoded;

    for (long i = 0; i < text.length(); i += 3) { // Поиск символа в квадрате Полибия
        if (text[i] == ' ') {
            decoded += ' ';
            i -= 2;
            continue;
        }
        if ((text[i + 2]) != ' ') {
            if (((text[i] - '0') * 100 + (text[i + 1] - '0') * 10 + (text[i + 2] - '0')) == 918) {
                decoded += char(-1);
                i++;
                continue;
            }
            int row = text[i] - '0' - 1;
            int col = (text[i + 1] - '0') * 10 + (text[i + 2] - '0') - 1;
            decoded += polybius[row][col];
            i++;
        } else {
            int row = text[i] - '0' - 1;
            int col = text[i + 1] - '0' - 1;
            decoded += polybius[row][col];
        }
    }
    return decoded;
}

void polibiy(string& password1, string& password2){

	int pick, pickencode;
	string pass1, pass2, message, filename;

	while (true) {
		try {
			cout << "----Polybius square----" << endl
				<< "Select an action:" << endl
				<< "<1> Encrypt" << endl
				<< "<2> Decrypt" << endl
				<< "<3> Exit to the main menu" << endl;
			cin >> pick;
			while (cin.fail() || cin.peek()!='\n') {
				throw logic_error("Input error!");
				cin >> pick;
			}
			if (pick!= 1 && pick != 2 && pick != 3) {
				throw logic_error("You entered the wrong command!");
			}

			if (pick == 1) {
				cout << "Enter the encoding password: ";
				cin >> pass1;
				if (pass1 == password1) {
					cout << "Input action:" << endl
						<< "<1> Enter text from the console" << endl
						<< "<2> Read text from a file" << endl;
					cin >> pickencode;
					if (cin.fail() || cin.peek() != '\n') {
						throw logic_error("Input error!");
					}
					if (pickencode != 1 && pickencode != 2) {
						throw logic_error("You entered the wrong command!");
					}
					if (pickencode == 1) {
						cout << "Input text: ";
						cin.ignore();
						getline(cin, message);
                        
						WriteIntoFile("polibiy.txt", message);
						string encodedText2 = ReadFromFile("polibiy.txt");
						string encoded2 = Polybius_square_Code(encodedText2);
                        
						cout << "Encrypted text: " << encoded2 << endl;
						WriteIntoFile("decoded.txt", encoded2);
					}
					if (pickencode == 2) {
						cout << "Enter the name of the file with the extension: ";
						cin >> filename;

						if (exist(filename) == false)
							throw logic_error("There is no such file or it cannot be opened!");

						string encodedText1 = ReadFromFile(filename);
						string encoded1 = Polybius_square_Code(encodedText1);

						cout << "Encrypted text: " << encoded1 << endl;
						WriteIntoFile("decoded.txt", encoded1);
					}
				} else {
					throw logic_error("Invalid encoding password");
				}

			} else if (pick == 2) {
				cout << "Enter the decoding password: ";
				cin >> pass2;

				if (pass2 == password2) {
					string encodedText1 = ReadFromFile("decoded.txt");
					string decoded1 = Polybius_square_Decode(encodedText1);
					WriteIntoFile("decoded1.txt", decoded1);

					cout << "The decrypted text: " << decoded1 << endl;
				} else {
					throw logic_error("Invalid decoding password");
				}
				
			} else if (pick == 3) {
				system(SYSTEM_CLEAR);
				break;
			}
		}
		catch (const exception& e) {
			cerr << e.what() << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
	}
    return;
}