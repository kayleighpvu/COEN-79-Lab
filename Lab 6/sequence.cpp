//FILE: sequence.cpp
//CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
//
//
//  COEN 79
//  --- Farokh Eskafi, COEN, SCU ---
//
//
//INVARIANT for the sequence class
//  1. The number of items in the sequence is stored in the member variable "many_nodes"
//
//  2. For an empty sequence, we do not care what is stored in any of data and head_ptr
//      and tail_ptr point to NULL; for a non-empty sequence, the items stored in the
//      sequence can be accessed using head_ptr and tail_ptr and we don't care what is
//      stored in the rest of the data.
//
//  3. If there is a current item, then it lies in *cursor; if there is no
//     current item, then cursor* equals NULL.
//
//  4. If there is a previous item, then it lies in precursor*.  If there is no previous
//       item, then precursor equals NULL.

//CODE WRITTEN BY KAYLEIGH VU
//CODE TESTED BY MONICA SOMMER
//LAB 6 - Sequence

#include <iostream>
#include <algorithm> //provides copy function
#include <cassert> //for assert function
#include "sequence.h" //header file for class
#include "node.h" // provides node class

using namespace std; //For copy function

namespace coen79_lab6
{
    // Default private member variable initialization function.
    void sequence::init()
    {
        //Initializing pointers to NULL
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        //Initializiing many_nodes (or our counter) to 0
        many_nodes = 0;
    }

    //CONSTRUCTOR IMPLEMENTATION for default constructor
    //Postcondition: Initialize sequence as empty
    sequence :: sequence ()
    {
        init();
    }

    //Copy Constructor
    //Postcondition: Copy constructor's empty sequence and initialize given the input data
    sequence :: sequence(const sequence& source)
    {
        init();
        *this = source;
    }

    //Destructor
    //Precondition: Check if the sequence is already empty
    //Postcondition: Delete all elements in the sequence
    sequence::~sequence( )
    {   
        list_clear(head_ptr);   //linked list toolkit
        many_nodes = 0;
    }

    // MODIFICATION MEMBER FUNCTIONS
    //Postcondition: If sequence is empty, there is not current item. But if is not empty, 
    //the precursor and cursor are adjusted so the first item is the current item in sequence
    void sequence::start( )
    {
        cursor = head_ptr;
        precursor = nullptr;                                                      
    }

    //Postcondition: Precursor and cursor are adjusted so the last item in sequence becomes the current item.
    //No current item if sequence is empty
    void sequence::end()
    {
        if (many_nodes == 0)    //if sequence is empty (0 nodes in list)
        {
            cursor = nullptr;
            precursor = nullptr;   
        }
        else if (head_ptr == tail_ptr)   //if there is one node in the sequence so both pointers point to same node
        {
            cursor = head_ptr;
            precursor = nullptr;
        }
        else    //if there are more than 1 node in the sequence, set the cursor to the end and the precursor to node right before the cursor
        {
            cursor = tail_ptr;
            precursor = list_locate(head_ptr, many_nodes - 1);  //linked list toolkit given the head pointer and position
        } 
    }

    //Precondition: is_item returns true.
    //Postcondition: If the current item was already the last item in the
    //sequence, then there is no longer any current item. Otherwise, the new
    //current item is the item immediately after the original current item.
    void sequence::advance( )
    {
        assert (is_item());
        precursor = cursor;
        cursor = cursor->link();
    }

    //Postcondition: A new copy of entry has been inserted in the sequence
    //before the current item. If there was no current item, then the new entry
    //has been inserted at the front of the sequence. In either case, the newly
    //inserted item is now the current item of the sequence.
    void sequence::insert(const value_type& entry)
    {
        if (!is_item() || precursor == nullptr)     //if there are no nodes in sequence 
        {
            list_head_insert(head_ptr, entry);      //toolkit to insert in front
            if(tail_ptr == nullptr) tail_ptr = head_ptr;    //set the tail_ptr to new node if not already pointing to it
            cursor = head_ptr;
            precursor = nullptr;
            many_nodes++;
        }
        else
        {
            list_insert(precursor, entry);      //toolkit to insert node anywhere but the front of sequence
            cursor = precursor->link();   //set cursor ahead of the precursor
            many_nodes++;                   
            if (cursor->link() == nullptr)  tail_ptr = cursor; //if the cursor is pointing to the end of sequence, set tail pointer to it
        }
    }

