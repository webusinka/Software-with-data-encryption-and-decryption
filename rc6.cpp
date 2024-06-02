#include <iostream>
#include <cstdint>
#include <cmath>
#include <iomanip>
#include <random>
#include "mainHeader.h"

using namespace std;
extern const char* SYSTEM_CLEAR;

// Константы
const uint32_t P = 0xb7e15163; //odd((e - 2)*2^w) - округление до большего, e - экспонента, f - золотое сечение 
const uint32_t Q = 0x9e3779b9; //odd((f - 1)*2^w) для w = 32
/*
//генерация рандомного ключа размером 128 бит
void generate_master_key(vector<unsigned char>& KEY, mt19937_64& mt) {
    uniform_int_distribution<int> letters('a', 'z');
    uniform_int_distribution<int> numbers(0, 9);
    for (int i = 1; i <= 8; i++) {
        KEY.push_back(letters(mt));
        KEY.push_back('0' + numbers(mt));
    }
}

//перевод числа из 2сс в 16сс
string to_hex(unsigned int value) {
    stringstream ss;
    ss << hex << uppercase << setw(2) << setfill('0') << value;
    return ss.str();
}

//преобразуем исходный текст string в vector 16cc
vector<string> textToHex(const string& text) {
    vector<string> result;
    
    // Преобразование текста в двоичное представление
    for (char c : text) {
        unsigned int byte = static_cast<unsigned int>(c);
        result.push_back(to_hex(byte));
    }
    
    // Дополнение вектора нулевыми значениями (padding)
    while (result.size() % 4 != 0) {
        result.push_back(to_hex(0));
    }
    
    return result;
}

// Функция для шифрования
string rc6_encrypt(string text) {
	//переводим текст в 16 сс.
	vector<string> vectorText = textToHex(text);

    string result;
    uint32_t plaintext;
    uint32_t key;
    uint32_t ciphertext;

    // Разделяем 128-битный блок открытого текста на 4 32-битных слова
    uint32_t A = plaintext[0];
    uint32_t B = plaintext[1];
    uint32_t C = plaintext[2];
    uint32_t D = plaintext[3];

    // Расширяем ключ до 44 32-битных подключей
    uint32_t S[44];
    uint32_t keylen = sizeof(key) / sizeof(uint32_t);
    S[0] = P;
    for (int i = 1; i < 44; i++) {
        S[i] = (S[i-1] + Q) & 0xFFFFFFFF;
    }

    // Выполняем 20 раундов преобразования
    for (int i = 0; i < 20; i++) {
        uint32_t t = (B * (2*B + 1)) << 5;
        t = t & 0xFFFFFFFF;
        uint32_t u = (D * (2*D + 1)) << 5;
        u = u & 0xFFFFFFFF;
        A = (A ^ t) << u | (A >> (32 - u));
        C = (C ^ u) << t | (C >> (32 - t));
        swap(A, B);
        swap(B, C);
        swap(C, D);
        A = (A + S[2*i]) & 0xFFFFFFFF;
        C = (C + S[2*i+1]) & 0xFFFFFFFF;
    }

    // Записываем результат в выходной массив
    ciphertext[0] = A;
    ciphertext[1] = B;
    ciphertext[2] = C;
    ciphertext[3] = D;

    return result;
}

string rc6_decrypt(string ciphertext){
	
}
*/
void rc6(string& password1, string& password2){
    /*
	int pick, pickencode;
	string pass1, pass2, message, filename;

	while (true) {
		try {
			cout << "------RC6------" << endl
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
				cout << "Enter the encoding password: " << endl;
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
                        
						WriteIntoFile("rc6.txt", message);
						string encodedText2 = ReadFromFile("rc6.txt");
						string encoded2 = rc6_encrypt(encodedText2);
                        
						cout << "Encrypted text: " << encoded2 << endl;
						WriteIntoFile("decoded.txt", encoded2);
					}
					if (pickencode == 2) {
						cout << "Enter the name of the file with the extension: ";
						cin >> filename;

						if (exist(filename) == false)
							throw logic_error("There is no such file or it cannot be opened!");

						string encodedText1 = ReadFromFile(filename);
						string encoded1 = rc6_encrypt(encodedText1);

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
					string decoded1 = rc6_decrypt(encodedText1);
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
	}*/
    return;
}