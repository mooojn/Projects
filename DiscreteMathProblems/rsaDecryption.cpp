#include<iostream>
using namespace std;

int findPrivateKey(float, float);

int main()
{
    float p, q, e;
    // getting input from the user's
    cout << "Enter the value of 'p': ";
    cin >> p;
    cout << "Enter the value of 'q': ";
    cin >> q;
    cout << "Enter the public key 'e': ";
    cin >> e;
    float totient = (p - 1) * (q - 1);   // value of phi(n)
    int d_privateKey = findPrivateKey(totient, e);
    cout << "Your private key 'd': " << d_privateKey;
    return 0;
}
int findPrivateKey(float totient, float publicKey)
{
    int privateKey = 0, k = 0;      
    float tempKey;                  // to store d until it has integer
    bool privateKeyFound = false;
    while(!privateKeyFound)
    {
        tempKey = (1 + k * totient) / publicKey;;
        k++;
        if (tempKey == static_cast<int>(tempKey)) // value of d is int
        {                                        // then it is our private key
            privateKey = static_cast<int>(tempKey);
            privateKeyFound = true;            // key found so exiting the loop
        }
    }
    return privateKey;
}