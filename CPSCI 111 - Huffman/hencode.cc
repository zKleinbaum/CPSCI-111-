/************************************************************************
    File: hencode.cc
    Author: Zach Kleinbaum
    Date: 11/17/16
    Assignment:  Lab 7 (Huffman)

    Implementation of huffman encoding

************************************************************************/
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <math.h>

using namespace std;

struct hnode {
  // Hnode data structure.
  // Contains left/right pointers, letter, and count.

  unsigned char letter;
  size_t count;
  hnode *left, *right;

  hnode(unsigned char letter, size_t count, hnode *left = NULL, hnode *right
        = NULL) :
    letter(letter), count(count), left(left), right(right) {}
};


size_t priority(hnode * const & n)
{
  // Returns the count on a given hnode.

  return n->count;
}

// Definition of a heap element, to be used in heap class.
typedef hnode* heap_element;

class heap {
  // Heap data structure.

private:
  heap_element _data[256];
  size_t _size;
  size_t(*priority)(const heap_element &);

  void reheap_down(size_t tree)
  {
    // Reheap down will be used when removing elements from the heap.
    // Will ensure that each element is in proper location.
    // If the priority of a child is higher than a parent they must be swaped.

    if (isLeaf(tree)) return;

    // Set child to the left child of the tree and change if the following.
    size_t child = leftchild(tree);

    if (rightchild(tree) < _size and priority(_data[rightchild(tree)]) < priority(_data[leftchild(tree)]))
      child = rightchild(tree);

    if (priority(_data[child]) < priority(_data[tree])){
      // Swap the nodes if they are not in the correct location.
      swap(child, tree);
      reheap_down(child);
    }
  }


  void reheap_up(size_t tree)
  {
    // Reheap up will be used when adding elements to the tree.
    // Will compare parents and children.
    // If the tree has lower priority than a parent it must be swapped.

    if (tree == 0) return;

    size_t par = parent(tree);

    if (priority(_data[tree]) < priority(_data[par]))
    {
      swap(tree, par);
      reheap_up(par);
    }
  }


public:
  heap(size_t (*p)(const heap_element &)): _size(0), priority(p){}
    // constructor.


  size_t leftchild(size_t k)
  {
    // Locate k's left child in the heap array.

    return (2 * k) + 1;
  }


  size_t rightchild(size_t k)
  {
    // Locate k's right child in the heap array.

    return (2 * k) + 2;
  }


  size_t parent(size_t k)
  {
    // Locate k's parent in the heap array.

    return (k - 1) / 2;
  }


  void swap(size_t x, size_t y)
  {
  // Swap two values

    heap_element z = _data[x];
    _data[x] = _data[y];
    _data[y] = z;
  }


  bool isLeaf(size_t k)
  {
    // Determine if k is a leaf.
    // left child will always be lower than right child. Right child cannot
    // exist without left child.

    if (leftchild(k) > _size)
      return true;
    return false;
  }


  heap_element remove()
  {
    // Remove an element from the heap.

    heap_element removed = _data[0];
    _data[0] = _data[_size - 1];
    _size --;
    reheap_down(0);
    return removed;
  }


  void insert(const heap_element & item)
  {
    // add to end of heap, increase size, reheap up

    _data[_size] = item;
    _size++;
    reheap_up(_size-1);
  }


  heap_element front()
  {
    // Return the element at the front of the heap

    return _data[0];
  }


  size_t size()
  {
    // Return the size of the heap
    return _size;
  }
};


// Global variables
int COUNTS[256];
string CODES[256];
int TOTALELEMENTS = 0;
string TREEREP = "";

void countElements(int frequencies[])
{
  // Count the total number of elements in the input for reference

  for (size_t i=0;i < 256;i++)
    if (frequencies[i] > 0)
    {
      TOTALELEMENTS ++;
    }
}


