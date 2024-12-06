////////////////////////////////////////////////////////////////////////////////////////// Start of Program ////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>                  // for input and output
#include <typeinfo>                // for checking the type of variable
#include <string>                // for string functions
#include <windows.h>           // for color
#include <conio.h>         // for getch()
#include <fstream>       // for file handling
#include <iomanip>     // for setw
using namespace std;
// headers
void header();
void adminLoginHeader();
void signUpHeader();
void signInHeader();
void managerHeader();
void userHeader();
void greetUser(string);   
/// manager
bool adminLoginCheck(string, string &);         
/// manager functions
void viewRecords(string [], string [], float [] ,int  ,int);
void viewAssets(string [], string [], int);
string resetAdminPassword(string, string);
int addAsset(string [], string [],int, string, string);
int liquidity(float [], int );
int setNewGoldRate();
float giveLoan(float [],int );
bool addNewUser(string [], string [], string [], int &, string, string);
bool modifyInfoAdmin(string [], int , int &);
bool deleteUser(string [], string [], float [], int , int &);
//////////////////////// user
/// user functions
void viewTransactions(string [], float [], int );
void checkPortfolio(float [], float [], int , float );
bool blockOrUnblockTransactions(bool);
bool modifyInformation(string [], string [], int , int , int &, string);
bool deleteAccount(string [], string [],int , int &, float [], float [], string []);
bool changePassword(string [], int , string);
bool depositMoney(float [], int , float );
bool withdrawMoney(float [], int , float );
bool transferMoney(string [], float [], int , int &, int , float , string );
bool investGold(string [],float [], float [], int , int , float , float );
/// menus
string mainMenu();
string managerMenu();
string userMenu();
/// sign up
bool createUser(string [], string [], string [], int &, string , string );
/// data Verification
bool uniqueUser(string[], int &, string);   /// sign up
bool userExist(string[], string, int, int &);     /// sign in
bool checkUserValidity(string [], string [], int , int &, string, string);  /// pass checker
// user data
void storeDataLocally(string [], string [], string [], float [], float [], string [], float [], int );
void loadUserDATA(string [], string [], string [], float [], float [], int &);
// admin data
void loadAdminDATA(string [], string [], int &, string &, float &);
void storeAdminDATA(string [], string [], int &, string &, float &);
// function to get field data from csv file
string getFieldData(string , int );
///////////////////////////////////////////////////////////////////////////////
/// colors
string setcolor(unsigned short );
int blue = 1, green = 2, cyan = 3, red = 4, brown = 6, lightwhite = 7, lightblue = 9, lightgreen = 10, lightcyan = 11, lightred = 12, yellow = 14, white = 15;
/////////////////  Extra   /////////////////////////// 
string maskedPassword();
string againExecuteThisFunction();
string getAdminPass();
string getUserEnteredName();
string getNAME();
string validatePassword(string);
string assetWorthHaveCash(string);
int validateIntInput(string, int);
float validateFloatInput(string);
void accountNotExists();
void passNotCorrect();
void showBalance(float [], int );
void transactionError();
void goldHeader(float);
void viewRecordHeader();
void viewTransactionsHeader();
void adminPressAnyKey();
void userPressAnyKey();
void mainPressAnyKey();
void simulateProcessing();
void simulateWithoutTelling();
void storeTransactionHistory(string [], float [], int &, float, string);
void invest(float [], float [], int , float , float );
void transferNow(string [], float [], int , int , float );
void loader();
bool nameCheck(string);
void simulateWithoutTellingLONG();
void invalidNameError();
void accessDeniedError();
void userAlreadyExists();
void terminateProgram();
void invalidChoiceError();
void invalidInputError();
void areYouMadError();
void invalidSrNoError();
void modificationSuccess();
void modificationError();
void transactionsBlockedError();   
void transactionsUnblocked();
void assetAddedSuccessfully();
void goldRateChanged();
void invalidPassError();
void passwordLenghtError();
void passwordCommaError();
//////////////////////////////////////////////////////////////////////////////////////   main function start    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    // arrays for user data
    int index = 0;                                                   /// counter for the storing values
    string userNames[100];
    string userPasswords[100];
    string userIDs[100];
    float userBalances[100] = {0};
    float userInvestments[100] = {0};
    float transactions[100] = {0};           
    string transactionsTypes[100];
    // loading users data
    loadUserDATA(userNames, userPasswords, userIDs, userBalances, userInvestments, index);   /// loading data from file
    ///////////////////////////////////////////////////////////////////
    // users extra vars
    int currentIndex = 0;
    int transferIndex = 0;                           /// for transfer of cash b/w users
    int transactionsIndex = 0;                          /// displaying transactions
    bool blockTransactions = false;                        /// for blocking transactions
    // admin vars
    string bankAssets[100];
    string bankAssetsWorth[100];
    int assetIndex = 0;
    string adminPassword = "";
    float goldRate;
    // loading admin data
    loadAdminDATA(bankAssets, bankAssetsWorth, assetIndex, adminPassword, goldRate);
    // gold rate or admin password not found in file then default values
    if (goldRate == 0)
        goldRate = 69.7;             // default gold rate
    if (adminPassword == "")
        adminPassword = "admin";   // default password for admin
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
    int del = 0;                  // for deletion of records
    string choice = "0";
    string LogInTo = "none"; 
