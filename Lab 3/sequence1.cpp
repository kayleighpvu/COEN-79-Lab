//
// FILE: sequence1.cpp
//  Sequence Class
//
//  COEN 79
//  
//
//
// INVARIANT for the sequence ADT (i.e. verbalization of rules governing
//   private member function behavior):
//   1. The number of items in the sequence is in the member variable used
//      (i.e. used = 0 means the sequence is empty).
//   2. For an empty sequence, we do not care what is stored in any of the
//      array data.  For a non-empty sequence, the items in the sequence are
//      stored in strictly maintained order in data[0] through
//      data[used].  We don't care what's in the rest of data (so don't
//      need to initialize data in the constructor).
//   3. To maintain strict order, current_index is used to keep track
//      of current location in data; when current_index is used-1,
//      we're at the last place in the array.  Also whenever current_index
//      is greater than or equal to used, there is no current item.
//   4. capacity keeps track of the current capacity of the array pointed
//      to by data; capacity starts out with the value initial_capacity
//      and is changed by resize as needed (whenever used is greater than
//      or equal to capacity).
//


#include "sequence1.h"
#include <cassert>
#include <cmath>
#include <iostream>

using namespace std;
using namespace coen79_lab3;

typedef double value_type;
typedef std::size_t size_type;
static const size_type CAPACITY = 50;

namespace coen79_lab3 {
	
	sequence::sequence() {
		//TO DO
		//initialize member variables here
		used = 0;
		current_index = 0;
	}

    
	void sequence::start() {
		//TO DO
		//set the current index pointing to the first item
		current_index = 0;	//set pointer to first index of sequence
	}

    
    void sequence::end() {
        //TO DO
        //set the current index pointing to the last item
        //don't forget to check if the sequence is empty
		assert(used > 0);
		for (int i = CAPACITY - 1; i >= 0; i--){	//start from the back of the capacity of the sequence
			current_index = i;						//set each index to current_index until found the index with the item
			if (is_item() == true){
				break;
			}
		}
		//setting current index pointing to the last item not the last part of the sequence
    }

	void sequence::last() {
		current_index = CAPACITY-1;		//set current_index pointer to last index in sequence
	}
    
    sequence::value_type sequence::current() const {
        //TO DO
    	//return the current index value
    	//don't forget to check if the current index is valid or not
		assert(is_item() == true);
		return data[current_index];
	};
    
    
    void sequence::advance() {
        //TO DO
        //set the current index pointing to the next item
        //check: 1.if reach the end of the sequence; 2.if reach the capacity of the 'bag'
		//assert (current_index < used - 1);  //checking if end of sequence is reached
		//assert (used != CAPACITY);	//checking if number of values in sequence has reached capacity of the bag
		assert(is_item() == true);
		if (current_index != CAPACITY - 1)  //check if haven't reached the end of sequence
			current_index++;				//point to the next index of sequence
	}

	void sequence::retreat() {
		if (current_index != 0)		
			current_index--;		//point to the previous index of sequence
	}


    bool sequence::is_item() const {
        //TO DO
        //does the current index point to an item or not
		if (current_index < used)	
			return true;
		else
			return false;
	}

    
	void sequence::insert(const value_type& entry) {
		//TO DO
		//check capacity first
		//if the current index pointing to no item, then insert the entry at the front of the sequence
		//otherwise, shifting other items over, and insert the new entry at the current index
		//don't forget to increment the 'used' variable
		assert (used < CAPACITY);
		if (is_item() == true){
			for (int i = used; i > current_index; i--){		//move all current elements in sequence to the right to make room at the index item is found at
				data[i] = data[i-1];
			}
			data[current_index] = entry;	//once index is found, put entry in index
			used++;		//incrementing used (number of elements in sequence) because of insertion
		}
		else{	
			data[0] = entry;
			used++;
		}
	}

    void sequence::attach(const value_type& entry) {
    	//TO DO
    	//check capacity first
    	//if the current index pointing to no item, then insert the entry at the end of the sequence
		//otherwise, shifting other items over, and attach the new entry behind the current index (current_index+1)
		//don't forget to increment the 'used' variable
		assert(size() < CAPACITY);

		if (used > 0) {		//if the sequence is not empty
            for(int i = used - 1; i > current_index; --i){		//similar to insertion
                data[i+1] = data[i];	//shifting items to the right
            }
            data[current_index + 1] = entry;	//attaching new entry behind the current index
            current_index++;	//pointing the current_index to the new entry
        } 
		else{	//else current_index = 0 and put entry in the first index of seq
            data[current_index] = entry;
        }
        used++;		//increment used because of adding new entry to seq
    }

