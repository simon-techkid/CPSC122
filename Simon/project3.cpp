/*
 Name: Simon Field
 Class: CPSC 122, Section 02
 Date Submitted: October 3, 2025
 Assignment: Project 3
 Description: Program implements the Affine Cipher.
 Sources:
  CPPReference, 10/3/2025, https://cplusplus.com/reference/istream/istream/get/
*/

#include <iostream>
#include <fstream>
using namespace std;

#define RAND_MINIMUM 1
#define RAND_MAXIMUM 25
#define ALPHABET_COUNT 26

void keyGen(string keyFile);
char set_7th_bit(char);
bool get_7th_bit(char);
char get_all_but_7th_bit(char);
char encrypt(char ch, int alpha, int beta);
char decrypt(char ch, int alpha, int beta, int MI[]);
void control(int mode, string keyFile, string input, string output);

int main(int argc, char* argv[]) {
	int mode;
	string keyFile, input, output;

	if (argc != 3 && argc != 5) {
		cout << "Incorrect number of command line arguments" << endl;
		exit(1);
	}

	mode = atoi(argv[1]);
	keyFile = argv[2];

	if (argc == 3) {
		keyGen(keyFile);
		return 0; 
	}

	if (argc == 5) {
		input = argv[3];
		output = argv[4];
		control(mode, keyFile, input, output); 
	}

	return 0;
}

/*
Description: Generates and stores an integer key in the range [1..25]
Input: Name of output file
Output: none. Generated key is stored in the output file 
*/
void keyGen(string keyFile) {
	unsigned seed = time(NULL);
	srand(seed);

	int legalAlpha[12] = {1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25};

	// Randomly select an alpha from the list of coprimes
	int alpha = legalAlpha[rand() % 12];

	// Randomly generate beta in the range [0, 25]
	int beta = rand() % ALPHABET_COUNT;

	ofstream fout;
	fout.open(keyFile);

	fout << alpha << " " << beta;
	fout.close();
}

/*
Description; 
1 Opens keyfile and reads key 
2 Opens plaintext and ciphertext files 
3 Reads each character of the plaintext file 
4 If mode is 1 and the character is alphabetic, transforms it to upper case, encrypts it and writes it to the output file 
5 If mode is 2 and the character is alphabetic, decrypts it and writes it to output file
6 If the character is not alphabetic, writes it to the output file
7 Closes all three files
Input: Encrypt/decrypt mode, names of key file, input, and output files
Output: Writes encrypted/decrypted text to output file
*/
void control(int mode, string keyFile, string input, string output) {
	ifstream finKey;
	ifstream fin;
	ofstream fout;

	finKey.open(keyFile);
	if (!finKey.is_open()) {
		cout << "Error opening key file." << endl;
		exit(1);
	}
	int alpha, beta;
	finKey >> alpha >> beta;
	finKey.close();

	fin.open(input);
	fout.open(output);

	if (!fin.is_open() || !fout.is_open()) {
		cout << "Error opening input/output files." << endl;
		exit(1);
	}

	// Problem with K-CodeStarts MI.
	//int MI[26] = {0,1,0,9,0,21,0,15,0,0,0,19,0,0,0,7,0,23,0,11,0,5,0,17,0,25};
	  int MI[26] = {0,1,0,9,0,21,0,15,0,3,0,19,0,0,0,7,0,23,0,11,0,5,0,17,0,25};
	//                                  ^

	char ch;
	while (fin.get(ch)) {
		if (mode == 1 && isalpha(ch)) {
			bool originalUpper = isupper(ch);
			ch = toupper(ch);
			ch = encrypt(ch, alpha, beta);
			if (originalUpper) {
				ch = set_7th_bit(ch);
			}
		} else if (mode == 2) {
			bool originalUpper = get_7th_bit(ch);
			char originalChar = ch;
			ch = get_all_but_7th_bit(ch);
			if (!isalpha(ch)) {
				ch = originalChar;
			} else {
				ch = decrypt(ch, alpha, beta, MI);
				if (!originalUpper) {
					ch = tolower(ch);
				}
			}
		}
		fout.put(ch);
	}

	fin.close();
	fout.close();
}

// Set the 7th bit to 1
inline char set_7th_bit(char c) {
    return c | (1 << 7);
}

// Get the 7th bit as a boolean
inline bool get_7th_bit(char c) {
    return (c & (1 << 7)) != 0;
}

// Returns the input char with the 7th bit cleared
inline char get_all_but_7th_bit(char c) {
    return c & ~(1 << 7);
}

/*
Description: Encrypts a single character with key according to the rules for affine cipher encryption
Input: character to be encrypted with key
Output: returns encrypted character 
*/
char encrypt(char ch, int alpha, int beta) {
	int pos = ch - 'A';
	pos = (alpha * pos + beta) % ALPHABET_COUNT;
	ch = pos + 'A';
	return ch;
}

/*
Description: Decrypts a single character with key according to the rules for affine cipher decryption
Input: character to be decrypted with key
Output: returns decrypted character 
*/
char decrypt(char ch, int alpha, int beta, int MI[]) {
	int pos = ch - 'A';
	int alpha_inverse = MI[alpha];
	pos = (alpha_inverse * (pos - beta + ALPHABET_COUNT)) % ALPHABET_COUNT;
	ch = pos + 'A';
	return ch;
}
