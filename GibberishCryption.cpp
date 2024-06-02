#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "mainHeader.h"

using namespace std;
extern const char* SYSTEM_CLEAR;

string cryption(string str) {
   // русские и английские согласные буквы
	vector<char> engVowels = {'B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Z'};
	vector<char> ruVowels = {
		'\xC1', '\xC2', '\xC3', '\xC4', '\xC6', '\xC7', '\xCA', '\xCB', '\xCC', '\xCD', '\xD9', '\xD8', '\xD7', '\xD6', '\xD5', '\xD4', '\xD2', '\xD1', '\xD0', '\xCF'
	};

	for (auto& letter : str) {
		bool lowercase;

		if ((letter >= '\xE0' && letter <= '\xFF') || (letter >= 'a' && letter <= 'z')) lowercase = true;
		else lowercase = false;

		if (letter > 0) {
			auto it = find_if(engVowels.begin(), engVowels.end(), [letter](char a) {
			return a == letter || a + 32 == letter;
			});
			if (it != engVowels.end()) {
				if (*it >= 'N') {
					if (lowercase) letter = *(it - engVowels.size() / 2) + 32;
					else letter = *(it - engVowels.size() / 2);
				}
				else{
					if (lowercase) letter = *(it + engVowels.size() / 2) + 32;
					else letter = *(it + engVowels.size() / 2);
				}
			}
		} else if (letter == '\xD9'){
			letter = '\xC1';
		} else {
			auto it = find_if(ruVowels.begin(), ruVowels.end(), [letter](char a) {
			return a == letter || a + 32 == letter;
			});
			if (it != ruVowels.end()) {
				if (distance(ruVowels.begin(),it) > ruVowels.size() / 2) {
					if (lowercase) letter = *(it - ruVowels.size() / 2) + 32;
					else letter = *(it - ruVowels.size() / 2);
				} else {
					if (lowercase) letter = *(it + ruVowels.size() / 2) + 32;
					else letter = *(it + ruVowels.size() / 2);
				}
			}
		}
	}
	return str;
}

void GibberishCryption(string& password1, string& password2) {
	int pick, pickencode;
	string pass1, pass2, message, filename;

	while (true) {
		try {
			cout << "----Gibberish Cryption----" << endl
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

						WriteIntoFile("gibberish.txt", message);
						string encodedText2 = ReadFromFile("gibberish.txt");
						string encoded2 = cryption(encodedText2);

						cout << "Encrypted text: " << encoded2 << endl;
						WriteIntoFile("decoded.txt", encoded2);
					}
					if (pickencode == 2) {
						cout << "Enter the name of the file with the extension: ";
						cin >> filename;

						if (exist(filename) == false)
							throw logic_error("There is no such file or it cannot be opened!");

						string encodedText1 = ReadFromFile(filename);
						string encoded1 = cryption(encodedText1);
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
					string decoded1 = cryption(encodedText1);
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
}