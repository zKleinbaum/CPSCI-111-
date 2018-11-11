/************************************************************************
    File: sudokuboard.cc
    Author: Zach Kleinbaum
    Date: 9/19/16
    Assignment:  Project 3: Sudoku

    Implementation of a sudokuboard class.

************************************************************************/
    #include <iostream>
    #include "sudokuboard.h"

    using namespace std;

    /*** Constructor ***/
    sudokuboard::sudokuboard()
    {
    	// Initialize a blank sudoku board.
    	// Use nested for loops to navigate all of the columns and rows.
    	// Assign each position of the arrays equal to underscore, which
    	// represents an empty spot.
    	for (size_t row = 0; row < _capacity; row++)
    	{
    		for (size_t col = 0; col < _capacity; col++)
    		{
    			_grid[row][col] = '_';
    		}
    	}
    }


    /*** Const Member Functions ***/
    void sudokuboard::print() const
    {
    	// Print the contents of the puzzle (_grid).
    	// Use nested for loops to print each item.
    	for (size_t row = 0; row < _capacity; row++)
    	{
    		for (size_t col = 0; col < _capacity; col++)
    		{
    			cout << _grid[row][col];
    		}
    		// End the line every time the column changes
    		cout << endl;
    	}
    }


    char sudokuboard::get(size_t row, size_t col) const
    {
        // Return the element at a given row and column.
        return _grid[row][col];
    }


    bool sudokuboard::canPlace(size_t row, size_t col, char element) const
    {
        // Determine if the element can be placed at a given location.
        // Several checks are required:
        // 1. The spot must be empty
        // 2. There must be no equivalent elements in the same row or column
        // 3. There must be no equivalent elements in the same 3x3 box.

        if (_grid[row][col] != '_')
        {
            return false;
        }
        for (size_t i = 0; i < _capacity; i++)
        {
            if (_grid[row][i] == element)
            {
                return false;
            }
        }
        for (size_t j = 0; j < _capacity; j++)
        {
            if (_grid[j][col] == element)
            {
                return false;
            }
        }
        // Initialize variables to find the coordinates of the first location
        // in a box. In sudoku a box is comprised of a 3X3 area.  There cannot
        // be any duplicates in a box. Use int division to find the starting
        // location.
        size_t boxrow = (row / 3) * 3;
        size_t boxcol = (col / 3) * 3;
        for (size_t r = boxrow; r < boxrow + 3; r++)
        {
            for (size_t c = boxcol; c < boxcol + 3; c++)
            {
                if (_grid[r][c] == element)
                {
                    return false;
                }

            }
        }
        return true;
    }


    bool sudokuboard::solved() const
    {
        // Return true if the board is solved.
        // Use a for loop to determine if any of the spots are empty.
        // If they are empty return false.
        for (size_t row = 0; row < _capacity; row++)
        {
            for (size_t col = 0; col < _capacity; col++)
            {
                if (_grid[row][col] == '_')
                {
                    return false;
                }
            }
        }
        return true;
    }


    /*** Non-Const Member Functions ***/
    void sudokuboard::place(size_t row, size_t col, char element)
    {
        // Place the element at the given position.
        _grid[row][col] = element;
    }


    void sudokuboard::remove(size_t row, size_t col)
    {
       // Remove the element at the given position by changing the value to '_'.
        _grid[row][col] = '_';
    }
        
