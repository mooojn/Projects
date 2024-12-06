#include <iostream>
#include <string>
#include <cmath>
#include <map>
using namespace std;

int modularExponentiation(int base, int exponent, int modulus);
int encryptUsingRSA(int msg, int n, int e);

int main() 
{
    int n = 2537, e = 13;     // public key random prime's
    string message;
    cout << "Enter your message: ";
    cin >> message;
    cout << "Encrypted data = ";
    map<char, int> blocksOfCharacters;
    for (int i = 0; i < 26; i++)
        blocksOfCharacters['A' + i] = i; // mapping each capital alphabet
    for (int i = 0; i < message.length(); i += 2) 
    {
        int block = blocksOfCharacters[message[i]] * 100 + blocksOfCharacters[message[i + 1]];  // text in block of 2 pairs
        cout << encryptUsingRSA(block, n, e) << " ";     // result
    }
    return 0;
}
int encryptUsingRSA(int msg, int n, int e) 
{
    int result = 1;
    msg = msg % n;         // reducing the msg 
    while (e > 0) 
    {
        if (e & 1)        // e is odd
            result = (result * msg) % n;
        e = e >> 1;               // bitwise shift to right by '1'
        msg = (msg * msg) % n;   // squaring the msg
    }
    return result;
}