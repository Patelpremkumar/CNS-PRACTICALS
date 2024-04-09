#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Function to encrypt the plaintext using the Columnar Transposition Cipher
string columnarEncrypt(const string& plaintext, const string& key) {
    string ciphertext;
    int cols = key.length();
    int rows = (plaintext.length() + cols - 1) / cols;
    vector<vector<char>> matrix(rows, vector<char>(cols, ' '));

    // Fill the matrix with the plaintext characters
    for (int i = 0; i < plaintext.length(); ++i) {
        matrix[i / cols][i % cols] = plaintext[i];
    }

    // Rearrange columns based on the key
    vector<pair<char, int>> sortedKey;
    for (int i = 0; i < cols; ++i) {
        sortedKey.push_back(make_pair(key[i], i));
    }
    sort(sortedKey.begin(), sortedKey.end());

    // Read the matrix column by column according to the sorted key
    for (int i = 0; i < cols; ++i) {
        int col = sortedKey[i].second;
        for (int j = 0; j < rows; ++j) {
            ciphertext += matrix[j][col];
        }
    }

    return ciphertext;
}

// Function to decrypt the ciphertext using the Columnar Transposition Cipher
string columnarDecrypt(const string& ciphertext, const string& key) {
    string plaintext;
    int cols = key.length();
    int rows = (ciphertext.length() + cols - 1) / cols;
    vector<vector<char>> matrix(rows, vector<char>(cols, ' '));

    // Fill the matrix with the ciphertext characters
    int index = 0;
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            if (index < ciphertext.length()) {
                matrix[j][i] = ciphertext[index++];
            }
        }
    }

    // Rearrange columns based on the key
    vector<pair<char, int>> sortedKey;
    for (int i = 0; i < cols; ++i) {
        sortedKey.push_back(make_pair(key[i], i));
    }
    sort(sortedKey.begin(), sortedKey.end());

    // Read the matrix column by column according to the sorted key
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int col = sortedKey[j].second;
            plaintext += matrix[i][col];
        }
    }

    return plaintext;
}

int main() {
    string plaintext, ciphertext, key;

    cout << "Enter plaintext: ";
    getline(cin, plaintext);

    cout << "Enter key: ";
    getline(cin, key);

    // Encrypt the plaintext using the Columnar Transposition Cipher
    ciphertext = columnarEncrypt(plaintext, key);
    cout << "Encrypted text: " << ciphertext << endl;

    // Decrypt the ciphertext using the Columnar Transposition Cipher
    string decryptedText = columnarDecrypt(ciphertext, key);
    cout << "Decrypted text: " << decryptedText << endl;

    return 0;
}
