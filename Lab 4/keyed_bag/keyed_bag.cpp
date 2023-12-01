//testing file for keyed_bag
//Kayleigh Vu & Monica Sommer
//COEN 79 Lab 4 Eskafi 

#include <cassert>
#include <cmath>
#include "keyed_bag.h"

using namespace std;

namespace coen79_lab4{

    // Constructor
    keyed_bag::keyed_bag(){
        // Postcondition: Bag is empty and initialized with default
        used = 0;
    }

    void keyed_bag::erase(){
        // Postcondition: Set keyed_bag to default of no values, items, and keys
        used = 0;
    }

    bool keyed_bag::erase(const key_type &key){
        // Postcondition: If key in the keyed_bag, remove key and return 1. Else, don't do anything and return 0
        assert(used > 0);   
        for (int i = 0; i < used; i++){     //search through all elements of bag
            if (keys[i] == key){        //if key is found in bag   
                for (int j = i; j < used - 1; j++){     //shift all other elements to remove the element where key is found
                    keys[j] = keys[j + 1];
                    data[j] = data[j + 1];
                }
                used--;
                return true;
            }
        }
        return false;
    }

    void keyed_bag::insert(const value_type &entry, const key_type &key){
        // Precondition: # of elements in bag is less than CAPACITY max and the bag does not contain key yet
        // Postcondition: A key and its values is added to bag at the end of all other elements and increment # of elements
        assert((size() < CAPACITY) && (has_key(key) == false));
        keys[used] = key;
        data[used] = entry;
        used++;
    }

    void keyed_bag::operator +=(const keyed_bag &addend){
        // Precondition:  Both bags' sizes add up to less or equal to than capacity size
        // Postcondition: Add all data from addend to keyed_bag.
        assert(size() + addend.size() <= CAPACITY);  
        for (int i = 0; i < addend.used; i++){     //iterate through all elements of addend bag
            if (!has_key(addend.keys[i])){
                keys[used] = addend.keys[i];
                data[used] = addend.data[i];
                used++;
            }
        }
    }

    // CONSTANT MEMBER FUNCTIONS
    bool keyed_bag::has_key(const key_type &key) const{
        // Postcondition: Return whether or not the key is in bag's list of keys.
        for (int i = 0; i < used; i++){    //iterate through elements in bag to look for key
            if (keys[i] == key){       //if key is found, return true (found). else, return false (not found)
                return true;
            }
        }
        return false;
    }

    keyed_bag::value_type keyed_bag::get(const key_type &key) const{
        // Precondition: key is found in list of keys
        // Postcondtion: get the data of element corresponding to the key 
        assert(has_key(key));
        for (int i = 0; i < used; i++){
            if (keys[i] == key){
                return data[i];
            }
        }
        return 0;
    }

    keyed_bag::size_type keyed_bag::size() const{
        // Postcondition: Return total number of items in bag.
        return used;
    }

    keyed_bag::size_type keyed_bag::count(const value_type &target) const{
        // Postcondition: Return number of times target value is found in the keyed_bag.
        size_type count = 0;
        for (int i = 0; i < used; i++){
            if (data[i] == target){
                count++;
            }
        }
        return count;
    }

    bool keyed_bag::hasDuplicateKey(const keyed_bag &otherBag) const{
        // Postcondition: The return value is true if there is at least one key used by both this bag and otherBag meaning it found a duplicate
        for (int i = 0; i < otherBag.used; ++i){       //iterate through otherBag to look for key
            if (has_key(otherBag.keys[i])){        //if key was found in otherBag, return true for found. else return flase for not found
                return true;
            }
        }
        return false;
    }

    keyed_bag operator +(const keyed_bag &b1, const keyed_bag &b2){
        // Precondition:  size of both bags is less than or equal to the capacity size of keyed_bag
        // Postcondition: The temp b3 bag of keyed_bag returns both b1 and b2 together
        assert((b1.size() + b2.size()) <= keyed_bag::CAPACITY);

        keyed_bag b3;
        b3 += b1;
        b3 += b2;
        return b3;
    }
}