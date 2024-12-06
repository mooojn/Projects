#include<iostream>
using namespace std;

string findPrimeFactorization(int);     // main function that returns the answer
bool isPrime(int);                     // function to check if a number is prime
int nextPrime(int);                   // function for finding the next prime number

int main()
{
    int number;
    cout << "Enter the number you want to find prime factorization of: ";
    cin >> number;
    cout << "Result: " << findPrimeFactorization(number);
    return 0;
}
string findPrimeFactorization(int number)
{
    string answer = "";    // answer will be stored here
    int primeNumber = 2;  // first prime number
    int num = number;    // using diff variable
    while (num != 1)  
    {
        if (num % primeNumber == 0)
        {
            num = num / primeNumber;
            answer += to_string(primeNumber) + " x ";
        }
        else
            primeNumber = nextPrime(primeNumber);  // assigning new prime number
    }
    return answer.substr(0, answer.length() - 3); // removing the last 3 element of string
}                                                //      which are extra ' x '
int nextPrime(int currentPrime)
{
    int nextPrimeNumber = currentPrime + 1;// next prime maybe next to current
    while (!isPrime(nextPrimeNumber))    // iterating until next prime number is found
    {
        nextPrimeNumber++;
    }
    return nextPrimeNumber;
}
bool isPrime(int numberToCheck)
{
    if (numberToCheck <= 1)
        return false;
    for (int i = 2; i < numberToCheck; i++) // starting with '2' upto 'num - 1'
    {
        if (numberToCheck % i == 0)
            return false;               // not prime
    }
    return true;
}