//node.cpp : linked list toolkit
//Lab 7 - 05/18/2023
//Coded by Kayleigh Vu
//Partner: Monica Sommer

#ifndef ITEM_CPP
#define ITEM_CPP

#include "node.h"

namespace coen79_lab7
{
    node::node(const std::string &itemName, const float &newPrice, node *nextNode) {
        name = itemName;
        price = newPrice;
        link = nextNode;
    }
    
    void node::setName(const std::string &newName) {
        name = newName;
    }
    
    void node::setPrice(const float &newPrice) {
        price = newPrice;
    }
    
    void node::setLink(node *new_next) {
        link = new_next;
    }
    
    node* node::getLink() {
        return link;
    }
    
    const node* node::getLink() const {
        return link;
    }
    
    std::string node::getName() const{
        return name;
    }
    
    float node::getPrice() const {
        return price;
    }
    
    
    void list_init(node*& head, node*& tail, const std::string& newName, const float& newPrice) {
        head = new node(newName, newPrice, NULL);
        tail = head;
    }
    
    
    void list_tail_insert(node*& tail, const std::string &newName, const float &newPrice) {

        // COMPLETE THE IMPLEMENTATION...
        if (tail == NULL) //check if list is empty
            return;
        node* temp = new node(newName, newPrice, NULL);     //add new node to insert
        tail->setLink(temp);    //establish link to new added node
        tail = temp;    //set tail ptr to node being added at the end
    }
    
    
    void list_clear(node*& head) {
        // COMPLETE THE IMPLEMENTATION...
        if (head == NULL)   //check if list is empty, if so, no need to clear anything
            return;
        while (head != NULL)    
        {                               //another toolkit function that will iterate 
            list_head_remove(head);     //through all nodes with head ptr and will delete
        }                               //each one till head doesn't point to anything
    }
    
    
    void list_copy(const node *old_head, node* &new_head, node* &new_tail) {
        new_head = NULL;
        new_tail = new_head;
        
        const node *cur = old_head;
        while (cur != NULL) {
            if (new_head == NULL) {
                new_head = new node(cur->getName(), cur->getPrice());
                new_tail = new_head;
            }
            else {
                new_tail->setLink(new node(cur->getName(), cur->getPrice()));
                new_tail = new_tail->getLink();
            }
            cur=cur->getLink();
        }
    }
    
    
    void list_head_remove(node*& head) {
        // COMPLETE THE IMPLEMENTATION...
        node *temp_ptr = head;      //temporary pointer to node that head points to
        head = head->getLink();     //set head ptr to next node
        delete temp_ptr;            //delet the node temp ptr points to
    }
    
    
    void list_print(node *head) {
        node *cur = head;
        while (cur != NULL) {
            std::cout << "- " << cur->getName() << ", where the price is $" << cur->getPrice() << std::endl;
            cur = cur->getLink();
        }
    }
    
    
    bool list_contains_item(node *head_ptr, const std::string& newName) {
        return (list_search(head_ptr, newName) != NULL);
    }
    
    
    node* list_search(node* head_ptr, const std::string& target)
    {
        node *cursor;
        
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->getLink( ))
            if (target == cursor->getName( ))
                return cursor;
        return NULL;
    }
    
    
    const node* list_search(const node* head_ptr, const std::string & target)
    {
        const node *cursor;
        
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->getLink( ))
            if (target == cursor->getName( ))
                return cursor;
        return NULL;
    }
    
}

#endif
