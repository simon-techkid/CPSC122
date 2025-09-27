/*
 Name: Simon Field
 Class: CPSC 122, Section 02
 Date Submitted: September 19, 2025
 Assignment: Project 2
 Description: Program implements the Substitution Cipher.
 Sources:
  StackOverflow, 9/19/2025, https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c
  StackOverflow, 9/19/2025, https://stackoverflow.com/questions/41669119/getting-caesar-cipher-to-wrap-around
  StackOverflow, 9/19/2025, https://stackoverflow.com/questions/40275512/how-to-generate-random-numbers-between-2-values-inclusive
  GeeksForGeeks, 9/19/2025, https://www.geeksforgeeks.org/cpp/how-to-generate-random-number-in-range-in-cpp/
  CPPReference, 9/19/2025, https://en.cppreference.com/w/cpp/numeric/random/rand.html
*/

#include <iostream>
#include <cstdlib>
#include <random>
#include <fstream>

#define LOWER_BEGIN 'a'
#define UPPER_BEGIN 'A'
#define NUM_KEYS 26
#define RAND_MINIMUM 1
#define RAND_MAXIMUM 25
#define USAGE_STRING "Usage: ./a.out <0 (gen)/1 (enc)/2 (dec)> <key_file> <pt_file> <ct_file>"

using namespace std;

enum MODE : char {
    GENERATE = 0,
    ENCRYPT = 1,
    DECRYPT = 2,
    INVALID = 3
};


/**
 * @brief Handles the error case scenario.
 *
 * This function is called when an error condition is encountered.
 * The specific error handling logic should be implemented within this function.
 */
void errorCase();

/**
 * @brief Retrieves the key from the specified key file.
 *
 * This function opens the given key file, reads the key value, and stores it in the provided pointer.
 *
 * @param keyFile Path to the file containing the key.
 * @param key Pointer to an integer where the key will be stored.
 * @return int Returns 0 on success, or -1 if the file could not be opened.
 */
int keyGet(string keyFile, int* key);

/*
Description: Generates and stores a randomly generated integer key in the range [1..25]
Input: Name of output file
Output: none. Generated key is stored in the output file 
*/
int keyGen(string keyFile);

/*
Description; 
1 Opens keyfile and reads key 
2 Opens plaintext and ciphertext files 
3 If mode is 1: reads each character of the PTfile
  --if alpha transforms to upper case, invokes Encrypt
  --writes both non-alpha and upper case encrypted alpha to CTfile 
4 If mode is 2: reads each character of the CTfile
  --if alpha invokes Decrypt
  --writes both non-alpha and the decrypted alpha chars to PTfile
5 Closes all three files
Input: Encrypt/decrypt mode, names of key file, PTfile, CTfile 
Output: Writes encrypted/decrypted text to either CTfile or CTfile depending on mode 
*/
int control(MODE mode, string keyFile, string PTfile, string CTFile);

/*
Description: Encrypts a single character using  key according to the rules for 
substitution cipher encryption
Input: character to be encrypted with key
Output: returns encrypted character 
*/
char encrypt(char ch, int key);

/*
Description: Decrypts a single character using key according to the rules for 
substitution cipher encrption
Input: character to be decrypted with key
Output: returns decrypted character 
*/
char decrypt(char ch, int key);

/**
 * @brief Determines the mode of operation based on the input character.
 *
 * This function converts the input character to the corresponding MODE enum value.
 *
 * @param c The character representing the mode.
 * @return MODE The mode of operation (GENERATE, ENCRYPT, DECRYPT, or INVALID).
 */
MODE getMode(char c);

/**
 * @brief Encrypts plaintext using a key and writes the ciphertext to a file.
 *
 * This function reads a key from the specified key file, encrypts the plaintext from the given plaintext file,
 * and writes the resulting ciphertext to the specified ciphertext file.
 *
 * @param keyFile Path to the file containing the encryption key.
 * @param ptFile Path to the file containing the plaintext to be encrypted.
 * @param ctFile Path to the file where the encrypted ciphertext will be written.
 * @return int Returns 0 on success, or a non-zero error code on failure.
 */
int modeEncrypt(
    string& keyFile,
    string& ptFile,
    string& ctFile
);

/**
 * @brief Decrypts ciphertext using a specified key file and writes the plaintext to a file.
 *
 * This function reads a key from the provided key file, decrypts the ciphertext from the specified ciphertext file,
 * and writes the resulting plaintext to the plaintext file.
 *
 * @param keyFile Path to the file containing the decryption key.
 * @param ptFile Path to the file where the decrypted plaintext will be written.
 * @param ctFile Path to the file containing the ciphertext to be decrypted.
 * @return int Returns 0 on success, or a non-zero error code on failure.
 */
int modeDecrypt(
    string& keyFile,
    string& ptFile,
    string& ctFile
);

