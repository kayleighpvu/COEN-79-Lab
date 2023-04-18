#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>

using namespace std;

/*
    Precondition: Prompts user to think of a number between 1 and 20

    Postcondition: Displays out the correct number of times it took to guess the correct number 1-20 for the user
*/

int main()
{
    srand(time(NULL));

    string reply;
    int counter = 0;

    cout << "\nThink of a number between 1 and 20. Press enter when you are ready.";
    cin.ignore(); 
    cout << endl;
    int guess = (rand() % 20) + 1; //generate a random number between 1 and 20

    do 
    {
        cout << "Is the number " << guess << " (Y or N) ";
        cin >> reply;
        if ((reply == "N") || (reply == "n") || (reply == "no")) //if guess was not correct
        {
            guess = (rand() % 20) + 1; //set a new guess
            counter++; //add 1 to steps counter
        }
        else if ((reply == "Y") || (reply == "y") || (reply == "yes")) //if guess was correct, breaking out of loop
        {
            break;
        }
        else
        {
            cout << "Please only enter Y or N\n"; //if anything not accepted was inputted by user
        }

    } while ((reply != "Y") || (reply != "y") || (reply != "yes")); //conditions of while loop
    counter++;
        
    cout << endl << "I found the number in " << counter << " step(s)\n\n";
    
}
