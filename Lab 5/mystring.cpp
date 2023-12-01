//Kayleigh Vu & Monica Sommer
//Functions coded by kayleigh or monica is marked in the header file
//Lab 5 - Implementation File
//test cases were just changing the inputs in the given tester.cpp file

#include <iostream>
#include <cassert>
#include <cstring>
#include "mystring.h"

using std::cout;
using std::cin;

namespace coen79_lab5 {
    // CONSTRUCTOR, COPY CONSTRUCTOR, and DESTRUCTOR
    //Constructor with new string of character array
    string::string(const char str[ ])
    {
        current_length = strlen(str);
        allocated = current_length + 1;
        characters = new char[allocated];   //creates a new string of characters of size allocated
        strncpy(characters, str, allocated);
    }

    //Constructor creating new function with length 1
    string::string(char c)
    {
        current_length = sizeof(c);
        allocated = current_length + 1;
        characters = new char[allocated];
        characters[0] = c;
        characters[1] = '\0';
    }

    //Copy constructor, creates new string copied from existing
    string::string(const string& source)
    {
        current_length = source.length();
        allocated = current_length + 1;
        characters = new char[allocated];
        strncpy(characters, source.characters, allocated);
    }

    //Destructor to delete string/char array
    string::~string()
    {
        delete[] characters;    //delete operator to delete a string
    }
        
    // MODIFICATION MEMBER FUNCTIONS
    //
    void string::operator +=(const string& addend)
    {
        current_length += addend.current_length;
        allocated = current_length + 1;
        reserve(allocated);
        strncat(characters, addend.characters, addend.current_length);
    }

    void string::operator +=(const char addend[ ])
    {
        current_length += strlen(addend);
        allocated = current_length + 1;
        reserve(allocated);
        strncat(characters, addend, strlen(addend));
    }

    void string::operator +=(char addend)
    {
        current_length++;
        allocated = current_length +1;
        reserve(allocated);
        characters[current_length-1] = addend;
        characters[current_length] = '\0';
    }

    void string::reserve(size_t n) {
        char *tmp = new char[n];
        if(characters != NULL)
        {
            strncpy(tmp, characters, current_length);
            delete[] characters;
        }
        allocated = n;
        characters = tmp;
    }

    string &string::operator =(const string& source)
    {
        if(this == &source) {
            return *this; //handles self-assignment
        }
        dlt(0, current_length); //delete string so it can be replaced
        if (current_length != source.current_length) {
            //If they are not the same, we reallocated
            allocated = source.allocated;
            reserve(allocated);
        }
        strncpy(characters, source.characters, source.current_length);
        current_length = source.current_length;
        return *this;
    }

    void string::insert(const string& source, unsigned int position)
    {
        assert(position <= length());
        current_length = source.length() + current_length;
        string temp = *this;
        
        if (allocated < current_length)
        {
            reserve(current_length + 1);
        }

        strncpy(characters, temp.characters, position);
        characters[position] = '\0';
        strncat(characters, source.characters, source.length());
        characters[position + source.length()] = '\0';
        strncat(characters, temp.characters + position, allocated - position);
        characters[current_length] = '\0';
    }
    
    void string::dlt(unsigned int position, unsigned int num) 
    {
        assert((position + num) <= length());

        for (int i = position; i < length(); i++) 
        {
            characters[i] = characters[num + i];
        }
        current_length = current_length - num;
    }

    void string::replace(char c, unsigned int position)
    {
        assert(position < length());
        characters[position] = c;
    }

    void string::replace(const string& source, unsigned int position)
    {
        assert(position + source.length() <= length());
        for (int i = 0; i < source.length(); i++) 
        {
            characters[position + i] = source[i];
        }
    }
        
    // CONSTANT MEMBER FUNCTIONS    
    char string::operator [ ](size_t position) const
    {
        assert(position < length()); //precondition
        return characters[position]; //return character at specified position
    }

    //postcondition: return the location of the first occurance of character c
    //return -1 if character c is not found within string
    int string::search(char c) const
    {
        for (int i = 0; i < length(); i++)  //iterate through string
        {
            if (characters[i] == c)
            {
                return i;   //returning loc of first occurance
            }
        }
        return -1;  //else return -1
    }

    int string::search(const string& substring) const
    {
        int total = 0;
        for (int i = 0; i < length(); i++) 
        {
            if (characters[i] == substring[0]) 
            {
                for (int j = 0; j < substring.length(); j++) 
                {
                    if (characters[i + j] == substring[j]) 
                    {
                        total++;
                    }
                }
                if (total == substring.length()) 
                {
                    return i;
                }
                total = 0;
            }
        }   
    return -1;
    }

    //Post-condition: The count of the occurrence of the character c within this
    //string is returned.
    //This function counts the number of times the character c occurs in the string
    unsigned int string::count(char c) const 
    {
        unsigned int total = 0;
        for (int i = 0; i < length(); i++)
        {
            if (characters[i] == c) 
            {
                total++;
            }
        }
        return total;
    }
        
    // FRIEND FUNCTIONS
    std::ostream& operator <<(std::ostream& outs, const string& source)
    {
        outs << source.characters;
        return outs;
    }

    bool operator ==(const string& s1, const string& s2)
    {
        if (strcmp(s1.characters, s2.characters) == 0) { return 1; }
        else { return 0; }
    }

    bool operator !=(const string& s1, const string& s2)
    {
        if (strcmp(s1.characters, s2.characters) != 0) { return 1; }
        else { return 0; }
    }

    bool operator >(const string& s1, const string& s2)
    {
        if (strcmp(s1.characters, s2.characters) > 0) { return 1; }
        else { return 0; }
    }

    bool operator <(const string& s1, const string& s2)
    {
        if (strcmp(s1.characters, s2.characters) < 0) { return 1; }
        else { return 0; }
    }

    bool operator >=(const string& s1, const string& s2)
    {
        if ((s1 > s2) || (s1 == s2)) { return 1; }
        else { return 0; }
    }

    bool operator <=(const string& s1, const string& s2)
    {
        if ((s1 < s2) || (s1 == s2)) { return 1; }
        else { return 0; }
    }

    // NON-MEMBER FUNCTIONS for the string class
    string operator +(const string& s1, const string& s2)
    {
        string s3(s1);
        s3 += s2;
        return s3;
    }

    //addition of two given strings using another temporary string to 
    string operator +(const string& s1, const char addend[ ])
    {
        string s3(s1);
        s3 += addend;
        return s3;
    }

    //function to read given string ins and skip the white space at the start of string ins 
    //reads up to the white space or end of file
    std::istream& operator >>(std::istream& ins, string& target)
    {
        char *temp = new char[100];
        
        //ignores the white space other than the characters in the string
        //peek returns the next character in sequence 
        while (ins && isspace(ins.peek())) 
        {
            ins.ignore();
        }
        ins >> temp;
        target = string(temp);
        return ins;
    }
}