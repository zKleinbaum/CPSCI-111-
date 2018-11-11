from crossword import *

DONE = False     # global variable to control main loop
PUZZLE = Crossword(["    *",    # global variable holding a Puzzle
                    "     ",
                    "     ",
                    "     ",
                    "*    "])



def clear():
    PUZZLE.clear()
    print("Cleared.")

def create():
    """ Change the global PUZZLE to a new Crossword """
    global PUZZLE
    lines = []                  # start with no lines, then
    print("Enter lines of spaces and asterisks.")
    while True:                 # use a loop and a half:
        nextLine = input()      #    read each line,
        if nextLine == "":
            break               #    (exiting loop on empty string),
        lines.append(nextLine)  #    appending all non-empty lines into a list
    PUZZLE = Crossword(lines)   # and finally creating a Crossword from
                                # the list

def nrc():
    print("numRows() == ", PUZZLE.numRows())
    print("numCols() == ", PUZZLE.numCols())

def quit():
    """ Set DONE to true, thereby ending the interactive program """
    global DONE
    DONE = True

def fl():
    """ ask user what they're looking for, print result. """
    print(PUZZLE.findLabel(int(input("Which label? "))))

def avail():
    r,c = eval("("+input("Enter r,c sep. by comma: ")+")")
    direction = ""
    while direction not in ['across', 'down']:
        direction = input("across or down? ")
    print(PUZZLE.availableSpace(r, c, direction))

def place_shared(r, c):
    assert r in range(PUZZLE.numRows())
    assert c in range(PUZZLE.numCols())
    direction = ""
    while direction not in ['across', 'down']:
        direction = input("across or down? ")
    word = input("Word to place: ").upper()
    if PUZZLE.fits(word, r, c, direction):
        PUZZLE.place(word, r, c, direction)
    else:
        print("It doesn't fit.")

def place_by_rc():
    r,c = eval("("+input("Enter r,c sep. by comma: ")+")")
    place_shared(r, c)

def place_by_label():
    r,c = PUZZLE.findLabel(int(input("Which label? ")))
    if r == -1:
        print("Can't find that label.")
    else:
        place_shared(r, c)

def menu(items):
    """ Given a list of tuples: (description, function)
        Show a menu of descriptions and wait for the user to
        enter a valid choice (by index number).  Return
        the corresponding function """
    choice = -1

    # loop:

    while True:

        # print a menu of items, indexed 0...length-1

        num = 0
        for (desc, _) in items:
            print (str(num)+") " + desc)
            num += 1

        # Get user input.  Handle it if they type garbage.

        try:
            choice = int(input("Choice: "))
        except ValueError:
            choice = -1

        # Exit with the corresponding function when they've entered
        # a valid index.

        if choice >= 0 and choice < len(items):
            return items[choice][1]

        # Otherwise print a helpful error message and repeat.

        print("Error.")


def main():
    """ Interactive program to manipulatpe a Crossword puzzle """
    print("Welcome to the crossword puzzle program")

    # loop until DONE is true:

    while not DONE:

        # print the puzzle

        print(PUZZLE)

        # Show the menu and get a function to call

        fn = menu([("Create a blank puzzle", lambda:create()),
                   ("numRows & numCols", lambda:nrc()),
                   ("available space", lambda:avail()),
                   ("clear", lambda :clear()),
                   ("findLabel", lambda : fl()),
                   ("place - by r,c", lambda : place_by_rc()),
                   ("place - by label", lambda : place_by_label()),
                   ("quit", lambda :quit())
        ])

        # Call the function

        fn()

if __name__ == "__main__":
    main()
