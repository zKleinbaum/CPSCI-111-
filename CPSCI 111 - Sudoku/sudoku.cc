/************************************************************************
    File: sudoku.cc
    Author: Zach Kleinbaum
    Date: 9/19/16
    Assignment:  Project 3: Sudoku

    Implementation of the completion of a sudoku puzzle.

************************************************************************/
#include <iostream>
#include <cstdlib>
#include "sudokuboard.h"
#include "stack.h"

using namespace std;

void placeRow(string sample, sudokuboard &product)
{
	// This function will take a string (sample), which is being input by the
	// user.  It will also take the reference to an empty sudokuboard and the
	// current row.  A for loop will be used to input each element of the input
	// puzzle.
	for (int r = 0; r < 9; r++)
	{
		cin >> sample;
		for (size_t c = 0; c < 9; c++)
		{
			product.place(r, c, sample[c]);
		}
	}
}


void backtrack(sudokuboard &puzzle, stack &tracker)
{
	// This function will be called to back track.  It will go to the last spot
	// and place a different number.  It takes references to a tracker stack
	// and a sudoku board as parameters.

	// This variable will track the element to be placed.
	char newNum = 'a';

	// Trackers for the coordinates.
	int row = 0;
	int col = 0;

	// This variable will track the lowest possible number
	int lowNum = 10;

	while(newNum == 'a')
	{
		// Track the previous columns, rows, and elements.  Pop them off
		// the stack.
		int numIndex = tracker.top();
		tracker.pop();
		col = tracker.top();
		tracker.pop();
		row = tracker.top();
		tracker.pop();

		// Remove the previous element from the board.
		puzzle.remove(row, col);

		// All of the possible elements
		string testString = "123456789";

		// If the number in scope is 9, there are no other possibilities.  Keep
		// backtracking.
		if (numIndex == 8)
		{
			newNum = 'a';
		}
		// Find the lowest possible number.
		else
		{
			for (int i = numIndex + 1; i < 9; i++)
			{
				if((puzzle.canPlace(row, col, testString[i]) and i < lowNum))
					{
						lowNum = i;
						newNum = testString[i];
					}
			}

		}
	}
	// Add the element to the board and track everything on the stack.
	puzzle.place(row, col, newNum);
	tracker.push(row);
	tracker.push(col);
	tracker.push(lowNum);
}


void mostConstrained(sudokuboard puzzle, stack &tracker)
{
	// This function will find the coordinates of the spot on the board that
	// takes the least amount of numbers. It takes a sudokuboard and a
	// reference to a stack for tracking purposes.

	// A tracker for the smallest number of elements a board can take.
	size_t count = 10;

	// A temporary tracker used for comparison.
	size_t tempCount = 0;

	// The row of the most constrained spot.
	size_t row = 0;

	// The column of the most constrained spot.
	size_t col = 0;

	// A string of possible element
	string test = "123456789";


	// For loop will determine the number of elements that fit in each spot
	for (size_t r = 0; r < 9; r++)
	{
		for (size_t c = 0; c < 9; c++)
		{
			for (int i = 0; i < 10; i++)
			{
				if (puzzle.canPlace(r, c, test[i]))
				{
					tempCount = tempCount + 1;
				}
			if (tempCount != 0 and  tempCount < count)
				{
					count = tempCount;
					row = r;
					col = c;
				}
			}
		}
	}
	// If the temporary count is equal to zero there are no possible solutions.
	// Commence back tracking.
	if (tempCount == 0)
	{
		backtrack(puzzle, tracker);
	}
	// If there are solutions, push the coordinates on to the stack.
	else
	{
		tracker.push(row);
		tracker.push(col);
	}
}


void placeLowest(sudokuboard &puzzle, stack &tracker)
{
	// This function will place the lowest possible number in the least
	// constrained spot.  It takes references to a sudokuboard and a tacker
	// stack as parameters.

	// Pop the stack in order to retrive the row and column in scope and save
	// them as variables.
	size_t col = tracker.top();
	tracker.pop();
	size_t row = tracker.top();
	tracker.pop();

	// This variable will track the lowest possible number at the particular
	// coordinates in char form.
	char lowest = 'z';

	// This variable will track the index of the lowest possible number in int
	// form for comparison purposes.
	int lowNum = 10;

	// All possible elements in a string.
	string testString = "123456789";

	// Use the for loop to determine the lowest placeable number.
	for (int i = 0; i < 9; i++)
	{
		char test = testString[i];
		if (puzzle.canPlace(row, col, test) and i < lowNum)
		{
			lowNum = i;
			lowest = test;
		}
	}
	// If there are no possible numbers to fit the spot, commence backtracking.
	if (lowest == 'z')
	{
		backtrack(puzzle, tracker);
	}
	// If a number fits push the coordinates and the index on to the stack
	// and place the element onto the board.
	else
	{
		puzzle.place(row, col, lowest);
		tracker.push(row);
		tracker.push(col);
		tracker.push(lowNum);
	}
}


void solve(sudokuboard &puzzle, stack &tracker)
{
	// This function will solve an incomplete puzzle.
	// The parameters are a reference to a sudoku puzzle board and a tracker
	// stack.

	// While the puzzle is not solved call mostConstrained and placeLowest.
	while(not puzzle.solved())
	{
		mostConstrained(puzzle, tracker);
		placeLowest(puzzle, tracker);
	}
	puzzle.print();
}


int main()
{
	// Establish a variable to account for the input to be.
	string sample;

	// Establish a tracker for rows, cols, and elements.
	stack tracker;

	// Establish a variable for an empty board.
	sudokuboard practice;

	// Take the input.
	placeRow(sample, practice);

	// Solve the puzzle.
	solve(practice, tracker);
	return 0;
}
