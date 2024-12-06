#include<iostream>
using namespace std;

int modularInverseFinder(int, int);
int extendedGCDForBezouts(int, int, int&, int&);

int main()
{
    int num, modulus;
    cout << "Enter the number: ";
    cin >> num;
    cout << "Enter the modulus: ";
    cin >> modulus;
    cout << "Modulo Inverse: " << modularInverseFinder(num, modulus);
    return 0;
}
int modularInverseFinder(int number, int mod) 
{
    int bezoutOne, bezoutTwo; // bezoit coeffiecients
    int gcd = extendedGCDForBezouts(number, mod, bezoutOne, bezoutTwo);
    if (gcd > 1)             // inverse not exists
    {
        cout << "The provided number is not invertible\n";              
        return -1;
    }
    return bezoutOne < 0 ? bezoutOne + mod : bezoutOne;   // ternary condition
}                                                        //  if negative then 
//...                                                   // add 'n' to make it '+ve'
// same function from previous code
int extendedGCDForBezouts(int a, int b, int &bezoutOne, int &bezoutTwo) 
{
    // basic case
    if (b == 0) 
    {
        bezoutOne = 1;
        bezoutTwo = 0;
        return a;
    }
    int gcdResult = extendedGCDForBezouts(b, a % b, bezoutOne, bezoutTwo);  // recursive call
    int temp = bezoutTwo;                            // temp value store so its not lost
    bezoutTwo = bezoutOne - (a / b) * bezoutTwo;    // formula for bezoit calculation
    bezoutOne = temp;                              // changing 'bezoutOne' to prev value of var 'bezoutTwo'
    return gcdResult;
}