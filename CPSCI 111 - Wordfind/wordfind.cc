/******************************************************************************
*                                                                             *
* wordfind.cc                                                                 *
* Zach Kleinbaum                                                              *
* Project 1: Finding Words                                                    *
* 9/5/2016                                                                    *
*                                                                             *
* This program, wordfind, is designed to search a given square grid of        *
* letters.  If a word is in the grid, it will be capitalized.                 *
******************************************************************************/

#include <wordgrid.h>

using namespace std;

//-function: upper(word, row, column, dr, dc, wordgrid & grid)------------------
// PRE: a word that exists within the grid, that should be capitalized
// with given directions and starting coordinates.
// Post: the word will be capitalized int the grid.
// CITATION: http://www.cplusplus.com/forum/general/32603/
// Function to uppercase a char.
void upper(string word, size_t row, size_t column, int dr, int dc,
           wordgrid & grid)
{
  // A for loop that will index the letters of a word and uppercase each of
  // them in the grid individually.  The loop will add the directions to the
  // coordinates in order to move in the proper direction.
  for (size_t k = 0; k < word.length(); k++)
  {
    char letter = toupper(word[k]);
    grid.set(row, column, letter);
    row = row + dr;
    column = column + dc;
  }
}


//-funtion: directionCheck(char letter, int row, int column, int dr, int dc,
// wordgrid)
// PRE: will check to see if a letter exists in all 8 possible directions(r, c):
//      ((0,-1), (0,-1), (1,1), (1, -1), (-1,1), (-1,-1), (1,0), (-1,0)).
//      1 = right/up, -1 = left/down
//      Must implement a bounds check for top/bottom row, left/right column.
// POST: Will return true if the next letter of a word exists in the grid.
bool directionCheck(char letter, size_t row, size_t column,
                    int dr, int dc, wordgrid & grid)
{
  // Return false if both directions are 0, because it is not an acceptable
  // direction.
  if (dr == 0 and dc == 0)
  {
    return false;
  }

  // Implemet a bounds check.  If row/column plus the direction is less than 0
  // we are out of bounds.  If row/ column plus direction is greater than
  // or equal to the size of the grid we are out of bounds.
  if (((int)(row + dr) < 0) or ((row + dr) >= grid.size()) or
     ((int)(column + dc) < 0) or ((column + dc) >= grid.size()))
  {
    return false;
  }

  // Return true if the grid spot is equivalent to the corresponding letter.
  if (grid.get(row + dr, column + dc) == letter)
  {
    return true;
  }

  // Return false if none of the conditions are met
  return false;
}


//-function: bool find(string word, wordgrid & grid)------------------------
// PRE: word consists of lowercase letters
// POST: If word is found in grid, starting anywhere
//       and in any of the 8 directions, it is converted
//       to uppercase in the grid, and true is returned.
//       otherwise, grid is unchanged, and false is returned.
bool find(string word, wordgrid & grid)
{
   // A count to track the place in a word.
   size_t count = 0;

   // A for loop that will cycle through the rows of the grid and a nested for
   // loop for the columns.
   for (size_t i = 0; i < grid.size(); i++)
   {
      for (size_t j = 0; j < grid.size(); j++)
      {
         count = 0;

         //Check to see if the specific word in a grid is equal to the
         //letter we are currently indexing in the word.
         if (grid.get(i,j) == word[count])
         {
            // Check to see if the word is one letter long
            // if the letter exits and is one letter long, return true and
            // capitalize the word.
            // This is a check for edge cases where the letter is one word long
            // run the upper function with 0 for both directions because a one
            // letter word does not require any movement.
            if (word.length() < 2)
            {
              upper(word, i, j, 0, 0, grid);
              return true;
            }

            // If the first letter exists add one to count and start checking
            // the next letter.
            count += 1;

            // Track the current check position/ reset the values
            // each time a new coordinate is being checked.
            size_t currentRow = i;
            size_t currentColumn = j;
            int currentDR = 0;
            int currentDC = 0;

            // Use for loops to check each direction in the grid.
            for (int dr = -1; dr < 2; dr++)
            {
              for (int dc = -1; dc < 2; dc++)
              {
                // Reset the count to one when checking a new direction.
                count = 1;

                // Use direction check to determine if the next letter of a
                // word exists in the grid.  If the word is there, then add to
                // the driection and starting position
                while (directionCheck(word[count], currentRow, currentColumn,
                       dr, dc, grid) and count < word.length())
                {
                  count += 1;

                  //Store the directions and coordinates in new variables.
                  currentDR = dr;
                  currentDC = dc;
                  currentRow = currentRow + dr;
                  currentColumn = currentColumn + dc;
                }

                // Reset the coordinates back to where the original letter
                // was found.
                currentRow = i;
                currentColumn = j;

                if (count == word.length())
                {
                  // Call the upper function and return true if the word exists.
                  upper(word, currentRow, currentColumn, currentDR, currentDC,
                        grid);
                  return true;
                }
              }
            }
         }
      }
   }
  return false;
}

//------------------------------------------------------------------------
int main()
{
  size_t dim = 0;  // size of the word grid
  string word = ""; // word to search for
  bool found = false;  // whether the word is found in the grid.
  string one_row = ""; // dim characters (one row) read from stdin
  string all_rows = ""; // dim x dim characters

  // SETUP
  cin >> dim;  // read the dimension
  // read each row and append to the string of all rows
  for (size_t r = 0; r < dim ; r = r + 1) {
    cin >> one_row;
    all_rows += one_row;
  }
  wordgrid grid(dim, all_rows);  // create the grid from that data
  cin >> word; // read the word

  // SEARCH  (you do)
  found = find(word, grid);

  // REPORT
  if (found) {
    cout << "FOUND!" << endl;
    cout << grid;
  }
  else
    cout << "NOT FOUND!" << endl;
}
