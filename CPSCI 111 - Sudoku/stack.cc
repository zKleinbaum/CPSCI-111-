/************************************************************************
    File: stack.cc
    Author: Zach Kleinbaum
    Date: 9/19/16
    Assignment:  Project 3: Sudoku

    Implementation of a linked list stack class.

************************************************************************/
    #include <iostream>
    #include "stack.h"
    #include <cassert>

    using namespace std;

    //CITATION: Provided by Professor Campbell in class.

    /*** Constructor ***/
    stack::stack()
    {
    	_create();
    }


    stack::stack(const stack & orig)
    // Copy constructor.
    {
        _copy(orig);
    }


    stack::~stack()
    // Destructor.
    {
    	_destroy();
    }


    stack& stack::operator=(const stack & rhs)
    // Assignment operator.
    {
        if (this != &rhs)
        {
            _destroy();
            _copy(rhs);
        }
        return *this;
    }


    /*** Member Functions ***/

    void stack::push(const stack_element & item)
    {
        // Add a new item to the stack.
    	_top = new node(item, _top);
    }


    void stack::pop()
    {
    	// Remove an item.
        node* dead = _top;
    	_top = _top -> next;
    	delete dead;
    }


    bool stack::empty() const
    {
    	// Determine if the stack has elements.
        return _top == NULL;
    }


    stack_element stack::top() const
    {
    	// Assuming that the stack is not empty, return the top element.
        assert(!empty());
    	return _top -> data;
    }

    void stack::_create()
    {
        // Create a new stack by setting the top to null.
        _top = NULL;
    }


    void stack::_copy(const stack & orig)
    {
        // Copy a stack.
        node* last = NULL;
        _create();
        for (node* curr = orig._top; curr != NULL; curr = curr -> next)
        {
            node* next = new node(curr -> data, NULL);
            if (last == NULL)
            {
                _top = next;
            }
            else
            {
                last -> next = next;
            }
            last = next;
        }
    }


    void stack::_destroy()
    {
    	// Delete all of the stack's elements.
        while(!empty())
    		pop();
    }
