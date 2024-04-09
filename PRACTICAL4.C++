#include <iostream>
#include <string>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

using namespace std;

// Function to generate a random key stream of the given length
string generateKeyStream(int length) {
    string keyStream = "";
    for (int i = 0; i < length; ++i) {
        // Generate a random uppercase letter (ASCII 65-90)
        char randomChar = rand() % 26 + 65;
        keyStream += randomChar;
    }
    return keyStream;
}

// Function to perform the Vernam encryption
string vernamEncrypt(const string& plaintext, const string& key) {
    string ciphertext = "";
    for (size_t i = 0; i < plaintext.length(); ++i) {
        // XOR each character of plaintext with the corresponding character of the key stream
        char encryptedChar = plaintext[i] ^ key[i];
        ciphertext += encryptedChar;
    }
    return ciphertext;
}

// Function to perform the Vernam decryption
string vernamDecrypt(const string& ciphertext, const string& key) {
    string decryptedText = "";
    for (size_t i = 0; i < ciphertext.length(); ++i) {
        // XOR each character of ciphertext with the corresponding character of the key stream
        char decryptedChar = ciphertext[i] ^ key[i];
        decryptedText += decryptedChar;
    }
    return decryptedText;
}

int main() {
    string plaintext, key, ciphertext;

    cout << "Enter plaintext: ";
    getline(cin, plaintext);

    // Generate a random key stream with the same length as the plaintext
    srand(time(0)); // Seed the random number generator with current time
    key = generateKeyStream(plaintext.length());

    // Encrypt the plaintext using the Vernam cipher
    ciphertext = vernamEncrypt(plaintext, key);
    cout << "Encrypted text: " << ciphertext << endl;

    // Decrypt the ciphertext using the same key
    string decryptedText = vernamDecrypt(ciphertext, key);
    cout << "Decrypted text: " << decryptedText << endl;

    return 0;
}
