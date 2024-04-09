#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Function to encrypt the plaintext using the Rail Fence Cipher
string railFenceEncrypt(const string& plaintext, int rails) {
    vector<string> fence(rails, ""); // Create a vector of strings to represent the fence
    int rail = 0; // Current rail index
    bool down = false; // Flag to indicate whether to move down or up the rails

    // Fill the fence with the plaintext characters
    for (char c : plaintext) {
        fence[rail] += c;
        if (rail == 0 || rail == rails - 1) {
            // Change direction when reaching the top or bottom rail
            down = !down;
        }
        // Move to the next rail based on the direction
        rail += down ? 1 : -1;
    }

    // Concatenate all rails to get the ciphertext
    string ciphertext;
    for (const string& railStr : fence) {
        ciphertext += railStr;
    }

    return ciphertext;
}

// Function to decrypt the ciphertext using the Rail Fence Cipher
string railFenceDecrypt(const string& ciphertext, int rails) {
    vector<string> fence(rails, ""); // Create a vector of strings to represent the fence
    int rail = 0; // Current rail index
    bool down = false; // Flag to indicate whether to move down or up the rails
    int index = 0;

    // Fill the fence with the ciphertext characters (similar to encryption process)
    for (char c : ciphertext) {
        fence[rail] += '*'; // Placeholder to mark the positions of the ciphertext characters
        if (rail == 0 || rail == rails - 1) {
            // Change direction when reaching the top or bottom rail
            down = !down;
        }
        // Move to the next rail based on the direction
        rail += down ? 1 : -1;
    }

    // Replace placeholders with the actual ciphertext characters
    for (int i = 0; i < rails; ++i) {
        for (int j = 0; j < fence[i].length(); ++j) {
            if (fence[i][j] == '*' && index < ciphertext.length()) {
                fence[i][j] = ciphertext[index++];
            }
        }
    }

    // Read the plaintext from the filled fence
    string plaintext;
    rail = 0;
    down = false;
    for (int i = 0; i < ciphertext.length(); ++i) {
        plaintext += fence[rail][i];
        if (rail == 0 || rail == rails - 1) {
            // Change direction when reaching the top or bottom rail
            down = !down;
        }
        // Move to the next rail based on the direction
        rail += down ? 1 : -1;
    }

    return plaintext;
}

int main() {
    string plaintext, ciphertext;
    int rails;

    cout << "Enter plaintext: ";
    getline(cin, plaintext);

    cout << "Enter number of rails: ";
    cin >> rails;

    // Encrypt the plaintext using the Rail Fence Cipher
    ciphertext = railFenceEncrypt(plaintext, rails);
    cout << "Encrypted text: " << ciphertext << endl;

    // Decrypt the ciphertext using the Rail Fence Cipher
    string decryptedText = railFenceDecrypt(ciphertext, rails);
    cout << "Decrypted text: " << decryptedText << endl;

    return 0;
}
