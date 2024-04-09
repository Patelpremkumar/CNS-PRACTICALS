#include <iostream>
#include <string>

using namespace std;

// Function to decrypt the ciphertext using a brute-force attack
void bruteForceDecrypt(string ciphertext) {
    for (int shift = 0; shift < 26; ++shift) {
        string decryptedText = "";
        for (char& c : ciphertext) {
            // Decrypt uppercase letters
            if (isupper(c))
                decryptedText += char(int(c - shift - 65 + 26) % 26 + 65);
            // Decrypt lowercase letters
            else if (islower(c))
                decryptedText += char(int(c - shift - 97 + 26) % 26 + 97);
            // Non-alphabetic characters remain unchanged
            else
                decryptedText += c;
        }
        cout << "Shift " << shift << ": " << decryptedText << endl;
    }
}

int main() {
    string ciphertext;

    cout << "Enter ciphertext: ";
    getline(cin, ciphertext);

    cout << "Brute-force decryption results:" << endl;
    bruteForceDecrypt(ciphertext);

    return 0;
}
