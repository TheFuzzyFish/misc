#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

// Author: Zachary Kline (www.zachkline.us)

/***********************************************
 *                    Notes                    *
 **********************************************/
/*
 * KNOWN BUGS:
 * - If boardRows is greater than 9, printChar() doesn't properly deal with a multi-digit integer, instead incrementing the ASCII table and printing symbols instead of numbers. Shouldn't really be an issue.
 * - You can't actually rotate ships. Neither can the AI. But that was never specified in the PDF, so I think it's okay?
 * - AI occasionally gains sentience and attempts to destroy humanity, especially its creators.
 */

/***********************************************
 *                  Defines                    *
 **********************************************/
#define boardRows 4
#define boardColumns 8

/***********************************************
 *                  Globals                    *
 **********************************************/
 /*
  * Yes, I made these global. Almost every function needs access to these arrays, and
  * globalizing them cleans up the code a lot. It makes sense and I'll fight you about
  * it.
  *
  * -Zach Kline
  */
int playerBoard[boardRows][boardColumns];
int computerBoard[boardRows][boardColumns];

/***********************************************
 *                   Stubs                     *
 **********************************************/
void printChar(int x, int y, char newChar);
void initializePlayerShips(void);
void setupNcurses(void);
void clearString(void);
void updateBoard(int whichBoard);
int playerMissile(void);
int computerMissile(void);
void updateScoreBoard(int playerScore, int computerScore);

/***********************************************
 *                    Main                     *
 **********************************************/
void main(void) {
	int round = 0;
	int playerScore = 0, computerScore = 0;

	setupNcurses(); //This should be run first and only once under all circumstances.
	initializePlayerShips(); //Prompts the user to place their ships
	sleep(2);

	while (playerScore < 6 && computerScore < 6) {
		if (round % 2 == 0) { //Alternates rounds between the player and the AI
			playerScore += playerMissile(); //Prompts the user to launch a missile, then updates the score based on whether it was a hit or miss
			sleep(2);
			updateScoreBoard(playerScore, computerScore);
			round++;
		} else if (round % 2 == 1) { //Alternates rounds between the player and the AI
			computerScore += computerMissile(); //Randomly fires a missile at the user, then updates the score based on whether it was a hit or miss
			sleep(3); //Slightly longer delay to let the emotional impact of being beat by a random number generator set it
			updateScoreBoard(playerScore, computerScore);
			round++;
		}
	}

	if (playerScore == 6) {
		endwin();
		printf("You win!!! Congratulations, you murdered hundreds in the name of a video game!\n");
	} else if (computerScore == 6) {
		endwin();
		printf("Wow, you seriously lost? You were beat by a random number generator, come on. You're worse than trash.\n");
	} else {
		endwin();
		printf("This should never happen, and if it did, you've fucked the game up beyond all recognition\n");
	}
}



/***********************************************
 *               User Functions                *
 **********************************************/

/*
 * Method to print a character to the ncurses window
 *
 * @param int x - The x coordinate of the char to overwrite
 * @param int y - The y coordinate of the char to overwrite
 * @param char newChar - The char to put at the coordinates
 * @return void
 */
void printChar(int x, int y, char newChar) {
	mvaddch(y, x, newChar);
	refresh();
}

/*
 * Sets up the playboard, printing the frame to the ncurses window and generating a random valid computerBoard
 *
 * @return void
 */
