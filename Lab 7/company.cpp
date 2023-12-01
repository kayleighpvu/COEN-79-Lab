// FILE: company.cpp
// CLASS implemented: company (see company.h for documentation)
//Lab 7 - 05/18/2023
//Coded by Kayleigh Vu
//Partner: Monica Sommer

#include <cassert>
#include "company.h"

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

namespace coen79_lab7
{
    company::company() {
        this->company_name = "";
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    company::company(const std::string& company_name) {
        assert(company_name.length() > 0);

        // COMPLETE THE IMPLEMENTATION...
        this->company_name = company_name;
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    company::company(const company &src) {
        Debug("Company copy constructor..." << std::endl);

        // COMPLETE THE IMPLEMENTATION...
        *this = src;
    }

    
    company& company::operator= (const company &src) {
        Debug("Company assignemnt operator..." << std::endl);
        // COMPLETE THE IMPLEMENTATION...
        if(this == &src)    //Checking if this is a self assignment
            return *this; 
        
        this->company_name = src.company_name;
        list_copy(src.head_ptr, this->head_ptr, this->tail_ptr);
        return *this;
    }
    
    
    company::~company() {
        list_clear(head_ptr);
    }
    
    
    std::string company::get_name() const {
        return company_name;
    }
    
    const node *company::get_head() const {
        return head_ptr;
    }
    
    const node *company::get_tail() const {
        return tail_ptr;
    }
    
    node* company::get_head() {
        return head_ptr;
    }
    
    node* company::get_tail() {
        return tail_ptr;
    }
    
    void company::print_items() {
        list_print(head_ptr);
    }
    
    
    bool company::insert(const std::string& product_name, const float& price) {
        
        assert(product_name.length() > 0);

        if (list_contains_item(head_ptr, product_name)) {
            return false;
        }
        
        if (head_ptr == NULL) {
            // COMPLETE THE IMPLEMENTATION...
            list_init(this->head_ptr, this->tail_ptr, product_name, price);
        }
        else {
            // COMPLETE THE IMPLEMENTATION...
            list_tail_insert(this->tail_ptr, product_name, price);
        }
        
        return true;
    }

    
    bool company::erase(const std::string& product_name) {
        assert(product_name.length() > 0);

        // COMPLETE THE IMPLEMENTATION...
        node* cursor;
        node* precursor = head_ptr;

        //while the node precursor is pointing name is not the target name and the node is NULL 
        while(precursor->getLink()->getName() != product_name && precursor->getLink() == NULL) 
        {
            precursor = precursor->getLink();   //iterate to next node
        }
        if (precursor->getLink() == NULL) {      //if reached the end of the sequence
            return false;
        }
        cursor = precursor->getLink();
        precursor->setLink(cursor->getLink());
        delete cursor;
        return true;
    }
    
    
}
