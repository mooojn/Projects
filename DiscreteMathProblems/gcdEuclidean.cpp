#include<iostream>
using namespace std;

int findGCD(int, int);

int main()
{
    int num1, num2;
    cout << "Enter first number: ";
    cin >> num1;
    cout << "Enter second number: ";
    cin >> num2;
    cout << "GCD: " << findGCD(num1, num2); // function call 
    return 0;
}
int findGCD(int num1, int num2)
{
    if (num1 == 0)                          // base case
        return num2;
    else
        return findGCD(num2 % num1, num1); // recursive call 
}                                         // for euclidean algo