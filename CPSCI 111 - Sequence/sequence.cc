/************************************************************************
    File: sequence.cc
    Author: Zach Kleinbaum
    Date: 9/12/16
    Assignment:  Lab 1 (sequence)

    Implementation of a simple array-based sequence class.

************************************************************************/
#include <iostream>
#include "sequence.h"

using namespace std;

/*** Constructor ***/
sequence::sequence()
{
  // Initializes this sequence with 0 elements.
  _size = 0;
}

/*** const member functions ***/


size_t sequence::size() const
{
  // Return the number of elements in this sequence.
  return _size;
}


bool sequence::empty() const
{
  // Return true if this sequence has no elements, false otherwise.
  if (_size == 0)
  {
    return true;
  }
  return false;
}


bool sequence::full() const
{
  // Return true if this sequence has _capacity elements, false otherwise.
  if (_size == _capacity)
  {
    return true;
  }
  return false;
}


void sequence::print() const
{
  // Produce output with cout: a single open square bracket, the elements
  // of the sequence, separated by commas and spaces, followed by a single
  // close square bracket.  No newline.
  // Examples of output:
  //  []
  //  [6]
  //  [9, -1, 4]

  // Use cout to print the elements of each position.
  // Use the for loop to cycle through all of the list's elements.
  cout << "[";
    for (size_t i = 0; i < _size; i++)
    {
      if (i == 0)
        cout << _data[i];
      else
        cout << ", " << _data[i];
    }
  cout << "]";
}


int sequence::get(size_t position) const
{
  // Precondition:  position < size()
  // Return the element at the given position.
  return _data[position];
}


size_t sequence::getLongestRun() const
{
  // Determine the length of the longest run of two or more identical adjacent
  // elements of this sequence.  Return the smallest starting position of a
  // run with this length.  If no such run occurs, return size().
  // (This method may use auxiliary stand-alone functions, but, again, you
  // cannot change this  file.  This means that you cannot define auxiliary
  // methods.)

  // track the length of the longest run of intergers using a counter
  int lengthCount = 0;

  // use a sample counter for comparison.
  int sampleCount = 0;

  // track the starting position using a variable
  int startPosition = -1;

  // Use a for loop to determine the length of a run of identical elements.
  // Use the .get() method to determine if two elements are equal.
  // If they are equal add one to the count within the for loop and if that
  // is greater than lengthCount we will reset both length count and
  // start position.
  for (size_t i = 0; i < _size; i++)
  {
    if (get(i) == get(i+1))
    {
      // Add one to the sample count if there are consecutive elements.
      ++ sampleCount;

      // If the sample count is longer than the longest run, replace the
      // lengthCount and set the startPosition to the position of the
      // longer run.
      if (sampleCount > lengthCount)
      {
        lengthCount = sampleCount;
        startPosition = i - lengthCount + 1;
      }
    }
    else
    {
      // Reset the sample count if the elements are not consecutive.
      sampleCount = 0;
    }
  }
  // If startPositioin is unchanged there is no consecutive run.
  if (startPosition == -1)
    {
      return size();
    }
  // Return the starting position of the longest run.
  return startPosition;
}


/*** non-const member functions ***/


void sequence::add(int item)
{
  // Preconditions:
  //   The sequence has N elements.
  //   N != _capacity;
  //   Without loss of generality, the sequence contains elements
  //     [V0, V1, V2, ...VN-1]
  // Adds item to the end of the sequence.
  // Postconditions:
  //   The sequence contains elements
  //     [V0, V1, ..., VN-1, item];
  //   size() == N+1.

  // Store the number of elements in the sequence in a variable.
  int position = size();

  // Set the position in the sequence equal to the current variable.
  _data[position] = item;

  // Update size.
  _size += 1;
}


void sequence::add(int item, size_t position)
{
  // Preconditions:
  //   The sequence has N elements.
  //   N != capacity;
  //   Without loss of generality, the sequence contains elements
  //     [V0, V1, V2, ..., Vposition,... VN-1];
  //   position <= size()
  // Inserts item at the given position.  All elements with indices at position
  // or greater are shifted to the right.
  // Postconditions:
  //   The sequence contains elements
  //     [V0, V1, V2, ..., item, Vposition,..., VN-1];
  //   size() == N+1

  // Starting at the last existing element shift each element to the right.
  for(size_t i = _size; i > position; i--)
    {
      _data[i] = _data[i - 1];
    }

  _data[position] = item;

  // Update the size of the sequence.
  _size += 1;
}


void sequence::remove(size_t position)
{
  // Preconditions:
  //   The sequence has N elements
  //   Without loss of generality, the sequence contains elements
  //     [V0, V1,  ..., Vposition-1, Vposition, Vposition+1, ... VN-1];
  //   0 <= position and position < N
  // The item at the given position is discarded.  All elements with greater
  // indices are shifted to the left.
  // Postconditions:
  //   The sequence contains elements
  //     [V0, V1, ..., Vposition-1, Vposition+1, ..., VN-1]
  //   size() == N-1.

  //  Starting at the position, change the value of the element to the value of
  //  the element to its right
  for(size_t i = position; i < _size - 1; i++)
    {
      _data[i] = _data[i + 1];
    }

  // Update the size of the sequence.
  _size  -= 1;
}


void sequence::replace(int newitem, size_t position)
{
  // Preconditions:
  //   The sequence has N elements.
  //   0 <= position < N
  //   Without loss of generality, the sequence contains elements
  //     [V0, V1, V2, ..., Vposition,... VN-1];
  // Replaces the item at the given position with the given new item.
  // Postcondition:
  //   The sequence contains elements
  //     [V0, V1, V2, ..., newitem,... VN-1];
  //   size() == N  (unchanged)

  // Assign the position in the sequence the value of newitem.
  _data[position] = newitem;
}


void sequence::clear()
{
  // Remove all elements from the sequence.
  // Postcondition:
  //   size() == 0

  // Check the edge case where the sequence only has one element.
  // If true, change the size to 0.
  if (_size == 1)
  {
    _size = 0;
  }

  // For larger lists, remove each element individually and set the size equal
  // to 0.
  for (size_t i = _size; i > 0; i--)
  {
    remove(i);
  }

  _size = 0;
}
