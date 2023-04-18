#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/*
    Precondition: The text file must be able to be accessed 

    Postcondition: Displays a list of words from a given text file that are at least 10 characters long and all uppercased
*/

void toUpperCase(string word)
{
    for (int i = 0; i < word.length(); i++) //given a word, sequentially accessing each character and setting to upper case
    {
        word[i] = toupper(word[i]);
    }
    cout << word << endl;
}

int main(int argc, char *argv[])
{
    if (!(argc > 1)) 
    {
        cout << "No file was entered...\n";
        return -1;
    }
    ifstream textFile(argv[1]); //calling the text file and setting it's name to textFile
    string text;

    if (!textFile.is_open()) //if textFile cannot be opened
    {
        cout << "Error, cannot open file\n";
        return 1; 
    }

    while (textFile >> text) //recording the text file's data one string at a time
    {
        for (int i = 0; i < text.length(); i++) //accessing each character of each string 
        {
            if (!(isalnum(text[i]) > 0)) //if character is non-alphanumeric, then erase it
            {
                text.erase(i, i+1);
                i--;
            }
        }
        if (text.length() >= 10) //if the length of the string is at least 10 characters long
        {
            toUpperCase(text); //calling the toUpperCase function with parameter text
        }
    }
    textFile.close(); //closing the text file
}