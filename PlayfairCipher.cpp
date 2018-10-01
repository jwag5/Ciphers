/*
VigenereCipher.cpp
Jake Wagner
September 26, 2018
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string encipher(char c1, char c2, char aT[5][5]);

int main() {
	//Variables
	char alphaTable[5][5];
	int row = 0;
	int col = 0;
	bool alphaUsed[26] = { false };
	bool iUSedKey = false;
	bool jUsedKey = false;
	string key;
	string text;
	string cipher;
	int head;
	int tail;
	int m;
	const int asciiOffset = 97;


	//First get the key
	cout << "Please enter an alphabetic key:   ";
	cin >> key;
	

	//Next break the key down into tokens and add only
	//unique lowercase letters to the 5x5 alphaMatrix
	m = key.length();
	for (int i = 0; i < m; ++i) {
		//If alphabetic but upper case, tolower
		if (64 < key[i] && key[i] < 91) {
			key[i] = tolower(key[i]);
		}
		//if unique alphabetic, insert and mark off
		if ((96 < key[i]) && (key[i] < 123) && (alphaUsed[key[i] - asciiOffset] == false)) {
			//ensure either i or j only
			if (key[i] == 'i') {
				alphaUsed[9] = true;
				iUSedKey = true;
			}
			if (key[i] == 'j') {
				alphaUsed[8] = true;
				jUsedKey = true;
			}
			//insert it
			alphaTable[row][col] = key[i];
			alphaUsed[key[i] - asciiOffset] = true;
			++col;
			//if over, wrap to next row
			if (col > 4) {
				col = 0;
				++row;
			}
		}
	}//end forloop


	
	//if neither i nor j used in key, use i for insertion purposes
	if (!iUSedKey && !jUsedKey) {
		alphaUsed[9] = true;
	}
	//Now fill in the rest of the alphaTable in order
	row = m / 5;
	col = m % 5;
	for (int i = m; i < 26; ++i) {
		for (int j = 0; j < 26; ++j) {
			if (alphaUsed[j] == false) {
				alphaTable[row][col] = char(j + asciiOffset);
				alphaUsed[j] = true;
				++col;
				if (col > 4) {
					col = 0;
					++row;
				}
			}
		}
	}//end forloop


	//Now get the plaintext
	cout << "Please enter the plain text message:   ";
	cin.ignore();
	getline(cin, text);


	//Prepare it for Playfair input
	transform(text.begin(), text.end(), text.begin(), tolower);
	if (!iUSedKey && !jUsedKey) {
		replace(text.begin(), text.end(), 'j', 'i');
	}


	//Now take two characters at a time, encrypt them, and save
	cout << "\nEncrypting...\n";
	cipher = "";
	head = 1;
	tail = 0;
	while (tail < text.length()) {
		//If the tail is pointing to a valid character...
		if ((96 < text[tail]) && (text[tail] < 123)) {
			//Check if the head is also
			if (96 < text[head] && text[head] < 123) {
				//If both are valid, check if a filler is necessary
				if (text[tail] == text[head]) {
					//If a filler is necessary, check the characters are not both 'x' 
					if (text[tail] == 'x') {
						//if it is, use 'z' as head
						cipher += encipher(text[tail], 'z', alphaTable) + " ";
						//now tail is head and increment head
						tail = head;
						++head;
					}
					else {
						//otherwise, use 'x' as head
						cipher += encipher(text[tail], 'x', alphaTable) + " ";
						//now tail is head and increment head
						tail = head;
						++head;
					}
				}
				else {
					//If no filler necessary, encrypt and move to next pair
					cipher += encipher(text[tail], text[head], alphaTable) + " ";
					head += 2;
					tail += 2;
				}
			}
			else {
				//if the head is not at a valid character it could be out of the string
				if (head >= text.length()) {
					//if it is, its an odd length string so use a filler
					//if last character is an 'x', dont create a similar pair
					if (text[tail] == 'x') {
						//if it is, use 'z' as head
						cipher += encipher(text[tail], 'z', alphaTable) + " ";
					}
					else {
						//otherwise, use 'x' as head
						cipher += encipher(text[tail], 'x', alphaTable) + " ";
					}
					//now move tail to head and increment head
					tail = head;
					++head;
				}
				else {
					//if its not a valid character nor at the end of the string, try the next one
					++head;
				}
			}
		}
		else {
			//If the tail is not on a valid character, inc it and in the head
			//only if it was immediately in front of the tail
			++tail;
			if (tail == head)
				++head;
		}
	}//end while loop


	//Finally, display the cipher
	cout << "Ciphertext:   " << cipher << endl;


	system("PAUSE");
	return 0;
}


//	encipher
//	Take as input two characters and an associated alphaTable. It
//	then returns as a string the new pair of characters.
//	Note: assumed from main that C1 != C2
string encipher(char C1, char C2, char aT[5][5]) {
	int rowC1, rowC2, colC1, colC2;
	string newPair = "";

	//find the row and col of C1 and C2
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			//C1 match
			if (C1 == aT[i][j]) {
				rowC1 = i;
				colC1 = j;
			}
			//C2 match
			if (C2 == aT[i][j]) {
				rowC2 = i;
				colC2 = j;
			}
		}
	}

	//Now, check for anomolies...
	//if both characters are in the same column
	if (colC1 == colC2) {
		//do a vertical shift
		++rowC1;
		++rowC2;
		if (rowC2 > 4)
			rowC2 = 0;
	}
	//if both are in the same row
	if (rowC1 == rowC2) {
		//do a vertical shift
		++colC1;
		++colC2;
		if (colC2 > 4)
			colC2 = 0;
	}

	//now find the corresponding character for C1
	newPair += aT[rowC1][colC2];

	//now find corresponding character for C2
	newPair += aT[rowC2][colC1];

	return newPair;
}//end encipher
