#include <iostream>
#include <string>
using namespace std;

/*
    Precondition: The number of alphanumeric characters and non-alphanumeric characters must be >= 0

    Postcondition: Displays the number of alphanumeric characters and non-alphanumeric characters from the user's input
*/

int main()
{
    string text;
    int alphaNum = 0;
    int nalphaNum = 0;
    cout << "Enter some text:\n"; //ask the user to input a text of random characters
    getline(cin,text); //read/get the entire inputted line
    cout << endl;

    for (int i = 0; i < text.size(); i++) //iterating the text
    {
        if (isalnum(text[i]) > 0) //if alphanumeric character, add to alphaNum counter;
        {
            alphaNum++;
        }
        else
        { 
            if (text[i] != 32) { nalphaNum++; } //if character in string is not a space, then add to nalphaNum counter
        }
    }

    cout << "Number of alphanumeric characters: " << alphaNum << endl;
    cout << "Number of non-alphanumeric characters: " << nalphaNum << endl;
}