    //Postcondition: A new copy of entry has been inserted in the sequence after
    //the current item. If there was no current item, then the new entry has
    //been attached to the end of the sequence. In either case, the newly
    //inserted item is now the current item of the sequence.
    void sequence::attach(const value_type& entry)
    {
        if (head_ptr == nullptr)    //if sequence is empty
        {
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = nullptr;
            tail_ptr = head_ptr;
        }
        else if (cursor == nullptr)      //attaching at the end 
        {      
            list_insert(tail_ptr, entry);
            precursor = tail_ptr;
            tail_ptr = tail_ptr->link();
            cursor = tail_ptr;
        }
        else
        {
            list_insert(cursor, entry);     //attaching after the cursor
            precursor = cursor;
            if (cursor == tail_ptr)
            {
                tail_ptr = tail_ptr->link();
            }
            cursor = cursor->link();
        }
        many_nodes++;
    }


    void sequence::operator =(const sequence& source)
    {
        if (this == &source)    //cannot do anything if it's equal to itself
        {
            return;
        }
        list_clear(head_ptr);   //toolkit: destroy sequence to make a new copy sequence
        init();                 //new sequence, setting everything to NULL or 0 (default values)
        many_nodes = source.many_nodes;
        list_copy(source.head_ptr, head_ptr, tail_ptr);     //toolkit: copy data from source to new sequence

        if (source.cursor == nullptr)   //adjusting cursor
        {
            cursor = nullptr;
        }
        else
        {
            cursor = list_search(head_ptr, source.cursor->data());
        }

        if (source.precursor == nullptr)    //adjusting precursor        
        {
            precursor = nullptr;
        }
        else
        {
            precursor = list_search(head_ptr, source.precursor->data());
        }
    }

    //Precondition: is_item returns true.
    //Postcondition: The current item has been removed from the sequence, and
    //the item after this (if there is one) is now the new current item.
	void sequence::remove_current( )
    {
        assert(is_item());
        if (head_ptr == cursor && head_ptr == tail_ptr)     //if only 1 node in sequence
        {
            list_head_remove(head_ptr);
            init();     //set everything back to default 0 or NULL
        }        
        else if (head_ptr == cursor && head_ptr != tail_ptr)    //if head pointer points to same node as cursor but not to tail
        {                                                       
            list_head_remove(head_ptr);
            cursor = head_ptr;
            precursor = nullptr;
            many_nodes--;
        }
        else if (cursor == tail_ptr)    //if you want to remove the node after the precursor but the cursor is pointing to end node
        {
            list_remove(precursor);
            tail_ptr = precursor;        
            cursor = nullptr;
            many_nodes--;
        }
        else                            //if you want to remove the node after the precursor but the cursor is not at the end node
        {
            list_remove(precursor);
            cursor = precursor->link();
            many_nodes--;
        }
    }

    // CONSTANT MEMBER FUNCTIONS
    //Postcondition: Return the number of items in the sequence
    sequence::size_type sequence::size( ) const
    {
        return many_nodes;
    }

    //Postcondition: A true return value indicates that there is a valid
    //"current" item that may be retrieved by activating the current
    //member function (listed below). A false return value indicates that
    //there is no valid current item.
    bool sequence::is_item( ) const
    {   
        return (cursor != nullptr);
    }

    //Precondition: is_item( ) returns true.
    //Postcondition: The item returned is the current item in the sequence.
    sequence::value_type sequence::current( ) const
    {
        assert (is_item());
        return cursor->data();
    }
    
}