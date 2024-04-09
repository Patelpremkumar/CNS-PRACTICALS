#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

// Function to convert a character to its corresponding numeric value
int charToInt(char c) {
    return toupper(c) - 'A';
}

// Function to convert a numeric value to its corresponding character
char intToChar(int n) {
    return 'A' + n;
}

// Function to calculate the modular inverse of a number
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

// Function to encrypt the plaintext using the Hill Cipher
string encrypt(string plaintext, vector<vector<int>> key) {
    string ciphertext = "";
    int n = key.size();
    int blockSize = n;

    // Pad the plaintext with 'X' if necessary to make the length a multiple of the block size
    while (plaintext.length() % blockSize != 0)
        plaintext += 'X';

    // Encrypt each block of the plaintext
    for (int i = 0; i < plaintext.length(); i += blockSize) {
        vector<int> block(blockSize, 0);
        for (int j = 0; j < blockSize; j++) {
            block[j] = charToInt(plaintext[i + j]);
        }

        // Multiply the key matrix with the plaintext block
        for (int j = 0; j < blockSize; j++) {
            int sum = 0;
            for (int k = 0; k < blockSize; k++) {
                sum += key[j][k] * block[k];
            }
            ciphertext += intToChar(sum % 26);
        }
    }

    return ciphertext;
}

// Function to decrypt the ciphertext using the Hill Cipher
string decrypt(string ciphertext, vector<vector<int>> key) {
    string plaintext = "";
    int n = key.size();
    int blockSize = n;

    // Calculate the determinant of the key matrix
    int det = key[0][0] * key[1][1] - key[0][1] * key[1][0];
    det = (det % 26 + 26) % 26;

    // Find the modular inverse of the determinant
    int detInverse = modInverse(det, 26);
    if (detInverse == -1) {
        cout << "Inverse does not exist, cannot decrypt." << endl;
        return plaintext;
    }

    // Calculate the adjugate matrix of the key matrix
    int temp = key[0][0];
    key[0][0] = key[1][1];
    key[1][1] = temp;
    key[0][1] = -key[0][1];
    key[1][0] = -key[1][0];

    // Apply modular arithmetic to the elements of the adjugate matrix
    for (int i = 0; i < blockSize; i++) {
        for (int j = 0; j < blockSize; j++) {
            key[i][j] = (key[i][j] * detInverse) % 26;
            if (key[i][j] < 0)
                key[i][j] += 26;
        }
    }

    // Decrypt each block of the ciphertext
    for (int i = 0; i < ciphertext.length(); i += blockSize) {
        vector<int> block(blockSize, 0);
        for (int j = 0; j < blockSize; j++) {
            block[j] = charToInt(ciphertext[i + j]);
        }

        // Multiply the adjugate matrix with the ciphertext block
        for (int j = 0; j < blockSize; j++) {
            int sum = 0;
            for (int k = 0; k < blockSize; k++) {
                sum += key[j][k] * block[k];
            }
            plaintext += intToChar(sum % 26);
        }
    }

    return plaintext;
}

int main() {
    string plaintext, ciphertext;
    vector<vector<int>> key = {{6, 24}, {1, 17}}; // Example key matrix

    cout << "Enter plaintext: ";
    getline(cin, plaintext);

    // Encrypt the plaintext
    ciphertext = encrypt(plaintext, key);
    cout << "Encrypted text: " << ciphertext << endl;

    // Decrypt the ciphertext
    cout << "Decrypted text: " << decrypt(ciphertext, key) << endl;

    return 0;
}
