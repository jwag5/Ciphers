/*
CeaserCipher.cpp
Jake Wagner
September 26, 2018
*/

#include <iostream>
#include <string>

using namespace std;

int main() {
	//Variables
	int key;
	string text;

	//First get the key
	cout << "Please enter a numeric key:   ";
	cin >> key;

	key = (key % 94); //make no larger than the alphabet

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
			//Apply Ceaser Cipher with key
			text[i] = ((text[i] + key) % 94);
			//reshift to ascii range
			text[i] += 32;
		}
	}

	//display cipher
	cout << "Ciphertext:  " << text;

	//unencrypt
	cout << "\nDecrypting...\n";
	for (int i = 0; i < text.length(); i++) {
		//for Ascii text characters 32 to 126
		if (31 < text[i] && text[i] < 127) {
			//shift start of alphabet to 0
			text[i] -= 32;
			//Apply Ceaser Decipher with key
			text[i] = ((text[i] - key + 94) % 94);
			//reshift to ascii range
			text[i] += 32;
		}
	}

	//redisplay plaintext
	cout << "Plaintext:  " << text << endl;

	system("PAUSE");
	return 0;
}//end main
