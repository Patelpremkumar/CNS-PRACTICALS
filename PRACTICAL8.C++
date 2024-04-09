#include <iostream>
#include <cmath>

using namespace std;

// Function to calculate the modular exponentiation (a^b mod m)
int modExp(int a, int b, int m) {
    if (b == 0)
        return 1;
    long long res = 1;
    long long base = a % m;
    while (b > 0) {
        if (b & 1)
            res = (res * base) % m;
        base = (base * base) % m;
        b >>= 1;
    }
    return res;
}

// Function to perform the Diffie-Hellman key exchange
void diffieHellman(int p, int g, int a, int b) {
    // Calculate A = g^a mod p
    int A = modExp(g, a, p);

    // Calculate B = g^b mod p
    int B = modExp(g, b, p);

    // Calculate shared secret key using A^b mod p (same as B^a mod p)
    int sharedKeyA = modExp(B, a, p);
    int sharedKeyB = modExp(A, b, p);

    // Both parties should have the same shared key
    if (sharedKeyA == sharedKeyB) {
        cout << "Shared secret key: " << sharedKeyA << endl;
    } else {
        cout << "Error: Shared secret keys do not match." << endl;
    }
}

int main() {
    int p, g, a, b;

    cout << "Enter prime modulus (p): ";
    cin >> p;

    cout << "Enter base (g): ";
    cin >> g;

    cout << "Enter private key of user A (a): ";
    cin >> a;

    cout << "Enter private key of user B (b): ";
    cin >> b;

    // Perform Diffie-Hellman key exchange
    diffieHellman(p, g, a, b);

    return 0;
}
