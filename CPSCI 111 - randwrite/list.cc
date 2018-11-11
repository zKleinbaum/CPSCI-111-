/************************************************************************
    File: randwrite.cc
    Author: Zach Kleinbaum
    Date: 10/24/16
    Assignment:  Lab 5 (randwrite)

    Implementation of random word generator

************************************************************************/
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "list.h"

using namespace std;

list reader(char * filename)
{
  	// Input a text file and use that to store characters into a list.

	int count = 0;
	list storeNovel;
	ifstream in(filename);
	for(;;){
	  char c = in.get();
	  if(!in)
	    break;
	  storeNovel.add(c, count);
	  count ++;
	}
	return storeNovel;
}


list choose_seed(const list & allChars, size_t k)
{
	// Find a random starting location in the list of all characters and
	// disect a string of k length.

	size_t start = rand() % allChars.size();

	// Create a list to store the seed and then add the seed.
	list storeSeed;
	for (size_t i = 0; i < k; i++)
	{
	  char seedChar = allChars.get(start + i);
	  storeSeed.add(seedChar, i);
	}
	return storeSeed;
}


list seedFollowers(const list & allChars, list & seed, size_t k)
{
	// Create a list of all of the characters that follow the seed

	list postSeedChars;

	// Loop through all of the characters in a given text and check to see if
	// they equal the characters of the seed.
	for (size_t i = 0; i < allChars.size(); i++)
	{
	  if (allChars.get(i) == seed.get(0))
	    {
	      // Initialize a count to ensure that all letters of the seed are
	   	  // found.
	      size_t count = 0;
	      for (size_t j = 0; j < k; j++)
			{
		  	  if (allChars.get(i+j) == seed.get(j))
		    	count ++;
		  	  else
		    // Break out of the loop if one letter is not found.
		    	break;
			}
	      // Add the letters to the final list if they are found.
	    	  if (count == k)
				{
		  		  for (size_t p = 0;  p < k; p++){
		      	  	postSeedChars.add(allChars.get(i+ k), postSeedChars.size());
		   			}
				}
	    }
	}
	return postSeedChars;
}


char addResult(list & seedFollowers, list & results)
{
	// Add a random one of the seed followers to the result.

	size_t index = rand() % seedFollowers.size();
	results.add(seedFollowers.get(index), results.size());
	return seedFollowers.get(index);
}


void updateSeed(list & seed, char letter)
{
	// Add the chosen character to the seed and delete the preexisting
	// first letter.
	// Example: pre seed: <a,b>
	// characer: 'c'
	// post seed: <b,c>
	seed.add(letter, seed.size());
	seed.remove_at(0);
}


void outputToFile(list & final, char* outputFile)
{
	// Take the final results and add them to an output file.

	ofstream out(outputFile);
	for (size_t i = 0; i < final.size(); i++)
	{
	  out << final.get(i);
	}
}


int main(int argc, char** argv)//int argc, char const *argv[])
{
	// Reset random seed
	srand(time(NULL));

	// Check that there are enough parameters.
	if (argc < 1){
	  cout << "more parameters are required"<< endl;
	  return 0;
	}

	// Check that the text file  can be opened for reading
	ifstream in(argv[3]);
	if (!in.good()){
	  cout << "The file is not readible." << endl;
	  return 0;
	}

	// Check that both k and length are positive, if so initialize the variable.
	if (atoi(argv[1]) < 0){
	  cout << "k cannot be negative"<< endl;
	  return 0;
	}
	size_t k =  size_t(atoi(argv[1]));
	if (atoi(argv[2]) < 0){
	  cout << "length cannot be negative"<< endl;
	  return 0;
	}
	size_t length = size_t(atoi(argv[2]));

	// Call reader to build a list of the characters in the input file.
	list sample = reader(argv[3]);
	// Check that sample is larger than the desired seed length (k).
	if (sample.size() < k){
	  cout << "Text file is too small for desired seed length." << endl;
	  return 0;
	}

	// Initialize the seed and final result list
	list seed = choose_seed(sample, k);
	list final;
	// While the final list is not full, find seed followers and add them to
	// the final version of the list.
	while(final.size() < length)
	{
	  list postSeedChars = seedFollowers(sample, seed, k);
	  // If no seed followers are found, initialize a new seed.
	  while(postSeedChars.size() == 0)
	    {
	      seed = choose_seed(sample, k);
	      seedFollowers(sample, seed, k);
	    }
	  char letter = addResult(postSeedChars, final);
	  updateSeed(seed, letter);
	}
	// Add the final list to an output file
	outputToFile(final, argv[4]);
	return 0;
}
