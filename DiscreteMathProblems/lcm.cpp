#include<iostream>
using namespace std;

int findGCD(int, int);
int findLCM(int, int);

int main()
{
    int num1, num2;
    cout << "Enter first number: ";
    cin >> num1;
    cout << "Enter second number: ";
    cin >> num2;
    cout << "LCM: " << findLCM(num1, num2);
    return 0;
}
//  formula for finding LCM is divide the product of two numbers
//       that you need to find the LCM of by thier GCD
int findLCM(int n1, int n2)
{
    return n1 * n2 / findGCD(n1, n2);
}
// function from previous code
int findGCD(int num1, int num2)
{
    if (num1 == 0)                          // base case
        return num2;
    else
        return findGCD(num2 % num1, num1); // recursive call for euclidean algo
}