/*
VigenereCipher.cpp
CS4600.01 Inclass Assignment #01
Jake Wagner
September 26, 2018
*/

#include <iostream>
#include <string>

using namespace std;

int main() {
	//Variables
	string keyWord;
	int key;
	int m;
	string text;
	int* k;

	//First get the key
	cout << "Please enter a numeric key: ";
	cin >> keyWord;
	key = stoi(keyWord);
	m = keyWord.length();

	//Break the key into its K_j elements
	k = new int[keyWord.length() - 1];
	for (int i = m - 1; key != 0; i--) {
		k[i] = key % 10;
		key /= 10;
	}

	//Next get the plain text from the user.
	cout << "Please enter the plain text message:   ";
	cin.ignore();
	getline(cin, text);

	//Now encrypt the message...
	cout << "\nEncrypting...\n";
	for (int i = 0; i < text.length(); i++) {
		//for Ascii text characters 32 to 126
		if (31 < text[i] && text[i] < 127) {
			//shift start of alphabet to 0
			text[i] -= 32;
			//Apply Vigenere Cipher with key
			text[i] = (text[i] + k[i % m]) % 94;
			//reshift to ascii range
			text[i] += 32;
		}
	}

	//display cipher
	cout << "Ciphertext:   " << text;

	//unencrypt
	cout << "\nDecrypting...\n";
	for (int i = 0; i < text.length(); i++) {
		//for Ascii text characters 32 to 126
		if (31 < text[i] && text[i] < 127) {
			//shift start of alphabet to 0
			text[i] -= 32;
			//Apply Vigenere Cipher with key
			text[i] = (text[i] - k[i % m]) % 94;
			//reshift to ascii range
			text[i] += 32;
		}
	}

	//redisplay plaintext
	cout << "Plaintext:  " << text << endl;

	system("PAUSE");
	return 0;
}//end main
