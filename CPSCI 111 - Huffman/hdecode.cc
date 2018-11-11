/************************************************************************
    File: hdecode.cc
    Author: Zach Kleinbaum
    Date: 12/4/16
    Assignment:  Lab 7 (Huffman)

    Implementation of huffman decoding

************************************************************************/
#include <cstdlib>
#include <iostream>
#include <fstream>

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


hnode* buildTree(ifstream &fin){
	// Build a tree recursively. To be called during the input stage.

	char element = fin.get();

	// I represents an internal node. If the element is not I, then it must
	// be a leaf.
	if (element == 'I')
	{
		return new hnode(NULL, NULL, buildTree(fin), buildTree(fin));
	}

	// If not I, then it must be L. The following char is a the letter.
	return new hnode(fin.get(),NULL, NULL, NULL);
}


bool isInternal(hnode * tree)
{
  // Determine if a node is internal or a leaf

  if(!tree -> left and !tree -> right)
    return false;
  else
    return true;
}

// Global variable that will store representation of tree
string TREEREP = "";

string treeRep(hnode * tree)
{
  // Represent a given tree as a string of ordinary characters.
  // I is internal, L is leaf. Leafs are followed by their data.

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


string byte2bit(unsigned char byte)
{
  // Convert byte to bit string by determining if the number is divisible by 2.
  // Will turn unsigned char into 0 and 1.

  unsigned char element = byte;
  string bits = "";
  for (int i = 0; i < 8; i++)
  {
    if ((element % 2) == 0)
    {
      bits = '0' + bits;
    }
    else
    {
      bits = '1' + bits;
    }
    element = element / 2;
  }
  return bits;
}


string navTree(hnode * tree, string codes, int size)
{
  // Given a string of bits, navigate the tree and return the data of the
  // encoded file.

  hnode * root = tree;
  hnode * current = tree;

  // Count will be used to track the number of elements that are output.
  int count = 0;
  string output = "";

  // Run the loop until the number of elements outputed equals the orinal file.
  for (size_t i = 0; i < codes.length() and count < size; i++)
  {
    if (codes[i] == '0')
    {
      current = current -> left;
    }
    else if(codes[i] == '1')
    {
      current = current -> right;
    }
    if(!isInternal(current))
    {
      output += current -> letter;
      count ++;
      current = root;
    }
  }
  cout << output << endl;
  return output;
}

int main(int argc, char ** argv)
{
	ifstream fin(argv[1]);

	string filename = (string)argv[1];

	if(filename.substr(filename.length()-4, 4) != ".huf")
		cout << "Not a .huf file. Cannot decode.";

	if (argc != 2)
    	cout << "Wrong number of arguments";

    // Store the input variables.
    int fileLength;
    fin >> fileLength;
    hnode * tree = buildTree(fin);
    string CODES = "";

    // The remainder of the input file is ts bytes to be converted into bits.
    while (true) {
      unsigned char b = fin.get();
      if (!fin)
        break;
      CODES += byte2bit(b);
    }

    // Retrive the output.
    navTree(tree, CODES, fileLength);
	return 0;
}