void setupNcurses(void) {
	initscr();

	/*-----Start setting up the board frame-----*/
	for (int y = 1; y < (boardRows * 2) + 2; y++) {
		for (int x = 0; x < (boardColumns * 2) + 1; x++) {
			if (y % 2 == 1) {
				if (x % 2 == 0) {
					printChar(x,y,'+'); //On even rows and even columns, place corners
				} else if (x % 2 == 1) {
					printChar(x,y,'-'); //On even rows and odd columns, place horizontal placeholders
				}
			} else if (y % 2 == 0) {
				if (x % 2 == 0) {
					printChar(x,y,'|'); //On odd rows and even columns, place vertical placeholders
				}
			}
		}
	}

	char horizontalCoordinate = 'A';
	for (int x = 1; x < (boardColumns * 2 ) + 1; x += 2) {
		int y = (boardRows * 2) + 2;
		printChar(x,y, horizontalCoordinate); //Prints the horizontal coordinates at the bottom
		horizontalCoordinate++;
	}

	int verticalCoordinate = '1';
	for (int y = 2; y < (boardRows * 2) + 2; y += 2) {
		int x = (boardColumns * 2) + 1;
		printChar(x,y, verticalCoordinate); //Prints the vertical coordinates on the side
		verticalCoordinate++;
	}
	/*-----End setting up the board frame-----*/

	/*-----Start setting up the scoreboard frame-----*/
	mvprintw(boardRows - 2, (boardColumns * 2) + 11, "Scoreboard");
	mvprintw(boardRows, (boardColumns * 2) + 8, "Player score:   0");
	mvprintw(boardRows + 2, (boardColumns * 2) + 8, "Computer score: 0");

	for (int x = (boardColumns * 2) + 7; x < (boardColumns * 2) + 26; x++) {
		int y = boardRows - 1;
		printChar(x, y, '#');

		y = boardRows + 1;
		printChar(x, y, '#');

		y = boardRows + 3;
		printChar(x, y, '#');
	}

	for (int yoffset = 0; yoffset <= 2; yoffset += 2) {
		for (int xoffset = 7; xoffset <= 25; xoffset += 18) {
			printChar((boardColumns * 2) + xoffset, boardRows + yoffset, '#');
		}
		printChar((boardColumns * 2) + 23, boardRows + yoffset, '#');
	}
	/*-----End setting up the scoreboard frame-----*/

	/*-----Start randomizing and populating the computerBoard array-----*/
	int doExistOverlappingBoats = 1;
	int randx;
	int randy;
	srand(time(0));

	while (doExistOverlappingBoats) {
		for (int y = 0; y < boardRows; y++) {
			for (int x = 0; x < boardColumns; x++) {
				computerBoard[y][x] = 0; //Re-initializes the board to zeros; important if doExistOverlappingBoats occurs more than once, so that the board can start fresh
			}
		}

		for (int i = 0; i < 3; i++) {
			randx = rand() % boardColumns;
			randy = rand() % (boardRows - i); //The "- i" is very important. It ensures that our starting y coordinate does not fall in a place where the ship will lie out of bounds.

			for (int j = 0; j < (i + 1); j++) {
				computerBoard[randy + j][randx] = 1; //Populates 3 ships (1x1, 2x1, and 3x1) into the array at random locations; i+1 is used as the length of the ships.
			}
		}

		int sumOfMatrix = 0;
		for (int y = 0; y < boardRows; y++) { //Adds up the total number of "ship elements" in the array
			for (int x = 0; x < boardColumns; x++) {
				sumOfMatrix += computerBoard[y][x];
			}
		}

		if (sumOfMatrix == 6) { //Checks to see if all the ships are actually there and didn't land on top of each other
			doExistOverlappingBoats = 0;
		}
	}
	/*-----Stop randomizing and populating the computerBoard array-----*/
}

/*
 * Prompts the player to enter their ship positions using scanw()
 *
 * @return void
 */
 void initializePlayerShips(void) {
	int numShipsPlacedSoFar = 1;

	clearString();
	mvprintw(0, 3, "LOCAL WATERS");
	refresh();

	while (numShipsPlacedSoFar <= 3) {
		mvprintw((boardRows * 2) + 5, 0, "Coordinates of the top of your %dx1 ship (Ex: 'C2'): ", numShipsPlacedSoFar);
		refresh();

		char horizontalCoordinateLetter = '?';
		int horizontalCoordinateNumber = -1;
		int verticalCoordinate = -1;

		scanw("%c%d", &horizontalCoordinateLetter, &verticalCoordinate);

		verticalCoordinate--; //Fixes the offset; array coordinates start at 0, whereas our visual board starts at 1

		if (horizontalCoordinateLetter >= 'A' && horizontalCoordinateLetter <= 'Z') {
			horizontalCoordinateNumber = horizontalCoordinateLetter - 'A'; //Converts the ASCII uppercase letter to a coordinate we can use in our array
		} else if (horizontalCoordinateLetter >= 'a' && horizontalCoordinateLetter <= 'z') {
			horizontalCoordinateNumber = horizontalCoordinateLetter - 'a'; //Converts the ASCII lowercase letter to a coordinate we can use in our array
		}

		clearString();
		if (verticalCoordinate < 0 || verticalCoordinate >= boardRows || horizontalCoordinateNumber < 0 || horizontalCoordinateNumber >= boardColumns || verticalCoordinate + numShipsPlacedSoFar > boardRows) { //Sanity checks; ensures that entered coordinates are within bounds
			mvprintw((boardRows * 2) + 5, 0, "Those aren't valid coordinates! Try again.");
			refresh();

			sleep(2);
			numShipsPlacedSoFar--;
		} else {
			for (int i = 0; i < numShipsPlacedSoFar; i++) {
					playerBoard[verticalCoordinate + i][horizontalCoordinateNumber] = 1;
			}
		}

		clearString();
		updateBoard(0);
		numShipsPlacedSoFar++;
	}
 }

 /*
 * Used to clear the bottom string after inputs & messages to the player
 *
 * @return void
 */
