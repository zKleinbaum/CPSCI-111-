

class Square:
    ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

    """ Square class """
# constructor
    def __init__(self, color):
        """ initialize a square where color is 'black' or 'white' """
        assert color in ['white', 'black']
        self._isblack = color == 'black'
        self._number = 0  # no number
        self._letter = "" # no letter
# accessors
    def isBlack(self):
        return self._isblack

    def isWhite(self):
        return not self.isBlack()

    def getLetter(self):
        """ return the letter currently written on this square.
        empty string indicates no letter """
        return self._letter

    def getNumber(self):
        """ return the number of this square. 0 indicates no label"""
        return self._number

# modifiers
    def setLetter(self, letter):
        """ set _letter to a new letter """
        assert letter in Square.ALPHABET
        self._letter = letter

    def removeLetter(self):
        """ Remove the letter from this square """
        self._letter = ""

    def labelWith(self, number):
        """ Give this square a label """
        assert self.isWhite() and number > 0
        self._number = number

    def removeLabel(self):
        """ Remove the label from this square """
        self._number == 0

# auxiliary methods
    def __str__(self):
        """ return a string representation of this Square """
        if self._number == 0:
            result = ["  ", "**"][self.isBlack()]
        else:
            result = str(self._number)
        if len(result) < 2:
            result += ' *'[self.isBlack()]
        if self._letter != '':
            result += self._letter
        else:
            result += " *"[self.isBlack()]
        return result

# END class Square