hnode * build_tree()
{
  // Build a huffman tree
  heap Q(priority);
  for (size_t i=0;i< 256;i++)
    if (COUNTS[i] > 0)
    {
      // If an element exists in the input add it to the tree.
      Q.insert(new hnode((unsigned char)i, COUNTS[i]));
    }
  while (Q.size() > 1) {
    // Remove elements from the heap as they are added to the tree.
    hnode *left = Q.front();
    Q.remove();
    hnode *right = Q.front();
    Q.remove();
    Q.insert(new hnode(0, left->count + right->count, left, right));
  }
  // Retrun a pointer to the front of the tree.
  return Q.front();
}


bool isInternal(hnode * tree)
{
  // Determine if a node is internal or a leaf

  if(!tree -> left and !tree -> right)
    return false;
  else
    return true;
}


string treeRep(hnode * tree)
{
  // Represent a given tree as a string of ordinary characters

  if(tree)
  {
    if (isInternal(tree))
    {
      TREEREP += 'I';
      treeRep(tree -> left);
      treeRep(tree -> right);
    }
    else
    {
      TREEREP += 'L';
      TREEREP += tree -> letter;
      treeRep(tree -> left);
      treeRep(tree -> right);
    }
  }
  return TREEREP;
}


void updateCodes(hnode * tree, string code)
{
  // Update the codes for each characte
  if(!tree -> left and !tree -> right)
  {
    CODES[tree -> letter] += code;
  }
  if (tree -> left)
  {
    updateCodes(tree -> left, code + "0");
  }
  if (tree -> right)
  {
    updateCodes(tree -> right, code + "1");
  }
}


string printCodes(unsigned char element)
{
  // Return a chars code.

  return CODES[element];
}


unsigned char bitstr2byte(string code)
{
  // Turn bit string into a byte
  // pre: code.length() == 8

  unsigned char byte = 0;
  for (int i = 7; i >= 0; i--)
  {
    if (code[i] == '0')
    {
      byte += pow(2, 7 - i) * 0;
    }
    else
    {
      byte += pow(2, 7 - i) * 1;
    }
  }
  return byte;
}


void error(string msg)
{
  // Report an error

  cout << msg << endl;
  exit(1);
}


string endOfString(string test)
{
  // Slice a string at the eigth position

  string slice = "";
  if (test.length() >= 8)
  {
    for (size_t i = 8; i < test.length(); i++)
    {
      slice += test[i];
    }
    return slice;
  }
  else
    return test;
}


string firstEight(string test)
{
  // Return the first 8 chars of a string

  string final ="";
  if (test.length() >= 8)
  {
    for (size_t i = 0; i < 8; i++)
    {
      final += test[i];
    }
    return final;
  }
  else
    return test;
}


int main(int argc, char ** argv)
{
  // Variable will track the total number of elements in the input file.
  int inputLength = 0;

  if (argc != 2)
    error("Wrong number of arguments");
  ifstream fin(argv[1]);
  for (size_t i=0;i < 256;i++)
    COUNTS[i] = 0;
  // Read the file
  while (true) {
    int b = fin.get();
    if (!fin)
      break;
    COUNTS[b]++;
    inputLength ++;
  }
  // Build the tree and update the codes
  hnode * tree = build_tree();
  updateCodes(tree, "");

  // Close the input file, so it can be read again
  fin.close();
  fin.open(argv[1]);

  ofstream fout((string(argv[1]) + ".huf").c_str());

  // Output the tree representation and number of elements to the .huf.
  fout << inputLength;
  fout << treeRep(tree);

  // Output the codes for each char in the input
  // Final code variable will be used to output the codes.
  string finalCode = "";
  string testString = "";
  while (true) {
    unsigned char b = fin.get();
    finalCode += printCodes(b);
    testString += printCodes(b);

    if (testString.length() >= 8)
    {
      fout << bitstr2byte(firstEight(testString));
      testString = endOfString(testString);
    }
    if (!fin)
      break;
  }
  // Implement edge case if final group of 8 bits is not complete
  if (testString != "")
  {
    while(testString.length() < 8)
      testString += "0";
      fout << bitstr2byte(firstEight(testString));
  }
}
