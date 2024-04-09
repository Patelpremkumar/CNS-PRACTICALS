#include <iostream>
#include <openssl/rsa.h>
#include <openssl/pem.h>

using namespace std;

// Function to generate RSA key pair
void generateRSAKeyPair(RSA*& publicKey, RSA*& privateKey) {
    RSA* rsa = RSA_generate_key(2048, RSA_F4, nullptr, nullptr);
    if (!rsa) {
        cerr << "Failed to generate RSA key pair." << endl;
        exit(1);
    }

    publicKey = RSAPublicKey_dup(rsa);
    privateKey = RSAPrivateKey_dup(rsa);
    RSA_free(rsa);
}

// Function to encrypt plaintext using RSA public key
string rsaEncrypt(const string& plaintext, RSA* publicKey) {
    int encryptedLength = RSA_size(publicKey);
    unsigned char* encryptedText = new unsigned char[encryptedLength];

    int result = RSA_public_encrypt(plaintext.size(), reinterpret_cast<const unsigned char*>(plaintext.c_str()),
                                    encryptedText, publicKey, RSA_PKCS1_OAEP_PADDING);

    if (result == -1) {
        cerr << "RSA encryption failed." << endl;
        exit(1);
    }

    string encryptedString(reinterpret_cast<char*>(encryptedText), result);
    delete[] encryptedText;
    return encryptedString;
}

// Function to decrypt ciphertext using RSA private key
string rsaDecrypt(const string& ciphertext, RSA* privateKey) {
    int decryptedLength = RSA_size(privateKey);
    unsigned char* decryptedText = new unsigned char[decryptedLength];

    int result = RSA_private_decrypt(ciphertext.size(), reinterpret_cast<const unsigned char*>(ciphertext.c_str()),
                                     decryptedText, privateKey, RSA_PKCS1_OAEP_PADDING);

    if (result == -1) {
        cerr << "RSA decryption failed." << endl;
        exit(1);
    }

    string decryptedString(reinterpret_cast<char*>(decryptedText), result);
    delete[] decryptedText;
    return decryptedString;
}

int main() {
    RSA* publicKey = nullptr;
    RSA* privateKey = nullptr;

    // Generate RSA key pair
    generateRSAKeyPair(publicKey, privateKey);

    string plaintext = "Hello, RSA!"; // Plain text to be encrypted

    // Encrypt the plaintext using RSA public key
    string ciphertext = rsaEncrypt(plaintext, publicKey);
    cout << "Encrypted text: " << ciphertext << endl;

    // Decrypt the ciphertext using RSA private key
    string decryptedText = rsaDecrypt(ciphertext, privateKey);
    cout << "Decrypted text: " << decryptedText << endl;

    // Clean up
    RSA_free(publicKey);
    RSA_free(privateKey);

    return 0;
}
