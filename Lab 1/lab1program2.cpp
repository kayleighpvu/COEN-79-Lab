#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
int flag;

/*
    Precondition: The string of digits must be exactly 10 digits long

    Postcondition: Displays the inputted string of 10 digits and in its reverse form in the format shown in the instructions
*/

void reversedDigits(string revDigits) //reversing the string
{
    int length = revDigits.length();
    int x = length;
    while(x--) cout << revDigits[x]; //iterate backwards through string parameter and print it forwards
}

int checkForChar(string input, int x) //checking for a non integer character in string
{
    flag = x;
    for (int i = 0; i < input.size(); i++) //loop through entire string
    {
        if (!(isdigit(input[i]))) { flag = 1; } //if non integer character found, set flag to 1
    }
    cout << flag;
}

int main(void)
{
    string digits;

    cout << "Input String of 10 digits (no spaces):\n";
    cin >> digits;
    cout << endl;

    while (true) //keeping the loop going till the break;
    {
        checkForChar(digits, 0); //calling the checkForChar function
        if (digits.size() != 10 || flag == 1) //if the string size is not 10 and there is a non integer number in user input string
        {
            cout << "Error! Input String of 10 digits (no spaces):\n";
            cin >> digits; 
        }
        else 
        { 
            break; 
        }
    }

    int x = 14; //setting the initial width to 14
    for (int i = 0; i < 5; i++) //want 6 rows of output starting at 0
    {
        cout << setw(x); 
        cout << digits;
        cout << setw(x); //reapply width between string and its reverse
        reversedDigits(digits); //call the reverse string
        cout << endl;
        x += 2;
    }
}
