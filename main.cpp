// AUTHOR: Shallu Nah                                                                                                                                                                                  //
// PROGRAM DESCRIPTION: The program calculate and print out bills for the city water company.
// INPUT: Reads the The customer 4-digit account number, the type of water services, home, commercial,
// or industrial, and the amount of gallons require.
// PROCESSING: The program calculates the costs base on the type of account and amount of gallons of water used.
// OUTPUT: The program output the chosen account plan, the number of gallons of water and the total bill.

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cctype>

using namespace std;

char validateCode(char& promptCode, double& numGallons);
double calBillTotal(char promptCode, double numGallons);
void disOutput(char codeType, double& gallons, double& totalbill);

// Description: Main() Reads the  The validate code function which determine the type of account
// and the number of gallons, and the calculate bill total   function which determine the bill total,
// and the display function to display the result.
// Returns:  0 if successful
int main()
{
    char codeSel;
    char codeType;
    double gallons;
    double totalbill;
    int accountNumber, flag = 0;
    char resp = 'y';
    do {
        //Read input from user
        cout << " This program will calculate a bill for the city water company" << endl << endl;
        while (flag == 0) {

            cout << " Enter your 4-digit account number: ";
            cin >> accountNumber;
            cout << endl;

            if (accountNumber / 1000 > 0 && accountNumber / 10000 == 0){
                flag = 1;
            }
            else {
                cout << " ERROR, enter an account number with (no leading zeros) " << endl;
            }
        }

        codeType = validateCode(codeSel, gallons);
        cout << endl;

        totalbill = calBillTotal(codeType, gallons);
        cout << endl;
        disOutput(codeType, gallons, totalbill);
        cout << endl;

        cout << " Calculate another bill (y/n)? ";
        cin >> resp;
        cout << endl;
    } while (resp != 'n');
    cout << endl;

    return 0;

}
// Description:  The function determines the validate code, the type of account ,and the number of gallons
// Input parameter:  Take in two input parameter,  which is reference  back to main() function
// Returns:  the type of account, and number gallons of water, if successful
char validateCode(char& promptCode, double& numGallons) {
    cout << " Code H: for home enter (code H)" << endl;
    cout << " Code C: for commercial use enter (code C)" << endl;
    cout << " Code I: for industrial use enter (code I). " << endl << endl;
    cout << " Enter a code letter from the Menu above: ";
    cin >> promptCode;
    promptCode = toupper(promptCode);
    cout << endl;

    while (promptCode != 'H' && promptCode != 'C' && promptCode != 'I') {
        cout << " Error - entered a valid choice from the Menu above: " << endl;
        cout << " Enter a code letter from the Menu above: ";
        cin >> promptCode;
        promptCode = toupper(promptCode);

    }

    if (promptCode == 'H' || promptCode == 'C' || promptCode == 'I')
        cout << " Enter the number of gallons: ";
    cin >> numGallons;
    while (numGallons < 0) {
        cout << " Error - entered a valid choice from the Menu above: " << endl;
        cout << " Enter a code letter from the Menu above: ";
        cin >> numGallons;
    }

    return promptCode;
}

// Description:  The function determines the validate code, and the type of account and the number of gallons
// Input parameter:  Take in two input parameter,  the type of account, and number of gallons
// Returns:  the Rate Fees base on the above function, if successful
double calBillTotal(char promptCode, double numGallons) {

    const double HGAL_FLATFEE = 15.00;
    const double H_DISCOUNTS = .0025;
    const double CGAL = 1000.00;       // for the first 500,000 gallons used
    const double C_ADDITIONAL_GAL = .0022;
    const double IGAL = 1000.00;    // for usage up to 600,000 gallons
    const double IGAL2 = 2000.00;  // if usage is over 600,000 gallons but does not exceed 1 million gallons;
    const double IGAL3 = 3000.00; // if usage is over 1 million gallons
    double rateFees;
    double gallonsCost;

    if (promptCode == 'H') {

        gallonsCost = HGAL_FLATFEE;
        rateFees = gallonsCost + numGallons*H_DISCOUNTS;

    }
    else if (promptCode == 'C') {

        if (numGallons <= 500000) {
            rateFees = CGAL;
        }
        else if (numGallons > 500000) {
            gallonsCost = numGallons * C_ADDITIONAL_GAL;
            rateFees = gallonsCost + CGAL;
        }
        else {

            gallonsCost = numGallons * C_ADDITIONAL_GAL;
            rateFees = CGAL + gallonsCost;
        }
    }
    else if (promptCode == 'I') {

        if (numGallons <= 600000) {

            rateFees = IGAL;
        }
        else if (numGallons <= 1000000) {

            rateFees = IGAL2;
        }
        else if (numGallons > 1000000) {
            rateFees = IGAL3;
        }

    }

    return rateFees;
}

// Description:  The function display the chosen plan for the account, the number of gallons,and the bill                                                                                            // //
// Input parameter:  Take in three input parameter,  the type of account,number of gallons, and the bill
// Returns:  the plan, number of gallons of water, and bill to the user, if successful
void disOutput(char codeType, double& gallons, double& totalbill) {

    cout << " Details bill for the city water company" << endl << endl;
    if (codeType == 'H') {
        cout << setw(5) << " The Chosen Plan:" << setw(20) << "Code H:" << endl;
    }
    else if (codeType == 'C') {
        cout << setw(5) << " The Chosen Plan:" << setw(20) << "Code C:" << endl;
    }
    else if (codeType == 'I') {
        cout << setw(5) << " The Chosen Plan:" << setw(20) << "Code I:" << endl;
    }
    cout << setw(5) << " The Number of Gallons:" << setw(13) << gallons << endl;
    // Dividers
    cout << setw(30) << "" << setfill('-') << setw(12) << "" << setfill(' ') << endl;
    cout << " The Bill Is: " << setw(20) << /*fixed << setprecision(2) <<*/  "$" << totalbill << endl;
}
