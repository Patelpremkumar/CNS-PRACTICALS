#include <iostream>
#include <string>

using namespace std;

// Function to encrypt the plaintext using Caesar Cipher
string encrypt(string plaintext, int shift) {
    string ciphertext = "";
    for (char& c : plaintext) {
        // Encrypt uppercase letters
        if (isupper(c))
            ciphertext += char(int(c + shift - 65) % 26 + 65);
        // Encrypt lowercase letters
        else if (islower(c))
            ciphertext += char(int(c + shift - 97) % 26 + 97);
        // Non-alphabetic characters remain unchanged
        else
            ciphertext += c;
    }
    return ciphertext;
}

// Function to decrypt the ciphertext using Caesar Cipher
string decrypt(string ciphertext, int shift) {
    // Decrypting is essentially same as encrypting, just with a negative shift
    return encrypt(ciphertext, -shift);
}

int main() {
    string plaintext, ciphertext;
    int shift;

    cout << "Enter plaintext: ";
    getline(cin, plaintext);

    cout << "Enter shift value: ";
    cin >> shift;

    // Encrypt the plaintext
    ciphertext = encrypt(plaintext, shift);
    cout << "Encrypted text: " << ciphertext << endl;

    // Decrypt the ciphertext
    cout << "Decrypted text: " << decrypt(ciphertext, shift) << endl;

    return 0;
}
