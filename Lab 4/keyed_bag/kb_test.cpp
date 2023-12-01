//testing file for keyed_bag
//Kayleigh Vu & Monica Sommer
//COEN 79 Lab 4 Eskafi 

#include <cstdio>
#include <iostream>
#include "keyed_bag.h"

using namespace std;
using coen79_lab4::keyed_bag;

void Insert(const int val, const string& key, keyed_bag& kb) {
    cout << "Inserting "<<val<<" with key \""<<key<<"\"." << endl;
    kb.insert(val, key);
}

void Erase(const string& key, keyed_bag& kb) {
    cout << "Erasing \""<< key <<"\"." << endl;
    kb.erase(key);
}

void Get(const string & key, const keyed_bag& kb) {
    cout << "Value for \""<<key<<"\": " << kb.get(key) << endl;
}

void Has(const string & key, const keyed_bag& kb) {
    cout << "Has "<<key<<": " << kb.has_key(key) << endl;
}

void Count(const int val, const keyed_bag& kb) {
    cout << "Number of "<< val <<"'s in the bag: " << kb.count(val) << endl;
}

void bSize(const keyed_bag& kb) {
    cout << "Bag size: " << kb.size() << endl;
}

int main(int argc, char const *argv[]) {
    keyed_bag kb1, kb2;

    Insert(10,"ten",kb1);
    Insert(5,"five",kb1);
    Insert(2,"two",kb1);
    Get("two", kb1);
    Get("ten", kb1);
    Get("five", kb1);
    Has("nine", kb1);
    Has("two", kb1);
    bSize(kb1);
    Erase("two", kb1);
    bSize(kb1);
    Has("four", kb1);
    Has("two", kb1);
    Insert(-3, "neg_three", kb1);
    bSize(kb1);
    Has("neg_three", kb1);
    Get("neg_three", kb1);
    Count(8, kb1);
    Count(2, kb1);
    Insert(1, "ONE", kb1);
    Count(5, kb1);
    Insert(8,"eight",kb1);
    Insert(9,"nine",kb1);
    Insert(11,"eleven",kb1);
    bSize(kb1);
    Erase("nine",kb1);
    bSize(kb1);
    Erase("ONE",kb1);
    bSize(kb1);

    // Do some stuff with bag 2.
    Insert(1,"1",kb2);
    Insert(2,"2",kb2);
    Insert(3,"3",kb2);
    Insert(4,"4",kb2);
    Insert(5,"5",kb2);

    // Testing add.
    keyed_bag kb3;
    kb3 = kb1+kb2;
    bSize(kb3);
    Has("5",kb3);
    Has("one",kb3);
    Has("ham",kb3);
    Count(4,kb3);
    Count(11,kb3);
    Count(-5,kb3);
    Get("5",kb3);
    cout << "Erasing all of kb2." << endl;
    kb2.erase();
    bSize(kb2);
    Insert(19,"I'm feelin'", kb2);
    Get("I'm feelin'", kb2);

    return 0;
}