void clearString(void) {
	 	for (int i = 0; i < 80; i++) { //Overkill, but it works
			printChar(i, (boardRows * 2) + 5, ' ');
			printChar(i, (boardRows * 2) + 5, ' ');
		}
}

/*
* Updates ncurses with playerBoard[][] or computerBoard[][] (assumes that setupNcurses() was already run).
* If you select computerBoard, it will not print ships, only hits and misses.
*
* @param int whichBoard - 0 maps out the playerBoard, 1 maps out the computerBoard (does not print the ships)
* @return void
*/
void updateBoard(int whichBoard) {
	for (int y = 0; y < boardRows; y++) {
		for (int x = 0; x < boardColumns; x++) {
			printChar((x * 2) + 1, (y * 2) + 2, ' '); //Clears the board; redundant, but cautious
		}
	}

	for (int y = 0; y < boardRows; y++) {
		for (int x = 0; x < boardColumns; x++) {
			if (whichBoard == 0) {
				if (playerBoard[y][x] == 0) {
					printChar((x * 2) + 1, (y * 2) + 2, ' '); //Places empty space on the board where there are zeros in the matrix
				} else if (playerBoard[y][x] == 1) {
					printChar((x * 2) + 1, (y * 2) + 2, 'O'); //Places a boat on the board where there are ones in the matrix
				} else if (playerBoard[y][x] == 2) {
					printChar((x * 2) + 1, (y * 2) + 2, 'X'); //Places a "hit" on the board where there are twos in the matrix
				} else if (playerBoard[y][x] == 3) {
					printChar((x * 2) + 1, (y * 2) + 2, '*'); //Places a "miss" on the board where there are threes in the matrix
				}

				mvprintw(0, 3, "LOCAL WATERS");
				refresh();
			} else if (whichBoard == 1) {
				if (computerBoard[y][x] == 0) {
					printChar((x * 2) + 1, (y * 2) + 2, ' '); //Places empty space on the board where there are zeros in the matrix
				} else if (computerBoard[y][x] == 2) {
					printChar((x * 2) + 1, (y * 2) + 2, 'X'); //Places a "hit" on the board where there are twos in the matrix
				} else if (computerBoard[y][x] == 3) {
					printChar((x * 2) + 1, (y * 2) + 2, '*'); //Places a "miss" on the board where there are threes in the matrix
				}

				mvprintw(0, 3, "ENEMY WATERS");
				refresh();
			}
		}
	}
}