/*
Generate the key: ./a.out 0 keyFile.txt
keyFile.txt is the name of the file storing the key 

Encrypt plaintext: ./a.out 1 keyFile.txt  PTfile.txt  CTfile.txt
PTfile.txt is the plain text file
CTfile.txt is the ciphertxt file

Decrypt ciphertext: ./a.out 2 keyFile.txt  PTfile.txt  CTfile.txt
PTfile.txt is the plain text file
CTfile.txt is the ciphertxt file
*/
int main(int argc, char* argv[]) {
    if (argc < 3) {
        errorCase();
        return 1;
    }

    vector<string> args;
    for (int i = 1; i < argc; ++i) {
        args.emplace_back(string(argv[i]));
    }

    MODE mode = getMode(args[0][0]);

    if (mode == MODE::INVALID || argc < 3) {
        errorCase();
        return 1;
    }

    string keyFile = args[1];

    if (mode == MODE::GENERATE) {
        return keyGen(keyFile);
    } else if (argc != 5) {
        errorCase();
        return -1;
    }

    string ptFile = args[2];
    string ctFile = args[3];

    return control(mode, keyFile, ptFile, ctFile);    
}

int control(MODE mode, string keyFile, string PTfile, string CTFile) {
    if (mode == MODE::DECRYPT) {
        return modeDecrypt(keyFile, PTfile, CTFile);
    } else if (mode == MODE::ENCRYPT) {
        return modeEncrypt(keyFile, PTfile, CTFile);
    } else return -1;
}

int modeEncrypt(
    string& keyFile,
    string& ptFile,
    string& ctFile
) {
    int key;
    if (keyGet(keyFile, &key) != 0) {
        cout << "Key could not be retrieved";
        return -1;
    }

    ifstream ptIn(ptFile);
    ofstream ctOut(ctFile, ios::out | ios::trunc);
    if (!ptIn.is_open()) {
        cout << "Could not open " << ptFile;
        return -1;
    }
    if (!ctOut.is_open()) {
        cout << "Could not open " << ctFile;
        return -1;
    }

    string line;
    while (getline(ptIn, line)) {
        for (char c : line) {
            if (isalpha(c)) {
                ctOut << encrypt(c, key);
            } else {
                ctOut << c;
            }
        }
        ctOut << endl;
    }

    ptIn.close();
    ctOut.close();
    return 0;
}

int modeDecrypt(
    string& keyFile,
    string& ptFile,
    string& ctFile
) {
    int key;
    if (keyGet(keyFile, &key) != 0) return -1;

    ifstream ctIn(ctFile);
    ofstream ptOut(ptFile);
    if (!ctIn.is_open() || !ptOut.is_open()) return -1;

    string line;
    while (getline(ctIn, line)) {
        for (char c : line) {
            if (isalpha(c)) {
                ptOut << decrypt(c, key);
            } else {
                ptOut << c;
            }
        }
        ptOut << endl;
    }

    ctIn.close();
    ptOut.close();
    return 0;
}

void errorCase() {
    cout << USAGE_STRING << endl;
}

MODE getMode(char c) {
    if (c >= '0' && c <= '2') {
        return static_cast<MODE>(c - '0');
    }
    return MODE::INVALID;
}

int keyGet(string keyFile, int* key) {
    ifstream inFile(keyFile);
    if (inFile.is_open()) {
        inFile >> *key;
        inFile.close();
    } else {
        return -1;
    }
    return 0;
}

int keyGen(string keyFile) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(RAND_MINIMUM, RAND_MAXIMUM);
    int randomValue = distrib(gen);
    string randomString = to_string(randomValue);

    ofstream outFile(keyFile);
    if (outFile.is_open()) {
        outFile << randomString;
        outFile.close();
    } else {
        return -1;
    }

    return 0;
}

inline char encrypt(char ch, int key) {
    if (islower(ch)) {
        int newChar = (ch - LOWER_BEGIN) + key;
        int adjustedKey = newChar % NUM_KEYS;
        return (char)(adjustedKey + LOWER_BEGIN);
    } else if (isupper(ch)) {
        int newChar = (ch - UPPER_BEGIN) + key;
        int adjustedKey = newChar % NUM_KEYS;
        return (char)(adjustedKey + UPPER_BEGIN);
    } else {
        return ch;
    }
}

inline char decrypt(char ch, int key) {
    if (islower(ch)) {
        int newChar = ((ch - LOWER_BEGIN) - key + NUM_KEYS);
        int adjustedKey = newChar % NUM_KEYS;
        return (char)(adjustedKey + LOWER_BEGIN);
    } else if (isupper(ch)) {
        int newChar = ((ch - UPPER_BEGIN) - key + NUM_KEYS);
        int adjustedKey = newChar % NUM_KEYS;
        return (char)(adjustedKey + UPPER_BEGIN);
    } else {
        return ch;
    }
}