mainPage:       // for logging out of user's
    while(choice != "4")
    {
        choice = mainMenu();         // menu bar option select
        if (choice == "1")          // admin login
        { 
            adminLoginHeader();
            string userEnterAdminPass = getAdminPass();
            bool login =  adminLoginCheck(userEnterAdminPass, adminPassword);
            simulateProcessing();
            if (login)
            {
                LogInTo = "admin";
                break;
            }
            accessDeniedError();
            mainPressAnyKey();
        }
        else if (choice == "2")      // sign in user
        {
            string userEnteredPassword, userEnteredName = getUserEnteredName();
            setcolor(lightcyan);
            cout << "\t\t\t\t\t\t\t\t\t\t\tEnter your Password: ";
            userEnteredPassword = maskedPassword();
            simulateProcessing();
            if (userExist(userNames, userEnteredName, index, transferIndex))
            {
                if (checkUserValidity(userNames, userPasswords, index, currentIndex, userEnteredName, userEnteredPassword))     /// password and name checking
                {
                    LogInTo = "user";       // login successful
                    break;
                }
                passNotCorrect();  // no need to place in else   :)
            }
            else
                accountNotExists();
            setcolor(white);
        }
        else if (choice == "3")   // sign up user
        {
            string name = getNAME();
            string pass;
            pass = validatePassword("\n\t\t\t\t\t\t\t\t\t\t\tSet Password:");
            setcolor(lightblue);
            if (uniqueUser(userNames, index ,name))         /// User created
                createUser(userNames, userPasswords, userIDs, index, name, pass);
            else
                userAlreadyExists();
            setcolor(white);
            mainPressAnyKey();
        }
        else if (choice == "4")
        {
            terminateProgram();
            storeDataLocally(userNames, userPasswords, userIDs, userBalances, userInvestments, transactionsTypes, transactions, index);
            storeAdminDATA(bankAssets, bankAssetsWorth, assetIndex, adminPassword, goldRate);
            return 0;                         /// end program
        }
        else             /// for error cases
            invalidChoiceError();
    }
    if (LogInTo == "admin")
    {
        string adminSelectedOption = "0";
        while(adminSelectedOption != "11")
        { 
            adminSelectedOption = managerMenu();
            if (adminSelectedOption == "1")
            {
                bool addUserAgain = true;
                while (addUserAgain)        // loop is for the admin if he want to add more then "1" user
                {
retakeNameInputAdminSignUp:   // if invalid name then again
                    managerHeader();
                    string newUserName, newUserPass;
                    setcolor(cyan);
                    cout << "\t\t\t\t\t\t\t\t\t\t\tEnter the Name: ";
                    cin >> newUserName;
                    bool nameValidation = nameCheck(newUserName);
                    if (!nameValidation)
                    {
                        invalidNameError();
                        goto retakeNameInputAdminSignUp;
                    }
                    setcolor(white);
                    newUserPass =  validatePassword("\n\t\t\t\t\t\t\t\t\t\t\tSet Password: ");
                    addUserAgain = addNewUser(userNames, userPasswords, userIDs, index, newUserName, newUserPass);
                }
            }
            else if (adminSelectedOption == "2")
            {
                viewRecordHeader();
                viewRecords(userNames, userIDs, userBalances ,index , del);      
            }
            else if (adminSelectedOption == "3")
            {   
                managerHeader();
                string assetName;
                setcolor(cyan);
                cout << "\t\t\t\t\t\t\t\t\t\t\tEnter the assest's name you want to add: ";
                cin >> assetName;
                bool assetNameValidation = nameCheck(assetName);
                if (!assetNameValidation)
                {
                    invalidNameError();
                    continue;
                }
                string assetWorth;
                assetWorth = assetWorthHaveCash("\t\t\t\t\t\t\t\t\t\t\tEnter the assest's worth you have added: ");
                assetWorth = assetWorth + "k";
                setcolor(white);
                assetAddedSuccessfully();
                assetIndex = addAsset(bankAssets, bankAssetsWorth, assetIndex, assetName, assetWorth);  // increasing the asset index by value return
            }
            else if (adminSelectedOption == "4")
            {   
                managerHeader();
                int cashHoldings = liquidity(userBalances, index);
                setcolor(brown);
                cout << "\t\t\t\t\t\t\t\t\t\t\tTotal Cash available in Liquid: " << cashHoldings << endl;
                setcolor(white);
                adminPressAnyKey();
            }
            else if (adminSelectedOption == "5")
            {   
                managerHeader();
                goldHeader(goldRate);
                float newRate = setNewGoldRate();       
                if (newRate <= 0)
                {
                    invalidInputError();
                    continue;            // wrong input 
                }
                goldRate = newRate;
                goldRateChanged();
                adminPressAnyKey();
            }
            else if (adminSelectedOption == "6")
            {   
                managerHeader();
                viewAssets(bankAssets, bankAssetsWorth, assetIndex);
                adminPressAnyKey();
            }
            else if (adminSelectedOption == "7")
            {   
                del = 1;
                viewRecordHeader();
                viewRecords(userNames, userIDs, userBalances , index, del);
                int loanIndex;
                loanIndex = validateIntInput("\n\t\t\t\t\t\t\t\t\t\t\tEnter the Sr.No you want to give loan to: ",index);
                userBalances[loanIndex] = giveLoan(userBalances, loanIndex);
                del = 0;
                viewRecordHeader();
                viewRecords(userNames, userIDs, userBalances , index, del);
            }
            else if (adminSelectedOption == "8")
            {   
                del = 1;
                viewRecordHeader();
                viewRecords(userNames, userIDs, userBalances , index, del);
                bool modification = modifyInfoAdmin(userNames, index, transferIndex);
                if (modification == true)
                    modificationSuccess();
                else    
                    modificationError();
                del = 0;
                viewRecordHeader();
                viewRecords(userNames, userIDs, userBalances , index, del);
            }
            else if (adminSelectedOption == "9")
            {   
                managerHeader();
                string userEnteredAdminpass;
                setcolor(yellow);
                cout << "\t\t\t\t\t\t\t\t\t\t\tEnter your current Password: ";
                userEnteredAdminpass = maskedPassword();
                setcolor(white);
                adminPassword = resetAdminPassword(adminPassword, userEnteredAdminpass);
            }
            else if (adminSelectedOption == "10")
            {   
                del = 1;
                viewRecordHeader();
                viewRecords(userNames, userIDs, userBalances , index, del);
                int deletionIndex;
                deletionIndex = validateIntInput("\n\t\t\t\t\t\t\t\t\t\t\tEnter the Sr.No you want to remove: ",index);
                bool deletion = deleteUser(userNames, userPasswords, userBalances, deletionIndex, index);
                del = 0;
                viewRecordHeader();
                viewRecords(userNames, userIDs, userBalances , index, del);
            }
            else if (adminSelectedOption == "11")
                goto mainPage;     /// logging out
            else
                invalidChoiceError();
        }
    }
    else if (LogInTo == "user")
    {
        string userSelectedOption = "0";
        while(userSelectedOption != "11")
        {
            userHeader();
            greetUser(userNames[currentIndex]);
            cout << endl;
            userSelectedOption = userMenu();
            if (userSelectedOption == "1")
            {
                userHeader();
                checkPortfolio(userInvestments, userBalances, currentIndex, goldRate);
                userPressAnyKey();
            }
            else if(userSelectedOption == "2")
            {
                userHeader();
                float deposit;
                if (!blockTransactions)
                {
                    deposit = validateFloatInput("\n\t\t\t\t\t\t\t\t\t\t\tEnter the amount that you want to Deposit: $");
                    bool depositStatus = depositMoney(userBalances, currentIndex, deposit);
                    if (depositStatus == true)   // transaction successful then storeDataLocally the history
                        storeTransactionHistory(transactionsTypes, transactions, transactionsIndex, deposit, "Deposit");
                    else
                        transactionError();
                }
                else
                    transactionsBlockedError();   
                userPressAnyKey();
            }
            else if (userSelectedOption == "3")
            {
                userHeader();
                float withdraw;
                if (!blockTransactions)
                {
                    withdraw = validateFloatInput("\n\t\t\t\t\t\t\t\t\t\t\tEnter the amount that you want to Withdraw: $");
                    bool withdrawStatus = withdrawMoney(userBalances, currentIndex, withdraw);
                    if (withdrawStatus)
                        storeTransactionHistory(transactionsTypes, transactions, transactionsIndex, withdraw, "Withdraw");
                }
                else
                    transactionsBlockedError();
                userPressAnyKey();
            }
            else if (userSelectedOption == "4")
            {
                userHeader();
                float transfer;
                if (!blockTransactions)
                {
                    transfer = validateFloatInput("\n\t\t\t\t\t\t\t\t\t\t\tEnter the amount that you want to Transfer: $");
                    if (transfer > 0)
                    {
                        setcolor(yellow);
                        string receiverName;
                        cout << "\t\t\t\t\t\t\t\t\t\t\tEnter name of the reciever: ";
                        cin >> receiverName;
                        bool transferStatus = transferMoney(userNames, userBalances, currentIndex, transferIndex, index, transfer, receiverName);            
                        if (transferStatus)
                            storeTransactionHistory(transactionsTypes, transactions, transactionsIndex,transfer, "Transfer");
                    }
                    else
                        transactionError();
                }
                else
                    transactionsBlockedError();
                userPressAnyKey();
            }
            else if (userSelectedOption == "5")
            {
                userHeader();
                float investment;
                if (!blockTransactions)
                {
                    userHeader();
                    showBalance(userBalances, currentIndex);
                    goldHeader(goldRate);
                    investment = validateFloatInput("\n\t\t\t\t\t\t\t\t\t\t\tEnter the amount that you want to Invest: $");
                    if (investment > 0)
                    {
                        bool investmentStatus = investGold(userNames, userInvestments, userBalances, currentIndex, index, goldRate, investment);             
                        if (investmentStatus)
                            storeTransactionHistory(transactionsTypes, transactions, transactionsIndex, investment, "Investment");
                    }
                    else
                        transactionError();
                }   
                else
                    transactionsBlockedError();
                userPressAnyKey();
            }
            else if (userSelectedOption == "6")
            {
                userHeader();
                setcolor(red);
                if (transactions[0] != 0)
                {
                    viewTransactionsHeader();
                    viewTransactions(transactionsTypes, transactions, transactionsIndex);
                }
                else
                    cout << "\n\t\t\t\t\t\t\t\t\t\t\tNo Transactions for Now..";
                setcolor(white);
                userPressAnyKey();
            }
            else if (userSelectedOption == "7")
            {
                userHeader();
                blockTransactions = blockOrUnblockTransactions(blockTransactions);
                if(blockTransactions == true)
                    transactionsBlockedError();
                else
                    transactionsUnblocked();
                userPressAnyKey();
            }
            else if (userSelectedOption == "8")
            {
                userHeader();   
                string userCurrentPassword;
                setcolor(yellow);
                cout << "\t\t\t\t\t\t\t\t\t\t\tEnter your Password: ";
                userCurrentPassword =  maskedPassword();
                bool modified = modifyInformation(userNames, userPasswords, currentIndex, index, transferIndex, userCurrentPassword);
                if (modified)
                    modificationSuccess();
                else
                    modificationError();
                userPressAnyKey();
            }
            else if (userSelectedOption == "9")
            {
                userHeader();
                string userEnteredPassword;
                setcolor(yellow);
                cout << "\t\t\t\t\t\t\t\t\t\t\tEnter Current Password: ";
                userEnteredPassword = maskedPassword();
                bool modificationOfPassword = changePassword(userPasswords, currentIndex, userEnteredPassword);
                if (modificationOfPassword)
                    modificationSuccess();
                else
                    modificationError();
                userPressAnyKey();
            }
            else if (userSelectedOption == "10")
            {
                bool confirmDelete = deleteAccount(userNames, userPasswords, currentIndex, index, userBalances, userInvestments, userIDs);
                if (confirmDelete)
                    goto mainPage;
            }
            else if (userSelectedOption == "11")
            {
                blockTransactions = false;                         // reseting the 
                for (int i = 0; i < transactionsIndex; i++)         //
                {                                                    //
                    transactionsTypes[i] = "";                        //
                    transactions[i] = 0;                               //
                }                                                        // values  ;}
                transactionsIndex = 0;                                
                goto mainPage;         // logging out
            }
            else 
                invalidChoiceError();
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////   main function end    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// main menu
string assetWorthHaveCash(string command)
{
    string assetWorth;
    setcolor(yellow);
    cout << endl << command;
    cin >> assetWorth;
    setcolor(white);
    try{
        int temp = stoi(assetWorth);
    }
    catch(invalid_argument){
        invalidInputError();
        assetWorthHaveCash(command);    // recursive call if invalid input
    }
    catch(out_of_range){
        areYouMadError();
        assetWorthHaveCash(command);
    }
    return assetWorth;
}
void goldRateChanged()
{
    simulateProcessing();
    setcolor(green);
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tGold Rate has been changed successfully...";
    setcolor(white);
}
void assetAddedSuccessfully()
{
    setcolor(lightgreen);
    cout << "\t\t\t\t\t\t\t\t\t\t\tAsset have been added successfully..." << endl;
    setcolor(white);
}
void transactionsUnblocked()
{
    setcolor(lightgreen);
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tYour Transactions have been unlocked..." << endl;
    setcolor(white);
}
void transactionsBlockedError()
{
    setcolor(lightred);
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tYour Transactions are Blocked..." << endl;
    setcolor(white);
}
void modificationSuccess()
{
    setcolor(lightgreen);
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tModification was successful";
    setcolor(white);
}
void modificationError()
{
    setcolor(lightred);
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tModification was not successful";
    setcolor(white);
}
int validateIntInput(string statement, int userCount)
{
retakeInput:
    int temp = 0;
    string srNumber = "";
    setcolor(yellow);
    cout << statement;
    cin >> srNumber;
    setcolor(white);
    try
    {
        temp = stoi(srNumber);
    }
    catch(invalid_argument)
    {
        invalidInputError();
        goto retakeInput;
    }
    catch(out_of_range)
    {
        areYouMadError();
        goto retakeInput;
    }
    if (temp >= userCount || temp < 0)
    {
        invalidSrNoError();
        goto retakeInput;
    }
    return temp;
}
void invalidSrNoError()
{
    setcolor(lightred);
    cout << "\t\t\t\t\t\t\t\t\t\t\tSr.NO out of range";
    simulateWithoutTellingLONG();
    setcolor(white);
}
string mainMenu()         
{
    header();
    string option;
    setcolor(cyan);
    cout << "\t\t\t\t\t\t\t\t\t\t\t1. Login as Manager" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t2. Login as User" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t3. Sign up as User" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t4. End" << endl;
    cout << endl;
    setcolor(yellow);
    cout << "\t\t\t\t\t\t\t\t\t\t\tPlease Select an Option...";
    cin >> option;
    setcolor(white);
    return option;
}
void mainPressAnyKey()
{
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tPress any key to continue..";
    getch();
}  
////////////////////////////////////////////////////////////////////////////////////// admin functions start ////////////////////////////////////////////////////////////////////////////////////////////////////////////
string managerMenu()
{
    managerHeader();
    string adminSelectedOption;
    setcolor(cyan);
    cout << "\t\t\t\t\t\t\t\t\t\t\t1. Add a New User" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t2. View All Records" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t3. Add an Asset" << endl; 
    cout << "\t\t\t\t\t\t\t\t\t\t\t4. View Bank's Liquidity" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t5. Set Gold Rate" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t6. View Asset's" << endl;   
    cout << "\t\t\t\t\t\t\t\t\t\t\t7. Give Loan" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t8. Update Information" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t9. Reset Password" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t10. Delete a User" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t11. Log Out" << endl;
    cout << endl;
    setcolor(yellow);
    cout << "\t\t\t\t\t\t\t\t\t\t\tPlease Select an Option...";
    cin >> adminSelectedOption;
    setcolor(white);
    return adminSelectedOption;
}
string resetAdminPassword(string adminPassword, string pass)
{
    string newPass = adminPassword;
    simulateProcessing();
    if (adminPassword == pass)
    { 
        newPass = validatePassword("\n\t\t\t\t\t\t\t\t\t\t\tSet new Password: ");
        setcolor(green);
        cout << "\n\t\t\t\t\t\t\t\t\t\t\tPassword Successfully changed\n";
        setcolor(white);
    }
    else
        invalidPassError();
    adminPressAnyKey();
    return newPass;
}
string validatePassword(string command)
{
retakePass:
    setcolor(lightgreen);
    cout << command;
    setcolor(white);
    string pass;
    pass = maskedPassword();
    // length check
    if (pass.length() < 4)
    {
        passwordLenghtError();
        goto retakePass;
    }
    // comma not in string
    for (int i = 0; i < pass.length(); i++)
    {
        if (pass[i] == ',')
        {
            passwordCommaError();
            goto retakePass;
        }
    }
    return pass;
}
void passwordLenghtError()
{
    setcolor(lightred);
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tPassword length must be greater then four characters...";
    simulateWithoutTellingLONG();
    setcolor(white);
}
void invalidPassError()
{
    setcolor(lightred);
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tInvalid Password...";
    setcolor(white);
}
void passwordCommaError()
{
    setcolor(lightred);
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tPassword can't have comma(,)...";
    simulateWithoutTellingLONG();
    setcolor(white);
}
void viewAssets(string bankAssets[], string bankAssetsWorth[], int assetIndex)
{
    setcolor(blue);
    cout << "\t\t\t\t\t\t\t\t\t\t\tAsset's Name\t\t\tAsset's Worth($)\n";
    setcolor(lightcyan);
    for (int i = 0; i < assetIndex; i++)
        cout << "\t\t\t\t\t\t\t\t\t\t\t" << setw(8) << bankAssets[i] << "\t\t\t     " << bankAssetsWorth[i] << endl;
    setcolor(white);
}
int addAsset(string bankAssets[], string bankAssetsWorth[], int assetIndex, string newAsset, string assetWorth)
{
    bankAssets[assetIndex] = newAsset;
    bankAssetsWorth[assetIndex] = assetWorth;
    assetIndex++;
    adminPressAnyKey();
    return assetIndex;
}
void adminPressAnyKey()
{
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    getch();
}
int liquidity(float userBalances[], int index)
{
    float cashHoldings;
    for (int i = 0; i < index; i++)
        cashHoldings += userBalances[i];
    return cashHoldings;
}
float giveLoan(float userBalances[], int choice)
{
    float loan;
    loan = validateFloatInput("\n\t\t\t\t\t\t\t\t\t\t\tEnter the amount of Loan you want to give: ");
    simulateProcessing();
    if (loan <= 0){
        cout << endl;
        invalidInputError();
        return 0;
    }
    float newAmount = userBalances[choice] + loan;  // previous and new balance added
    return newAmount;
}
bool modifyInfoAdmin(string userNames[], int index, int &transferIndex)
{
    bool modification = false;
    int choice;
    choice = validateIntInput("\n\t\t\t\t\t\t\t\t\t\t\tEnter the Sr.No you want to change the info of: ",index);
    string newName;
    setcolor(blue);
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tEnter new Name: ";
    cin >> newName;
    setcolor(white);
    bool nameValidation = nameCheck(newName);
    if (!nameValidation)
    {
        invalidNameError();
        return modification;
    }
    simulateProcessing();
    if(!userExist(userNames, newName, index, transferIndex))
    {
        userNames[choice] = newName;
        modification = true;
    }
    return modification;
}
void viewRecords(string userNames[], string userIDs[], float userBalances[] ,int index ,int del)
{
    setcolor(lightgreen);
    for (int i = 0; i < index; i++)
        cout << "\t\t\t\t\t\t\t\t\t\t\t  " << i << "      " << setw(8) << userNames[i] << "\t      " << userIDs[i] << "\t   " << userBalances[i] << endl;
    setcolor(white);
    if (del==0)
        adminPressAnyKey();
}
void viewRecordHeader()
{
    managerHeader();
    setcolor(lightcyan);
    cout << "\t\t\t\t\t\t\t\t\t\t\t#################################################" << endl;
    setcolor(cyan);
    cout << "\t\t\t\t\t\t\t\t\t\t\t Sr No       Name \t    ID - No. \t Balance($)" << endl;
    setcolor(lightcyan);
    cout << "\t\t\t\t\t\t\t\t\t\t\t#################################################" << endl;
    setcolor(white);
    cout << endl;
}
bool addNewUser(string userNames[], string userPasswords[], string userIDs[], int &index, string name, string pass)
{
    bool again = false;
    if (uniqueUser(userNames, index, name))
        createUser(userNames, userPasswords, userIDs, index, name, pass);
    else
        userAlreadyExists();
choiceAgain:  // if invalid choice then again
    string choice = againExecuteThisFunction();  /// if want to execute again
    if (choice == "1" || choice == "yes" || choice == "Yes" || choice == "y" || choice == "Y")
        again = true;
    else if (choice == "2" || choice == "no" || choice == "No" || choice == "n" || choice == "N")
        again = false;
    else
    {
        invalidChoiceError();
        goto choiceAgain;   // choice not correct so again
    }
    return again;
}
int setNewGoldRate()
{
    float newGoldRate;
    setcolor(yellow);
    newGoldRate = validateFloatInput("\n\n\t\t\t\t\t\t\t\t\t\t\tNew Gold Rate: ");
    setcolor(white);
    return newGoldRate;
}
bool deleteUser(string userNames[], string userPasswords[], float userBalances[], int choice, int &userCount)
{
    simulateProcessing();
    for (int i = choice; i < userCount; i++)
    {
        userNames[i] = userNames[i+1];
        userPasswords[i] = userPasswords[i+1];
        userBalances[i] = userBalances[i+1];
    }
    userCount--;
    return true;
}
string againExecuteThisFunction()
{
    string choice;
    setcolor(yellow);
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tDo you want to add another one press 1/yes/y or 2/no/n: ";
    setcolor(white);
    cin >> choice;
    return choice;
}
////////////////////////////////////////////////////////////////////////////////////// admin functions end ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////// user functions Start ///////////////////////////////////////////////////////////////////////////////////////////////////////////
string userMenu()
{    
    string userOption;
    setcolor(lightcyan);
    cout << "\t\t\t\t\t\t\t\t\t\t\t1. Check Portfolio" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t2. Deposit Money" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t3. With-Draw Money" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t4. Transfer Money To Another Account" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t5. Invest in Gold" << endl;
    // cout << "\t\t\t\t\t\t\t\t\t\t\t5. Verify Account" << endl;      //// future features "maybe" :}
    // cout << "\t\t\t\t\t\t\t\t\t\t\t5. Convert Gold" << endl;        //// future features "maybe" :}
    cout << "\t\t\t\t\t\t\t\t\t\t\t6. View Transaction's" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t7. Block/Unblock Transaction's" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t8. Change Name" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t9. Change Password" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t10. Delete Account" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t11. Log Out" << endl;
    cout << endl;
    setcolor(yellow);
    cout << "\t\t\t\t\t\t\t\t\t\t\tPlease Select an Option...";
    cin >> userOption;
    setcolor(white);
    return userOption;
}
void userPressAnyKey()
{
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    getch();   
}
void greetUser(string userName)
{
    setcolor(blue);
    cout << "\t\t\t\t\t\t\t\t\t\t\tWelcome Back " << userName << endl;
    setcolor(white);
}
void checkPortfolio(float userInvestments[], float userBalances[], int currentIndex, float goldRate)
{
    setcolor(lightcyan);
    cout << "\t\t\t\t\t\t\t\t\t\t\tCash: $" << userBalances[currentIndex] << endl;
    setcolor(yellow);
    if (userInvestments[currentIndex] != 0)
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\t\tGold(in grams): " << userInvestments[currentIndex];
        cout << "\n\t\t\t\t\t\t\t\t\t\t\tGold(in Dollars): " << userInvestments[currentIndex] * goldRate << endl;
    }
    setcolor(white);
}
bool depositMoney(float userBalances[], int currentIndex, float deposit)
{
    bool status = false;
    simulateProcessing();
    if (deposit > 0)
    {
        userBalances[currentIndex] += deposit;
        setcolor(lightgreen);
        cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tYou have successfully deposited \"$" << deposit << "\" into your account." << endl;
        setcolor(yellow);
        cout << "\n\t\t\t\t\t\t\t\t\t\t\tNew Balance: $" << userBalances[currentIndex] << endl;
        setcolor(white);
        status = true;
    }
    return status;
}
void storeTransactionHistory(string transactionsTypes[], float transactions[], int &transactionsIndex, float transactionAmount, string transactionName)
{
    transactions[transactionsIndex] = transactionAmount;
    transactionsTypes[transactionsIndex] = transactionName;
    transactionsIndex++;
}
bool withdrawMoney(float userBalances[], int currentIndex, float withdraw)
{
    bool status = false;
    simulateProcessing();
    setcolor(lightred);
    if (withdraw <= userBalances[currentIndex] && withdraw > 0)
    {
        userBalances[currentIndex] -= withdraw;
        setcolor(green);
        cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tYou have successfully With-Drawn \"$" << withdraw << "\" from your account." << endl;
        setcolor(yellow);
        cout << "\n\t\t\t\t\t\t\t\t\t\t\tNew Balance: $" << userBalances[currentIndex] << endl;
        status = true;
    }
    else if (withdraw > userBalances[currentIndex]) 
        cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tYour Balance is low." << endl;
    setcolor(white);
    return status;
}
bool transferMoney(string userNames[], float userBalances[], int currentIndex, int &transferIndex, int index, float transfer, string name)
{
    bool status = false;
    simulateProcessing();
    bool recieverExists = userExist(userNames, name, index, transferIndex);
    setcolor(lightred);
    if (recieverExists)
    {
        if (transfer <= userBalances[currentIndex] && transfer > 0)
        {
            transferNow(userNames, userBalances, currentIndex, transferIndex, transfer);
            status = true;
        }
        else if (transfer > userBalances[currentIndex]) 
            cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tYour Balance is low." << endl;
        else
            cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tThe attempted transaction was not approved.\n";
    }
    else
        cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tNo such user exists in our database ;(" << endl;
    setcolor(white);
    return status;
}
bool investGold(string userNames[],float userInvestments[], float userBalances[], int currentIndex, int index, float goldRate, float investment)
{
    bool status = false;
    float goldinGrams = investment / goldRate;
    setcolor(green);
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tYou will get " << goldinGrams << "-Gram of Gold.";
    string proceed;
    while(proceed != "2")
    {
        setcolor(yellow);
        cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tDo you want to proceed Press 1(yes) or 2(no)... ";
        cin >> proceed;
        if (proceed == "1")
        {
            simulateProcessing();
            if (investment <= userBalances[currentIndex])
            {
                invest(userBalances, userInvestments, currentIndex, investment, goldinGrams);
                status = true;
                break;
            }
            else if (investment > userBalances[currentIndex])
            {
                setcolor(lightred);
                cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tBalance is Low.";
                break;
            }
        }
        else if (proceed == "2")
        {
            setcolor(lightred);
            cout << "\n\t\t\t\t\t\t\t\t\t\t\tTransaction Terminated.........";
            simulateWithoutTellingLONG();
        }
    }
    setcolor(white);
    return status;
}
void viewTransactions(string transactionsTypes[], float transactions[], int transactionsIndex)
{
    setcolor(yellow);
    for (int i = 0; i < transactionsIndex; i++ )
        cout << "\t\t\t\t\t\t\t\t\t    " << transactionsTypes[i] << "\t\t\t" << transactions[i] << endl;
    setcolor(white);
}
bool blockOrUnblockTransactions(bool blockTransactions)
{
    bool transactionStatus = blockTransactions;
    simulateProcessing();
    if (transactionStatus == false)         
        transactionStatus = true;           // false ---> true
    else
        transactionStatus = false;        // true  ---> false
    return transactionStatus;
}
bool modifyInformation(string userNames[], string userPasswords[], int currentIndex, int index, int &transferIndex, string currentPass)
{
    bool modified = false;
    simulateProcessing();
    if(currentPass == userPasswords[currentIndex])
    {
        string newName;
        setcolor(lightgreen);
        cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tEnter new Name: ";
        cin >> newName;
        bool nameValidation = nameCheck(newName);
        if (!nameValidation)
        {
            invalidNameError();
            return false;    // going back to the menu
        }
        simulateProcessing();
        if(!userExist(userNames,newName, index, transferIndex))                    /// does'nt exist
        {
            string oldName = userNames[currentIndex];         //// optional for output :]
            userNames[currentIndex] = newName;
            setcolor(green);
            cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tYour name was successfully changed from \"" << oldName << "\" to " << "\"" << newName << "\"\n";
            modified = true;
        }
        else
            userAlreadyExists();
    }
    else
        invalidPassError();
    setcolor(white);
    return modified;
}
bool changePassword(string userPasswords[], int currentIndex, string currentPass)
{
    bool passwordModification = false;
    simulateProcessing();
    if(currentPass == userPasswords[currentIndex])
    {
        string newPass;
        newPass = validatePassword("\n\t\t\t\t\t\t\t\t\t\t\tSet New Password: ");
        if (newPass == currentPass)
        {
            setcolor(lightred);
            cout << "\n\t\t\t\t\t\t\t\t\t\t\tNew Password same as Old Password...";
            setcolor(white);
            simulateWithoutTellingLONG();
            return false;                   // as modification was not successful
        }
        userPasswords[currentIndex] = newPass;
        passwordModification = true;
    }
    else
        invalidPassError();
    return passwordModification;
}
bool deleteAccount(string userNames[], string userPasswords[],int currentIndex, int &index, float userBalances[], float userInvestments[], string userIDs[])
{
    bool accountDeletion = false;
    userHeader();
    string currentPass;
    setcolor(yellow);
    cout << "\t\t\t\t\t\t\t\t\t\t\tEnter your Password: ";
    currentPass = maskedPassword();
    simulateProcessing();
    if(currentPass == userPasswords[currentIndex])
    {
        for (int i = currentIndex; i < index; i++)  // shifting the array to left
        {
            userNames[i] = userNames[i+1];
            userPasswords[i] = userPasswords[i+1];
            userBalances[i] = userBalances[i+1];
            userInvestments[i] = userInvestments[i+1];
            userIDs[i] = userIDs[i+1];
        }
        index--;                            // decrementing the index as one account is deleted
        accountDeletion = true;
        setcolor(green);
        cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tYour account has been removed.";
    }
    else
        invalidPassError();
    setcolor(white);
    adminPressAnyKey();
    return accountDeletion;                // returning the status of account deletion
}
void transferNow(string userNames[], float userBalances[], int currentIndex, int transferIndex, float transfer)
{
    userBalances[currentIndex] -= transfer;               //  from user1
    userBalances[transferIndex] += transfer;              //   to user2
    setcolor(green);
    cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tYou have successfully Transfered \"$" << transfer << "\" from your account to the account of \"" << userNames[transferIndex] << "\"" << endl;
    setcolor(yellow);
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tNew Balance: $" << userBalances[currentIndex] << endl;
    setcolor(white);
}
void invest(float userBalances[], float userInvestments[], int currentIndex, float investment, float goldinGrams)
{
    userBalances[currentIndex] -= investment;
    userInvestments[currentIndex] += goldinGrams;
    setcolor(green);
    cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tYou have successfully invested \"$" << investment << "\" into " << goldinGrams << "-Gram of gold..";
    setcolor(yellow);
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tNew Balance: " << userBalances[currentIndex] << endl;
    setcolor(white);
}
////////////////////////////////////////////////////////////////////////////////////////// user  functions  End  ////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////// input validation start //////////////////////////////////////////////////////////////////////////////////////////////////////////
void viewTransactionsHeader()
{
    setcolor(blue);
    cout << "\t\t\t\t\t\t\t\t       #################################################" << endl;
    setcolor(lightcyan);
    cout << "\t\t\t\t\t\t\t\t\t  Transaction Type\t     Amount($)" << endl;
    setcolor(blue);
    cout << "\t\t\t\t\t\t\t\t       #################################################" << endl << endl;                
    setcolor(white);
}
void showBalance(float userBalances[], int currentIndex)
{
    setcolor(yellow);
    cout << "\t\t\t\t\t\t\t\t\t\t\tYour Balance: $" << userBalances[currentIndex] << endl << endl;
    setcolor(white);
}
void goldHeader(float goldRate)
{
    setcolor(blue);
    cout << "\t\t\t\t\t\t\t\t\t\t\t1-Gram of Gold = $" << goldRate << endl;
    setcolor(white);
}
void transactionError()
{
    setcolor(red);
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tThe attempted transaction was not approved.\n";
    simulateWithoutTellingLONG();
    setcolor(white);
}
void passNotCorrect()
{
    setcolor(lightred);
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tInvalid Password" << endl;
    setcolor(white);
    cout << "\t\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    getch();
}
void accountNotExists()
{
    setcolor(lightred);
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tAccount does'nt Exist" << endl;
    setcolor(white);
    cout << "\t\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    getch();
}
bool checkUserValidity(string userNames[], string userPasswords[], int index, int &currentIndex,  string name, string pass)
{
    bool validPass = false;
    for (int i = 0; i < index; i++)
    {
        if (name == userNames[i] && pass == userPasswords[i])
        {
            validPass = true;
            currentIndex = i;
            break;
        }    
    }
    return validPass;
}
bool userExist(string userNames[], string name, int index, int &transferIndex)
{
    bool exists = false;
    for (int i = 0; i < index; i++)
    {
        if (name == userNames[i])
        {
            exists = true;    
            transferIndex = i;       // for transfer of cash  
            break;
        }
    }
    return exists;
}
bool uniqueUser(string userNames[], int &index, string name)
{
    bool unique = true;     
    for (int i = 0; i < index; i++)    // looping through names array to check if new user 
    {
        if (name == userNames[i])
        {
            unique = false;
            break;
        }
    }
    return unique;
}
///////////////////////////////////////////////////////////////////////////////////////// input validation end  //////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////// start of signUp/signIn //////////////////////////////////////////////////////////////////////////////////////////////////////////
bool nameCheck(string name)  ///username when signup
{
    bool found = true;
    if (name.length() < 3)   // name length can't be less then 3
        return false;
	for (int i = 0; i < name.length(); i++)    // loop to check if name have any special characters
	{
		if ((name[i] < 'A' || name[i] > 'Z') && (name[i] < 'a' || name[i] > 'z'))
        {
            found = false;
            break;
        }
	}
	return found;
}
bool adminLoginCheck(string pass, string &adminPassword)
{
    bool login = false; 
    if (pass == adminPassword)
        login = true;
    return login;
}
bool createUser(string userNames[], string userPasswords[], string userIDs[], int &index, string name, string pass)
{
    simulateProcessing();
    /// assigning values
    userNames[index] = name;
    userPasswords[index] = pass;
    userIDs[index] = "000"; 
    userIDs[index] += to_string(index+1);
    index++;  
    setcolor(lightgreen);
    cout << endl << endl << "\t\t\t\t\t\t\t\t\t\t\tSuccessfully created new user" << endl;
    setcolor(white);
    return true;
}
void invalidNameError()
{
    setcolor(lightred);
    cout << "\t\t\t\t\t\t\t\t\t\t\tInvalid Name....";
    setcolor(white);
    simulateWithoutTellingLONG();                    
}
void simulateProcessing()
{
    setcolor(lightblue);
    cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tProcessing please wait...";
    setcolor(white); 
    Sleep(800);
}
void simulateWithoutTellingLONG()
{
    Sleep(700);
}
void simulateWithoutTelling()
{
    Sleep(500);
}
// data storage
void loadUserDATA(string userNames[], string userPasswords[], string userIDs[], float userBalances[], float userInvestments[], int &index)
{
    try
    {
        fstream loadFile;
        string data = "";
        loadFile.open("userData.csv", ios::in);
        bool firstIteration = true;
        while (!loadFile.eof())
        {
            getline(loadFile, data);
            if (firstIteration)
            {
                firstIteration = false;
                continue;
            }
            userNames[index] = getFieldData(data, 0);
            userPasswords[index] = getFieldData(data, 1);
            userIDs[index] = getFieldData(data, 2);
            userBalances[index] = stof(getFieldData(data, 3));
            userInvestments[index] = stof(getFieldData(data, 4));
            index++;
        }
        loadFile.close();
    }
    catch(std::invalid_argument)
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        setcolor(lightred);
        remove("userData.csv");     /// removing the file as it is corrupted
        cout << "\n\t\t\t\t\t\t\t\t\t\t\tData file for user is corrupted.";
        cout << "\n\t\t\t\t\t\t\t\t\t\t\tCreating new record file"; 
        cout << "\n\t\t\t\t\t\t\t\t\t\t\tDo you want to proceed.";
        userPressAnyKey();
        setcolor(white);
    }
}
void storeAdminDATA(string bankAssets[], string bankAssetsWorth[], int &assetIndex, string &adminPassword, float &goldRate)
{
    fstream file;
    file.open("adminData.csv", ios::out);
    file << adminPassword << "," << goldRate;
    // if no assets then return
    if (assetIndex == 0)
        return;
    // else add new line
    file << "\n";    
    for (int i = 0; i < assetIndex; i++)
    {
        file << bankAssets[i] << "," << bankAssetsWorth[i];
        if (i != assetIndex - 1)
            file << "\n";
    }
    file.close();
}
void loadAdminDATA(string bankAssets[], string bankAssetsWorth[], int &assetIndex, string &adminPassword, float &goldRate)
{
    try
    {
        fstream loadFile;
        string data = "";
        loadFile.open("adminData.csv", ios::in);
        bool firstIteration = true;
        while (!loadFile.eof())
        {
            getline(loadFile, data);
            if (firstIteration)
            {
                adminPassword = getFieldData(data, 0);
                goldRate = stof(getFieldData(data, 1));        
                firstIteration = false;
                continue;
            }
            bankAssets[assetIndex] = getFieldData(data, 0);
            bankAssetsWorth[assetIndex] = getFieldData(data, 1);
            assetIndex++;
        }
        loadFile.close();
    }
    catch(std::invalid_argument)
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        setcolor(lightred);
        remove("adminData.csv");     /// removing the file as it is corrupted
        cout << "\n\t\t\t\t\t\t\t\t\t\t\tData file for admin is corrupted.";
        cout << "\n\t\t\t\t\t\t\t\t\t\t\tCreating new record file"; 
        cout << "\n\t\t\t\t\t\t\t\t\t\t\tDo you want to proceed.";
        userPressAnyKey();
        setcolor(white);
    }
}
string getFieldData(string data, int count)
{
    string result = "";      
    int comma = 0;
    for (int i =0; i<data.length(); i++)
    {
        if (data[i] == ',')
            comma++;
        else if (comma == count)
            result += data[i];
        else if (comma > count)
            break;
    }
    return result;
}
void storeDataLocally(string userNames[], string userPasswords[], string userIDs[], float userBalances[], float userInvestments[], string transactionsTypes[], float transactions[], int index)
{
    fstream storeFile;
    storeFile.open("userData.csv", ios::out);
    storeFile << "Name,Password,ID,Balance,Investments\n";
    for (int i = 0; i < index; i++)
    {
        storeFile << userNames[i] << "," << userPasswords[i] << "," << userIDs[i] << "," << to_string(userBalances[i]) << "," << to_string(userInvestments[i]); 
        if (i != index - 1)     // last line not adding "\n"
            storeFile << "\n";
    }
    storeFile.close();
}
// xtra functions
string getAdminPass()
{
    string userEnterAdminPass;
    setcolor(lightcyan);    
    cout << "\t\t\t\t\t\t\t\t\t\t\tEnter the Password: ";
    userEnterAdminPass = maskedPassword();       /// pass in  '***' format
    setcolor(white);
    return userEnterAdminPass;        
}
void accessDeniedError()
{
    setcolor(lightred);
    cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tAccess Denied.............." << endl;
    setcolor(white);
}
string getUserEnteredName()
{
retakeNameInputSignIN:   // if invalid name then again
    signInHeader();
    string userEnteredName;
    setcolor(lightcyan);
    cout << "\t\t\t\t\t\t\t\t\t\t\tEnter your User Name: ";
    cin >> userEnteredName;
    bool nameValidation = nameCheck(userEnteredName);
    if (!nameValidation)
    {
        invalidNameError();
        goto retakeNameInputSignIN;
    }
    setcolor(white);
    return userEnteredName;
}
string getNAME()
{
retakeNameInputSignUP:   // if invalid name then again
    signUpHeader();
    string name;
    setcolor(lightcyan);
    cout << "\t\t\t\t\t\t\t\t\t\t\tEnter your name: ";
    cin >> name;
    bool nameValidation = nameCheck(name);
    if (!nameValidation)
    {
        invalidNameError();
        goto retakeNameInputSignUP;
    }
    return name;
}
void userAlreadyExists()
{
    setcolor(lightred);
    cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tUser Already Exists....";
    setcolor(white);
}
void terminateProgram()
{
    setcolor(red);
    cout << "\t\t\t\t\t\t\t\t\t\t\tTerminating the program....";
    setcolor(white);
    simulateWithoutTelling();        
    system("cls");
}
void invalidChoiceError()
{
    setcolor(lightred); 
    cout << "\t\t\t\t\t\t\t\t\t\t\tInvalid choice....";
    setcolor(white);   
    simulateWithoutTelling(); 
}
float validateFloatInput(string statement)
{
    string deposit;
    float temp;
    setcolor(yellow);
    cout << statement;
    cin >> deposit;
    setcolor(white);
    try
    {
        temp = stof(deposit);       /// temp storing the value to check if it is float or not
    }
    catch(invalid_argument)
    {
        invalidInputError();
        validateFloatInput(statement);   // recursive call
    }
    catch(out_of_range)
    {
        areYouMadError();       
        validateFloatInput(statement);
    }
    return temp;  
}
void invalidInputError()
{
    setcolor(lightred);
    cout << "\t\t\t\t\t\t\t\t\t\t\tInvalid Input...";
    simulateWithoutTellingLONG();
    setcolor(white);
}
void areYouMadError()
{
    setcolor(lightred);
    cout << "\t\t\t\t\t\t\t\t\t\t\tAre you mad??...";
    simulateWithoutTellingLONG();
    setcolor(white);
}
string maskedPassword()
{
    char singleLetter;
    string completeWord;
    while (true)
    {
        singleLetter = getch();
        if (singleLetter == '\r')   // enter key return the string
        {
            break;
        }
        else if (singleLetter != ',' && singleLetter != ' ' && singleLetter != '\b') // characters other then these will be printed
        {
            cout << "*";
            completeWord += singleLetter;
        }
    }
    cout << endl;
    return completeWord;
}
/////////////////////////////////////////////////////////////////////////////////////// end of signUp/SignIn /////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////   headers   start    //////////////////////////////////////////////////////////////////////////////////////////////////////////////   
void header()
{
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    system("cls");
    cout << R"(                                                                         ______                                                    )" << endl;
    cout << R"(                                                                        /\  _  \                                                   )" << endl;
    cout << R"(                                                                        \ \ \L\ \    ____     __  __    _ __      __               )" << endl;
    cout << R"(                                                                         \ \  __ \  /\_ ,`\  /\ \/\ \  /\`'__\  /'__`\             )" << endl;
    cout << R"(                                                                          \ \ \/\ \ \/_/  /_ \ \ \_\ \ \ \ \/  /\  __/             )" << endl;
    cout << R"(                                                                           \ \_\ \_\  /\____\ \ \_____\ \ \_\  \ \____\            )" << endl;
    cout << R"(                                                                            \/_/\/_/  \/____/  \/______\ \/_/   \/____/            )" << endl;
    cout << R"(                                                                                                                                   )" << endl;
    cout << R"(                                                                                                                                   )" << endl;
    cout << R"(                                                               ____                     __           ______                        )" << endl;
    cout << R"(                                                              /\  _`\                  /\ \         /\__  _\                       )" << endl;
    cout << R"(                                                              \ \ \L\ \     __      ___\ \ \/'\     \/_/\ \/     ___     ___       )" << endl;
    cout << R"(                                                               \ \  _ <'  /'__`\  /' _ `\ \ , <        \ \ \   /' _ `\  /'___\     )" << endl;
    cout << R"(                                                                \ \ \L\ \/\ \L\.\_/\ \/\ \ \ \\`\       \_\ \__/\ \/\ \/\ \__/  __ )" << endl;
    cout << R"(                                                                 \ \____/\ \__/.\_\ \_\ \_\ \_\ \_\     /\_____\ \_\ \_\ \____\/\_\)" << endl;
    cout << R"(                                                                  \/___/  \/__/\/_/\/_/\/_/\/_/\/_/     \/_____/\/_/\/_/\/____/\/_/)" << endl;
    cout << endl;
    cout << "                                                                  ####################################################################" << endl; 
    cout << endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void signInHeader()
{
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    cout << R"(                                                                     ____                                      )" << endl;
    cout << R"(                                                                    /\  _`\   __                               )" << endl;
    cout << R"(                                                                    \ \,\L\_\/\_\     __     ___               )" << endl;
    cout << R"(                                                                     \/_\__ \\/\ \  /'_ `\ /' _ `\             )" << endl;
    cout << R"(                                                                       /\ \L\ \ \ \/\ \L\ \/\ \/\ \            )" << endl;
    cout << R"(                                                                       \ `\____\ \_\ \____ \ \_\ \_\           )" << endl;
    cout << R"(                                                                        \/_____/\/_/\/___L\ \/_/\/_/           )" << endl;
    cout << R"(                                                                                      /\____/                  )" << endl;
    cout << R"(                                                                                      \_/__/                   )" << endl;
    cout << R"(                                                                                ______                         )" << endl;
    cout << R"(                                                                               /\__  _\                        )" << endl;
    cout << R"(                                                                               \/_/\ \/     ___                )" << endl;
    cout << R"(                                                                                  \ \ \   /' _ `\              )" << endl;
    cout << R"(                                                                                   \_\ \__/\ \/\ \             )" << endl;
    cout << R"(                                                                                   /\_____\ \_\ \_\            )" << endl;
    cout << R"(                                                                                   \/_____/\/_/\/_/            )" << endl;
    cout << endl;
    cout << "                                                                            ################################" << endl << endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void signUpHeader()
{
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    cout << R"(                                                                      ____                                      )" << endl;
    cout << R"(                                                                     /\  _`\   __                               )" << endl;
    cout << R"(                                                                     \ \,\L\_\/\_\     __     ___               )" << endl;
    cout << R"(                                                                      \/_\__ \\/\ \  /'_ `\ /' _ `\             )" << endl;
    cout << R"(                                                                        /\ \L\ \ \ \/\ \L\ \/\ \/\ \            )" << endl;
    cout << R"(                                                                        \ `\____\ \_\ \____ \ \_\ \_\           )" << endl;
    cout << R"(                                                                         \/_____/\/_/\/___L\ \/_/\/_/           )" << endl;
    cout << R"(                                                                                       /\____/                  )" << endl;
    cout << R"(                                                                                       \_/__/                   )" << endl;
    cout << R"(                                                                                 __  __                         )" << endl;
    cout << R"(                                                                                /\ \/\ \                        )" << endl;
    cout << R"(                                                                                \ \ \ \ \  _____                )" << endl;
    cout << R"(                                                                                 \ \ \ \ \/\ '__`\              )" << endl;
    cout << R"(                                                                                  \ \ \_\ \ \ \L\ \             )" << endl;
    cout << R"(                                                                                   \ \_____\ \ ,__/             )" << endl;
    cout << R"(                                                                                    \/_____/\ \ \/              )" << endl;
    cout << R"(                                                                                             \ \_\              )" << endl;
    cout << R"(                                                                                              \/_/              )" << endl;
    cout << endl;
    cout << "                                                                            ################################" << endl << endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void adminLoginHeader()
{
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    cout << R"(                                                                      ______      __                                  )" << endl;
    cout << R"(                                                                     /\  _  \    /\ \              __                 )" << endl;
    cout << R"(                                                                     \ \ \L\ \   \_\ \    ___ ___ /\_\    ___         )" << endl;
    cout << R"(                                                                      \ \  __ \  /'_` \ /' __` __`\/\ \ /' _ `\       )" << endl;
    cout << R"(                                                                       \ \ \/\ \/\ \L\ \/\ \/\ \/\ \ \ \/\ \/\ \      )" << endl;
    cout << R"(                                                                        \ \_\ \_\ \___,_\ \_\ \_\ \_\ \_\ \_\ \_\     )" << endl;
    cout << R"(                                                                         \/_/\/_/\/__,_ /\/_/\/_/\/_/\/_/\/_/\/_/     )" << endl;
    cout << R"(                                                                                                                      )" << endl;
    cout << R"(                                                                                                                      )" << endl;
    cout << R"(                                                                             __                                       )" << endl;
    cout << R"(                                                                            /\ \                      __              )" << endl;
    cout << R"(                                                                            \ \ \        ___      __ /\_\    ___      )" << endl;
    cout << R"(                                                                             \ \ \  __  / __`\  /'_ `\/\ \ /' _ `\    )" << endl;
    cout << R"(                                                                              \ \ \L\ \/\ \L\ \/\ \L\ \ \ \/\ \/\ \   )" << endl;
    cout << R"(                                                                               \ \____/\ \____/\ \____ \ \_\ \_\ \_\  )" << endl;
    cout << R"(                                                                                \/___/  \/___/  \/___L\ \/_/\/_/\/_/  )" << endl;
    cout << R"(                                                                                                  /\____/             )" << endl;
    cout << R"(                                                                                                  \_/__/              )" << endl;
    cout << endl;
    cout << "                                                                              #########################################" << endl << endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void userHeader()
{
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    cout << R"(                                                                                 __  __                          )" << endl;
    cout << R"(                                                                                /\ \/\ \                         )" << endl;
    cout << R"(                                                                                \ \ \ \ \    ____     __   _ __  )" << endl;
    cout << R"(                                                                                 \ \ \ \ \  /',__\  /'__`\/\`'__\)" << endl;
    cout << R"(                                                                                  \ \ \_\ \/\__, `\/\  __/\ \ \/ )" << endl;
    cout << R"(                                                                                   \ \_____\/\____/\ \____\\ \_\ )" << endl;
    cout << R"(                                                                                    \/_____/\/___/  \/____/ \/_/ )" << endl;
    cout << endl;         
    cout << "                                                                                      ##############################" << endl;
    cout << endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void managerHeader()
{
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    cout << R"(                                                                      /'\_/`\                                                   )" << endl;
    cout << R"(                                                                     /\      \     __      ___      __       __      __   _ __  )" << endl;
    cout << R"(                                                                     \ \ \__\ \  /'__`\  /' _ `\  /'__`\   /'_ `\  /'__`\/\`'__\)" << endl;
    cout << R"(                                                                      \ \ \_/\ \/\ \L\.\_/\ \/\ \/\ \L\.\_/\ \L\ \/\  __/\ \ \/ )" << endl;
    cout << R"(                                                                       \ \_\\ \_\ \__/.\_\ \_\ \_\ \__/.\_\ \____ \ \____\\ \_\ )" << endl;
    cout << R"(                                                                        \/_/ \/_/\/__/\/_/\/_/\/_/\/__/\/_/\/___L\ \/____/ \/_/ )" << endl;
    cout << R"(                                                                                                             /\____/            )" << endl;
    cout << R"(                                                                                                             \_/__/             )" << endl;
    cout << endl;        
    cout << "                                                                        ##########################################################" << endl;
    cout << endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
string setcolor(unsigned short color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
    return "";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////   headers   end    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////// End of Program ////////////////////////////////////////////////////////////////////////////////////////////////////////////