    void sequence::remove_current() {
    	//TO DO
    	//check if the current index pointing to an item or not
    	//remove the current entry and shifting other items over
    	//don't forget to decrement the 'used variable'
		assert(is_item() == true);

        for (int i = current_index; i < used; i++){		//if item is found in seq and current_index is pointing at item
            data[i] = data[i+1];	//shifting all items to the left after removing the item current_index is pointing at
        }
        used--;		//decrement used
    }

	void sequence::insert_front(const value_type& entry) {
		//TO DO
		//check capacity first
		//move the current index to the front and then insert
		assert(used < CAPACITY);	//checking if size of elements is less than the CAPACITY
		for (int i = used; i > 0; i--) {	//moving all current items to the right to make room at the beginning 
                data[i] = data[i-1];
        }
        data[0] = entry;	//adding new entry to the first index
        used++;	//increment used
        current_index = 0;	//setting current_index to the first index (where new entry was just added into)
	}


	void sequence::attach_back(const value_type& entry) {
		//TO DO
		//check capacity first
		//move the current index to the end and then attach
		assert(used < CAPACITY);
        data[used] = entry;		//last item in sequence is at position used-1 so adding entry to the index after that
		current_index = used;	//setting current_index to the new entry
		used++;
	}

	void sequence::remove_front() {
		//TO DO
		//don't forget to check if there is an item or not
		// Move to front
        current_index = 0;	//initially set current_index to first index
		remove_current(); 	//call function because it will remove wherever the current_index is pointing at --in this case the first index
	}

	sequence::size_type sequence::size() const {
		//TO DO
		//return the number of entry
		return used;
	}

    sequence::value_type sequence::operator[](int index) const {
    	//TO DO
    	//return the value of the specific entry
    	//don't forget to check if the index is valid of not (whether has an item there)
		assert(index < used);
        return data[index];	//return the item in the sequence where index is pointed at 
	}

	sequence operator +(const sequence& lhs, const sequence& rhs) {
		//TO DO
		//combine 2 sequences to 1 new sequence
		//don't forget to check the total capacity
		//returns the new sequence object
		sequence new_seq(lhs);	//creating new sequence to hold addition
		sequence right_seq(rhs);
		right_seq.start();	//setting index of its sequence location to 0
		
        for (int i = 0; i < right_seq.size(); i++){		//iterate through every item of right sequence
            new_seq.attach_back(right_seq.current());	//adding it to the new sequence
			right_seq.advance();	//setting current_index to the next index
        }
        return new_seq;		//return new sequence
	}

	void operator +=(sequence& lhs, sequence& rhs) {
		//TO DO
		//attach 1 sequence to another
		//don't forget to check the total capacity
		//does not reurn a new sequence object, operator updates the object that invoked the function
		assert((lhs.size() + rhs.size()) <=  sequence::CAPACITY);	//check if the two sizes combined will still be less than the Capacity (+=)

        for(int i = 0; i < rhs.size(); i++){	
            lhs.attach_back(rhs[i]);	//adding rhs sequence to the lhs 
        }	//doesnt need a return because just combining both sequences
	}

	// Homework Question Functions
	double sequence::mean() const
	{
		//TO DO
		//calculate the mean of the sequence
		double total = 0.0;

        for (int i = 0; i < used; i++){ //summation of all items 
                total += data[i];
		}
        return total/used;		//return calculation
	}

	double sequence::standardDeviation() const
	{
		//TO DO
		//calculate the standard deviation of the sequence
		double mean = this->mean();	//calling the mean function
		double total = 0.0;

        for (int i = 0; i < used; i++){
        	total += pow(data[i] - mean, 2);	//the calculation of standard deviation
        }
        return sqrt(total/used);
	}

	sequence::value_type summation(const sequence &s)
	{
		//TO DO
		//calculate the sum of the sequence
		sequence seq(s);
		seq.start();	//calling start to start from beginning
		int total = 0;

        for (int i = 0; i < seq.size(); i++){	//get every index/value in the sequence
            total += seq.current();	//summation
			seq.advance();	//set current_index location to the next item in sequence
        }
        return total;
	}
}