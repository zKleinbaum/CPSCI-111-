/************************************************************************
    File: list.cc
    Author: Zach Kleinbaum
    Date: 10/23/16
    Assignment:  Lab 4 (list)

    Implementation of a list data structure

************************************************************************/
#include "list.h"

// List node constructors provided by Prof. Campbell

list_node::list_node() : prev(NULL), next(NULL) {}

list_node::list_node(list_node *p, list_node *n) : prev(p), next(n) {}

list_node::list_node(list_node *p, const list_element & d, list_node * n):
  prev(p), data(d), next(n) {}

// List constructors/destructor/assignment also provided.
// No need to change these.

list::list()
{
  _init();
}

list::~list()
{
  _destroy();
}

list::list(const list & orig)
{
  _copy(orig);
}

list & list::operator=(const list & rhs)
{
  if (this != &rhs) {
    _destroy();
    _copy(rhs);
  }
  return *this;
}


void list::_init()
{
  // Initialize an empty lidst
  _size = 0;
  _front = new list_node(NULL, new list_node(_front, NULL));
  _rear = _front -> next;
  _current = _rear;
  _current_index = 0;

  // Set front and rear to point to each other.
  _front -> next = _rear;
  _rear -> prev = _front;
}


void list::_copy(const list & orig)
{
  // This will initialize a copy of a list
  _init();
  _size = orig._size;

  // Make a node* pointing to the rear of the original list
  list_node *origCurr;
  origCurr = orig._rear;

  // Add nodes to the new list with contents that match the original
  while(origCurr -> prev!= NULL)
  {
    list_node *baby = new list_node(_front, origCurr -> data, _current);
    _current -> prev -> next = baby;
    _current -> prev = baby;
    origCurr = origCurr -> prev;
    _current = _current -> prev;
  }
}


void list::_destroy()
{
  // destructor.
  _current = _rear;

  // Delete all of the nodes in the list
  while(_current -> prev != NULL)
  {
    list_node *dead = _current;
    _current = _current -> prev;
    _current -> next = NULL;
    delete dead;
  }
  delete _current;
}


void list::add(const list_element & item, int index)
{
  // This method will add a list_node to the list.

  _set_current_index(_compute_index(index));

  // Create the new node to be added.  Set its pointers to current and the
  // node before current.
  list_node* baby = new list_node(_current -> prev, item, _current);
  _current -> prev -> next = baby;
  _current -> prev = baby;

  // Set current equal to the freshly added node.
  _current = baby;

  // Update the size of the list.
  _size ++;
}


void list::remove_at(int index)
{
  // Remove the element at a given index.

   _set_current_index(_compute_index(index));

  // Establish a pointer to the element that is to be removed.
  list_node *dead = _current;
  _current -> prev -> next = _current -> next;
  _current -> next -> prev = _current -> prev;
  _current = _current -> next;
  delete dead;

  // Change size
  _size -= 1;
}


void list::remove(const list_element & item)
{
  // Remove the first occurence of item in the list

  // Ensure that the item is in the list.
  if (find(item) != _size)
  {
    remove_at(find(item));
  }
}


size_t list::find(const list_element & item) const
{
  // Find the lowest index where an element occurs

  size_t indexCounter = 0;
  _set_current_index(0);

  // Search the list for the element. If it does not exist return size
  while(_current -> next != NULL)
  {
    if (_current -> data == item)
      return  indexCounter;
    else
      indexCounter ++;
      _set_current_index(indexCounter);
  }

  return _size;
}


list_element list::get(int index) const
{
  // Set the current index to the desired location and return its data
  _set_current_index(_compute_index(index));
  return _current -> data;
}


size_t list::size() const
{
  // Return the number of items in a list.
  return _size;
}


void list::output(std::ostream & ostr) const
{
  // Print the items of the list.
  ostr << '<';
  for (size_t i = 0; i < _size; i++)
  {
    if (i == 0)
      ostr << get(i);
    else
      ostr << ", " << get(i);
  }
  ostr << '>';
}


size_t list::_compute_index(int index) const
{
  // compute the proper index if negative.
  if (index >= 0)
  {
    size_t newIndex = index;
    return newIndex;
  }
  else
  {
    size_t newIndex = index + _size;
    return newIndex;
  }
}


void list::_set_current_index(size_t index) const
{
  // Set index equal to the desired number.90

  // Find the distance from front, rear, current, and the desired index.
  int frontDistance = index;
  int rearDistance = _size - index;
  int currentDistance = _current_index - index;

  //adjust currentDistance for negatives.
  if (currentDistance < 0)
  {
    currentDistance = currentDistance * -1;
  }

  // Compare the distances and adhust current to the closest location.
  if (frontDistance < rearDistance and frontDistance < currentDistance){
    _current = _front -> next;
    _current_index = 0;
  }

  else if (rearDistance < frontDistance and rearDistance < currentDistance){
     _current = _rear;
     _current_index = _size;
  }

  // Change current to desired starting location.
  if (index >= _current_index)
  {
    while(_current_index != index)
      {
        _current = _current -> next;
        _current_index ++;
      }
  }
  else
  {
    while(_current_index != index)
    {
      _current = _current -> prev;
      _current_index --;
    }
  }
}
