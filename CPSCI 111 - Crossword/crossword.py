""" Crossword Puzzle module """

from square import Square

class Crossword:
    """ Crossword puzzle class """

    # constructor

    def __init__(self, lineList):
        """ initialize a grid of Squares according to lineList.
        where lineList[r][c] is '*', the square is black;
        otherwise white. """

        # start with an empty grid
        self._grid = []

        # ensure precondition: all lines are the same length
        if lineList != []:
            for line in lineList:
                assert len(line)==len(lineList[0])

        # create a row of Squares for each line
        # in _grid

        for line in lineList:
            nextline = []
            self._grid.append(nextline)
            for sym in line:
                assert sym in " *"
                # each square is black or white depending on whether
                # the symbol is space or asterisk.
                if sym == '*':
c                    nextline.append(Square('black'))
                else:
                    nextline.append(Square('white'))
        self.labelSquares()

    # accessors

    def numRows(self):
        """ This will return the number of rows in the crossword as a int """

        return len(self._grid)


    def numCols(self):
        """ This will return the number of columns in the
            crossword as an int """

        return len((self._grid)[0])


    def toBeLabeled(self, row, col):
        """ A square shall be labeled if and only if it is white and does
            not have white squares both above and to its left.
            (to be implemented in project) """

        #must check to see if the square is black.  If the square is black than
        #it cannot be labeled
        if self._grid[row][col].isBlack():
            return False

        #must check to see if the square is furthest left or on the top row,
        #which will always be white
        if row == 0 or col == 0:
            return True

        #must check to see if there are black squares above or below
        if self._grid[row - 1][col].isBlack() or\
        self._grid[row][col - 1].isBlack():
            return True

        #If the second conditions are not met we return false
        return False


    def findLabel(self, label):
        """ return a list of intergers which is the location of
            a particular label """

        #Must check each square in each column to see if its label is equal
        #to the label variable
        for i in range(len(self._grid)):
            for j in range(len(self._grid[i])):
                if self._grid[i][j].getNumber() == label:
                    return (i,j)

        #if the label is not found return (-1,-1)
        return(-1,-1)


    def availableSpace(self, r, c, direction):
        """ return an interger, which is equal to the number of free spaces in
            a given direction """

        #establish a count
        count = 0

        #check to see if the adjacent space is white for both directions
        #use a for loop to cycle through each square and add 1 to the count if
        #white.
        if direction == 'across':
            for i in range((len(self._grid[0])) - c):
                if self._grid[r][c + i].isWhite():
                    count = count + 1
                else:
                    return count

        if direction == 'down':
            for i in range((len(self._grid[0])) - r):
                if self._grid[r + i][c].isWhite():
                    count = count + 1
                else:
                    return count
        return count


    def fits(self, word, r, c, direction):
        """ determine if a word can fit at a given location and makes sure that
            pre existing letters are also in the word """

        #create a check to see if the string is the length of the word
        check = 0

        #check to see if the square is labeled
        if self._grid[r][c].getNumber() > 0:

            #call the availableSpace method to see if a space is available the
            #same size as a word
            if self.availableSpace(r, c, direction) == len(word):

                #use the getLetter method to determine if a square has the same
                #letter as the word or is a blank string
                if direction == 'across':
                    for i in range(len(word)):
                        if self._grid[r][c + i].getLetter() == word[i] or\
                        self._grid[r][c + i].getLetter() == '':
                            check = check + 1

                if direction == 'down':
                    for i in range(len(word)):
                        if self._grid[r + i][c].getLetter() == word[i] or\
                        self._grid[r + i][c].getLetter() == '':
                            check = check + 1

                #if the length of the check and the desired word are equal than
                #the word can fit.
                if check == len(word):
                    return True

        return False


    # modifiers

    def labelSquares(self):
        """ In row-major order, sequentially number all the squares
            to be labeled.   Called by the constructor
            (to be implemented in project) """

        #maintain a count of labels
        count = 1

        #cycle through each square and determine if it can be labeled.
        #If it can be labeled we will add one to the count used to label.
        for i in range(len(self._grid)):
            for j in range(len(self._grid[0])):
                if self.toBeLabeled(i,j):
                    self._grid[i][j].labelWith(count)
                    count = count + 1


    def clear(self):
        """ remove all letters from the crossword """

        #cycle through the squares of the crossword and remove the letters
        for i in range(len(self._grid)):
            for j in range(len(self._grid[0])):
                self._grid[i][j].removeLetter()


    def place(self, word, r, c, direction):
        """ place a word in a given square """

        #First check to see if a word fits in a given slot
        if self.fits(word, r, c, direction):

            #change the letter in the adjacent spots if it fits
            if direction == 'across':
                for i in range(len(word)):
                    self._grid[r][i + c].setLetter(word[i])

            if direction == 'down':
                for i in range(len(word)):
                    self._grid[i + r][c].setLetter(word[i])


    def __str__(self):
        """ return a string representation of this Crossword """
        if len(self._grid) == 0:
            return ""
        result = '-' + "----" * len(self._grid[0]) + '\n'
        for row in self._grid:
            result += '|'
            for sq in row:
                result += str(sq) + '|'
            result += '\n'
            result += '-' + "----" * len(self._grid[0]) + '\n'
        return result

# End class Crossword