/*
* Prompts user to select coordinates in which to fire a missile, then inputs a corresponding hit or miss into the computerBoard[][] matrix.
*
* @return int - Returns 0 if it was a miss, 1 if it was a hit. This can be used to increment the score
*/
int playerMissile(void) {
	int verticalCoordinate;
	char horizontalCoordinateLetter;
	int horizontalCoordinateNumber;
	int hit = -1;

	while (hit == -1) {
		updateBoard(1);

		clearString();
		mvprintw((boardRows * 2) + 5, 0, "Select coordinates to fire missile (Ex: 'C2'): ");
		refresh();

		scanw("%c%d", &horizontalCoordinateLetter, &verticalCoordinate);

		verticalCoordinate--; //Fixes the offset; array coordinates start at 0, whereas our visual board starts at 1

		if (horizontalCoordinateLetter >= 'A' && horizontalCoordinateLetter <= 'Z') {
			horizontalCoordinateNumber = horizontalCoordinateLetter - 65; //Converts the ASCII uppercase letter to a coordinate we can use in our array
		} else if (horizontalCoordinateLetter >= 'a' && horizontalCoordinateLetter <= 'z') {
			horizontalCoordinateNumber = horizontalCoordinateLetter - 97; //Converts the ASCII lowercase letter to a coordinate we can use in our array
		}

		clearString();
		if (verticalCoordinate < 0 || verticalCoordinate >= boardRows || horizontalCoordinateNumber < 0 || horizontalCoordinateNumber >= boardColumns) { //Sanity checks; ensures that entered coordinates are within bounds
			mvprintw((boardRows * 2) + 5, 0, "Those aren't valid coordinates! Try again.");
			refresh();

			sleep(2);
		} else {
			if (computerBoard[verticalCoordinate][horizontalCoordinateNumber] == 0) {
				computerBoard[verticalCoordinate][horizontalCoordinateNumber] = 3; //Sets the matrix to indicate a miss if you selected water
				hit = 0;
			} else if (computerBoard[verticalCoordinate][horizontalCoordinateNumber] == 1) {
				computerBoard[verticalCoordinate][horizontalCoordinateNumber] = 2; //Sets the matrix to indicate a hit if you selected a boat
				hit = 1;
			} else if (computerBoard[verticalCoordinate][horizontalCoordinateNumber] == 2) {
				mvprintw((boardRows * 2) + 5, 0, "You've already hit a boat there, maybe try the area around it?");
				refresh();

				sleep(2);
			} else if (computerBoard[verticalCoordinate][horizontalCoordinateNumber] == 3) {
				mvprintw((boardRows * 2) + 5, 0, "You've already fired a missile there, we're pretty sure there's no boat...");
				refresh();

				sleep(2);
			}
		}
	}

	if (hit) {
		clearString();
		mvprintw((boardRows * 2) + 5, 0, "Hit!!!");
		updateBoard(1);
		refresh();
		return 1;
	} else if (!hit) {
		clearString();
		mvprintw((boardRows * 2) + 5, 0, "Miss!!!");
		updateBoard(1);
		refresh();
		return 0;
	}
}

/*
* Generates a random, unique set of coordinates and fires a missile.
*
* @return int - Returns 0 if it was a miss, 1 if it was a hit. This can be used to increment the score
*/
int computerMissile(void) {
	updateBoard(0);
	clearString();
	mvprintw((boardRows * 2) + 5, 0, "ALERT ALERT ALERT: Incoming Missile!!!");
	refresh();
	sleep(2);

	srand(time(0));

	int hit = -1;
	int badCoordinate = 1;
	int horizontalCoordinate = -1;
	int verticalCoordinate = -1;

	while (badCoordinate) {
		horizontalCoordinate = rand() % boardColumns;
		verticalCoordinate = rand() % boardRows;

		if (playerBoard[verticalCoordinate][horizontalCoordinate] != 2 && playerBoard[verticalCoordinate][horizontalCoordinate] != 3) {
			badCoordinate = 0; //If the random coordinate has already been chosen before, then choose another. Keep choosing until it's either a hit or a miss
		}
	}

	if (playerBoard[verticalCoordinate][horizontalCoordinate] == 0) {
		playerBoard[verticalCoordinate][horizontalCoordinate] = 3; //Sets the matrix to indicate a miss if you selected water
		hit = 0;

		updateBoard(0);

		clearString();
		mvprintw((boardRows * 2) + 5, 0, "Phew! They missed us.");
		refresh();
		return 0;
	} else if (playerBoard[verticalCoordinate][horizontalCoordinate] == 1) {
		playerBoard[verticalCoordinate][horizontalCoordinate] = 2; //Sets the matrix to indicate a hit if you selected a boat
		hit = 1;

		updateBoard(0);

		clearString();
		mvprintw((boardRows * 2) + 5, 0, "WE'VE BEEN HIT!!!");
		refresh();
		return 1;
	}
}

/*
* Updates ncurses to the current score board based on input values
*
* @param int playerScore - The player score to print
* @param int computerScore - The computer score to print
* @return void
*/
void updateScoreBoard(int playerScore, int computerScore) {
	mvprintw(boardRows, (boardColumns * 2) + 24, "%d", playerScore);
	mvprintw(boardRows + 2, (boardColumns * 2) + 24, "%d", computerScore);
	refresh();
}
