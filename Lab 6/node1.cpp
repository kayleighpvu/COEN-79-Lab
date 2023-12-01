// FILE: node.cpp
// by Monica Sommer
//
//  COEN 79
//  --- Farokh Eskafi, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

//CODE WRITTEN BY MONICA SOMMER
//CODE TESTED BY KAYLEIGH VU
//LAB 6 - Node

/*#include "node.h"
#include <cassert>    // Provides assert
#include <iostream>
#include <cstdlib> // Provides NULL and size_t

using namespace std;

namespace coen79_lab6 {

    //     Precondition: head_ptr is the head pointer of a linked list.
    //     Postcondition: The value returned is the number of nodes in the linked
    //     list.
    size_t list_length(const node *head_ptr)
    {
        const node *cursor;
        size_t answer;

        answer = 0;
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->link())
            ++answer;

        return answer;
    }

    //     Precondition: head_ptr is the head pointer of a linked list.
    //     Postcondition: A new node containing the given entry has been added at
    //     the head of the linked list; head_ptr now points to the head of the new,
    //     longer linked list.
    void list_head_insert(node *&head_ptr, const node::value_type &entry) {
        head_ptr = new node(entry, head_ptr);
    }

    //     Precondition: previous_ptr points to a node in a linked list.
    //     Postcondition: A new node containing the given entry has been added
    //     after the node that previous_ptr points to.
    void list_insert(node *previous_ptr, const node::value_type &entry) {
        node *insert_ptr;

        insert_ptr = new node(entry, previous_ptr->link());
        previous_ptr->set_link(insert_ptr);
    }

    //     Precondition: head_ptr is the head pointer of a linked list.
    //     Postcondition: The pointer returned points to the first node containing
    //     the specified target in its data member. If there is no such node, the
    //     null pointer is returned.
    node *list_search(node *head_ptr, const node::value_type &target)
    {
        node *cursor;

        for (cursor = head_ptr; cursor != NULL; cursor = cursor->link())
            if (target == cursor->data())
                return cursor;

        return NULL;
    }

    //     Precondition: head_ptr is the head pointer of a linked list.
    //     Postcondition: The pointer returned points to the first node containing
    //     the specified target in its data member. If there is no such node, the
    //     null pointer is returned.
    const node *list_search(const node *head_ptr, const node::value_type &target)
    {
        const node *cursor;

        for (cursor = head_ptr; cursor != NULL; cursor = cursor->link())
            if (target == cursor->data())
                return cursor;

        return NULL;
    }

    //     Precondition: head_ptr is the head pointer of a linked list, and
    //     position > 0.
    //     Postcondition: The pointer returned points to the node at the specified
    //     position in the list. (The head node is position 1, the next node is
    //     position 2, and so on). If there is no such position, then the null
    //     pointer is returned.
    node *list_locate(node *head_ptr, size_t position)
    {
        node *cursor;
        size_t i;

        assert (0 < position);
        cursor = head_ptr;
        for (i = 1; (i < position) && (cursor != NULL); i++)
            cursor = cursor->link();

        return cursor;
    }

    //     Precondition: head_ptr is the head pointer of a linked list, and
    //     position > 0.
    //     Postcondition: The pointer returned points to the node at the specified
    //     position in the list. (The head node is position 1, the next node is
    //     position 2, and so on). If there is no such position, then the null
    //     pointer is returned.
    const node *list_locate(const node *head_ptr, size_t position)
    {
        const node *cursor;
        size_t i;

        assert (0 < position);
        cursor = head_ptr;
        for (i = 1; (i < position) && (cursor != NULL); i++)
            cursor = cursor->link();

        return cursor;
    }

    //     Precondition: head_ptr is the head pointer of a linked list, with at
    //     least one node.
    //     Postcondition: The head node has been removed and returned to the heap;
    //     head_ptr is now the head pointer of the new, shorter linked list.
    void list_head_remove(node *&head_ptr) {
        node *remove_ptr;

        remove_ptr = head_ptr;
        head_ptr = head_ptr->link();
        delete remove_ptr;
    }

    //     Precondition: previous_ptr points to a node in a linked list, and this
    //     is not the tail node of the list.
    //     Postcondition: The node after previous_ptr has been removed from the
    //     linked list.
    void list_remove(node *previous_ptr) {
        node *remove_ptr;

        remove_ptr = previous_ptr->link();
        previous_ptr->set_link(remove_ptr->link());
        delete remove_ptr;
    }

    //     Precondition: head_ptr is the head pointer of a linked list.
    //     Postcondition: All nodes of the list have been returned to the heap,
    //     and the head_ptr is now NULL.
    void list_clear(node *&head_ptr)
    {
        while (head_ptr != NULL)
            list_head_remove(head_ptr);
    }

    //     Precondition: source_ptrst_ is the head pointer of a linked list.
    //     Postcondition: head_ptr and tail_ptr are the head and tail pointers for
    //     a new list that contains the same items as the list pointed to by
    //     source_ptr. The original list is unaltered.
    void list_copy(const node *source_ptr, node *&head_ptr, node *&tail_ptr)
    {
        head_ptr = NULL;
        tail_ptr = NULL;

        //empty list
        if (source_ptr == NULL)
            return;

        // head for new list with data
        list_head_insert(head_ptr, source_ptr->data());
        tail_ptr = head_ptr;

        // copy the nodes to the end of tail
        source_ptr = source_ptr->link();
        while (source_ptr != NULL) {
            list_insert(tail_ptr, source_ptr->data());
            tail_ptr = tail_ptr->link();
            source_ptr = source_ptr->link();
        }
    }

    //    Precondition: start_ptr and end_ptr are pointers to nodes on the same
    //    linked list, with the start_ptr node at or before the end_ptr node
    //    Postcondition: head_ptr and tail_ptr are the head and tail pointers for a
    //    new list that contains the items from start_ptr up to but not including
    //    end_ptr.  The end_ptr may also be NULL, in which case the new list
    //    contains elements from start_ptr to the end of the list.
    void list_piece(node *start_ptr, node *end_ptr, node *&head_ptr, node *&tail_ptr) {
        node *linker = start_ptr;
        head_ptr = NULL;
        tail_ptr = NULL;
        if (end_ptr != NULL)    //precondition
        {
            while(linker != NULL)
            {
                linker = linker->link();
                if(linker == end_ptr)
                {
                    break;
                }
            }
        }
        if (linker == NULL) return;     //checking if linker pointer points to NULL
        list_head_insert(head_ptr, start_ptr->data());
        tail_ptr = head_ptr;

        while (start_ptr->link() != end_ptr)
        {
            list_insert(tail_ptr, start_ptr->link()->data());
            tail_ptr = tail_ptr->link();
            start_ptr = start_ptr->link();
        }
    }

    //     Precondition: head_ptr is the head pointer of a linked list.
    //     Postcondition: The return value is the count of the number of times
    //     target appears as the data portion of a node on the linked list.
    //     The linked list itself is unchanged.
    size_t list_occurrences(node *head_ptr, const node::value_type &target) {
        size_t count = 0;
        node *ptr = head_ptr;
        while (ptr != NULL) {
            if (ptr->data() == target) {
                count++;
            }
            ptr = ptr->link();
        }
        return count;
    }

    //     Precondition: head_ptr is the head pointer of a linked list, and
    //     position > 0 and position <= list_length(head_ptr)+1.
    //     Postcondition: A new node has been added to the linked list with entry
    //     as the data. The new node occurs at the specified position in the list.
    //     (The head node is position 1, the next node is position 2, and so on.)
    //     Any nodes that used to be after this specified position have been
    //     shifted to make room for the one new node.
    void list_insert_at(node *&head_ptr, const node::value_type &entry, size_t position) {
        if (position < 1 || position > list_length(head_ptr) + 1) return;
        
        if (position == 1) {        //inserting at front
            list_head_insert(head_ptr, entry);
            return;
        } 
        
        node *cursor = head_ptr;
        for (size_t i = 1; i < position - 1; i++) {
            cursor = cursor->link();
        }
        list_insert(cursor, entry);
    }

    //     Precondition: head_ptr is the head pointer of a linked list
    //     Postcondition: The node at the specified position has been removed from
    //     the linked list and the function has returned a copy of the data from
    //     the removed node.
    //     (The head node is position 1, the next node is position 2, and so on.)
    node::value_type list_remove_at(node *&head_ptr, size_t position) {
        assert ((position > 0) && (position <= list_length(head_ptr)));
        //prev location so we can shift
        if (position == 1) {
            //node::value_type data = head_ptr->data();
            list_head_remove(head_ptr);
            return head_ptr->data();
        } else {
            node *cursor = head_ptr;
            for (size_t i = 1; i < position - 1; i++) {
                cursor = cursor->link();
            }
            list_remove(cursor);
            node::value_type data = cursor->data();
            return data;
        }
    }

    //     Precondition: head_ptr is the head pointer of a linked list
    //     Postcondition: The value returned is the head pointer for
    //     a new list that contains copies of the items from the start position to
    //     the finish position in the list that head_ptr points to.
    //     (The head node is position 1, the next node is position 2, and so on.)
    //     The list pointed to by head_ptr is unchanged.
    node *list_copy_segment(node *head_ptr, size_t start, size_t finish) {
        if((1 > start) || (start > finish) || (finish > list_length(head_ptr)))
        {
            return NULL;
        }
        node *new_head = NULL;
        node *new_tail = NULL;
        node *begin = list_locate(head_ptr, start);     //starting node
        node *end = list_locate(head_ptr, finish + 1); //2nd cursor for end node.

        list_piece(begin, end, new_head, new_tail); //list piece: creating new list with new_head
        return new_head;
    }

    //     Precondition: head_ptr is the head pointer of a linked list, and
    //     the operator << has been defined for the value_type
    void list_print(const node *head_ptr) {
        while (head_ptr != NULL) {
            if (head_ptr->link() == NULL) {
                cout << head_ptr->data();
                break;
            } 
            cout << head_ptr->data() << ", ";
            head_ptr = head_ptr->link();
        }
        cout << endl;
    }

    void list_remove_dups(node *head_ptr) {
        node *cursor = head_ptr;
        while(cursor->link() != NULL){
            size_t dups = list_occurrences(cursor,cursor->data());
            node::value_type target = cursor->data();
            int pos = 1;
            while(dups > 1){
                pos++;
                if(cursor->link()->data() == target)
                {
                    node* remove = list_locate(head_ptr, pos - 1);
                    list_remove(remove);
                    dups--;
                    pos--;
                }
            }
        }    
    }

    node *list_detect_loop(node *head_ptr) {
        node *slow_ptr = head_ptr;
        node *fast_ptr = head_ptr;
        while (slow_ptr != NULL && fast_ptr != NULL && fast_ptr->link() != NULL) {
            slow_ptr = slow_ptr->link();
            fast_ptr = fast_ptr->link()->link();

            if (slow_ptr == fast_ptr)
            {
                slow_ptr = head_ptr;
                while (slow_ptr != fast_ptr) {
                    slow_ptr = slow_ptr->link();
                    fast_ptr = fast_ptr->link();
                }
                return slow_ptr;
            } 
        }
        return NULL;
    }
}
*/
