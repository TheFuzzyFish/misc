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
 * WARNING WARNING WARNING
 * THIS PROGRAM IS A TOTAL BODGE (see https://youtu.be/lIFE7h3m40U?t=19)
 * This program was written to be player vs AI, NOT AI vs AI as it runs.
 * The structure of the code still reflects this. The comments of the code still reflects this.
 * Parts of this code has been copied and pasted in very inefficient and unreadable ways.
 * Parts of this code has been rewritten with zero commenting.
 *
 * If you plan on augmenting this code AT ALL, please start fresh with the proper version
 * of the program. The comments are accurate, the structure is readable, and most importantly,
 * it runs the way it was designed to.
 */

/*
 * Compile with 'gcc ai-battleship.c -o ai-battleship -lncurses'
 */

/***********************************************
 *                  Defines                    *
 **********************************************/
#define boardRows 4
#define boardColumns 8
#define sleepTimeBetweenMovesInMicroseconds 1000000

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
void initializeShips(void);
void setupNcurses(void);
void clearString(void);
void updateBoard(int whichBoard);
int playerMissile(void);
int computerMissile(void);
void updateScoreBoard(int playerScore, int computerScore);
void updateTime(int startTime);
int returnScore(int whichBoard);

/***********************************************
 *                    Main                     *
 **********************************************/
void main(void) {
//	FILE* log = fopen("log.txt", "a");
//	fprintf(log, "Starting log at %d\n", time(0));
//	fclose(log);
	int round = 0;
	int playerScore = 0, computerScore = 0;
	int totalPlayerScore = 0, totalComputerScore = 0;
	int startTime = time(0);

	srand(time(0));

	setupNcurses(); //This should be run first and only once under all circumstances. updateTime(startTime);
	updateTime(startTime);

	while (1) {
		initializeShips(); //Prompts the user to place their ships
		round = rand() % 2;

		while (playerScore < 6 && computerScore < 6) {
			if (round % 2 == 0) { //Alternates rounds between the player and the AI
				playerMissile();
				playerScore = returnScore(1);
			} else if (round % 2 == 1) { //Alternates rounds between the player and the AI
				computerMissile();
				computerScore = returnScore(0);
			}
			usleep(sleepTimeBetweenMovesInMicroseconds);
			round++;
			updateScoreBoard(totalPlayerScore, totalComputerScore);
			updateTime(startTime);
		}

		if (playerScore == 6) {
			totalPlayerScore++;
//			fopen("log.txt", "a");
//			fprintf(log, "AI 1 won at %d\n", time(0));
//			fclose(log);
		} else if (computerScore == 6) {
			totalComputerScore++;
//			fopen("log.txt", "a");
//			fprintf(log, "AI 2 won at %d\n", time(0));
//			fclose(log);
		}
		playerScore = 0;
		computerScore = 0;
		updateScoreBoard(totalPlayerScore, totalComputerScore);
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
	mvprintw(boardRows, (boardColumns * 2) + 8, "AI 1 Score:     0");
	mvprintw(boardRows + 2, (boardColumns * 2) + 8, "AI 2 Score:     0");

	for (int x = (boardColumns * 2) + 7; x < (boardColumns * 2) + 35; x++) {
		int y = boardRows - 1;
		printChar(x, y, '#');

		y = boardRows + 1;
		printChar(x, y, '#');

		y = boardRows + 3;
		printChar(x, y, '#');
	}

	for (int yoffset = 0; yoffset <= 2; yoffset += 2) {
		for (int xoffset = 7; xoffset <= 34; xoffset += 27) {
			printChar((boardColumns * 2) + xoffset, boardRows + yoffset, '#');
		}
		printChar((boardColumns * 2) + 23, boardRows + yoffset, '#');
	}
	/*-----End setting up the scoreboard frame-----*/

	/*-----Start randomizing and populating the computerBoard array-----*/
	/*-----Stop randomizing and populating the computerBoard array-----*/
}

/*
 * Prompts the player to enter their ship positions using scanw()
 *
 * @return void
 */
 void initializeShips(void) {
	int doExistOverlappingBoats = 1;
	int randx;
	int randy;

	while (doExistOverlappingBoats) {
		for (int y = 0; y < boardRows; y++) {
			for (int x = 0; x < boardColumns; x++) {
				playerBoard[y][x] = 0; //Re-initializes the board to zeros; important if doExistOverlappingBoats occurs more than once, so that the board can start fresh
			}
		}

		for (int i = 0; i < 3; i++) {
			randx = rand() % boardColumns;
			randy = rand() % (boardRows - i); //The "- i" is very important. It ensures that our starting y coordinate does not fall in a place where the ship will lie out of bounds.

			for (int j = 0; j < (i + 1); j++) {
				playerBoard[randy + j][randx] = 1; //Populates 3 ships (1x1, 2x1, and 3x1) into the array at random locations; i+1 is used as the length of the ships.
			}
		}

		int sumOfMatrix = 0;
		for (int y = 0; y < boardRows; y++) { //Adds up the total number of "ship elements" in the array
			for (int x = 0; x < boardColumns; x++) {
				sumOfMatrix += playerBoard[y][x];
			}
		}

		if (sumOfMatrix == 6) { //Checks to see if all the ships are actually there and didn't land on top of each other
			doExistOverlappingBoats = 0;
		}
	}




	doExistOverlappingBoats = 1;
	randx;
	randy;

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

				mvprintw(0, 3, "AI 1 WATERS");
				refresh();
			} else if (whichBoard == 1) {
				if (computerBoard[y][x] == 0) {
					printChar((x * 2) + 1, (y * 2) + 2, ' '); //Places empty space on the board where there are zeros in the matrix
				} else if (computerBoard[y][x] == 1) {
					printChar((x * 2) + 1, (y * 2) + 2, 'O'); //Places a boat on the board where there are ones in the matrix
				} else if (computerBoard[y][x] == 2) {
					printChar((x * 2) + 1, (y * 2) + 2, 'X'); //Places a "hit" on the board where there are twos in the matrix
				} else if (computerBoard[y][x] == 3) {
					printChar((x * 2) + 1, (y * 2) + 2, '*'); //Places a "miss" on the board where there are threes in the matrix
				}

				mvprintw(0, 3, "AI 2 WATERS");
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
	updateBoard(1);
	clearString();
	mvprintw((boardRows * 2) + 5, 0, "AI 1 fired a missile at AI 2");
	refresh();
	usleep(sleepTimeBetweenMovesInMicroseconds);

	int hit = -1;
	int badCoordinate = 1;
	int horizontalCoordinate = -1;
	int verticalCoordinate = -1;

	while (badCoordinate) {
		horizontalCoordinate = rand() % boardColumns;
		verticalCoordinate = rand() % boardRows;

		if (computerBoard[verticalCoordinate][horizontalCoordinate] != 2 && computerBoard[verticalCoordinate][horizontalCoordinate] != 3) {
			badCoordinate = 0; //If the random coordinate has already been chosen before, then choose another. Keep choosing until it's either a hit or a miss
		}
	}

	if (computerBoard[verticalCoordinate][horizontalCoordinate] == 0) {
		computerBoard[verticalCoordinate][horizontalCoordinate] = 3; //Sets the matrix to indicate a miss if you selected water
		hit = 0;

		updateBoard(1);

		clearString();
		mvprintw((boardRows * 2) + 5, 0, "AI 1 missed AI 2.");
		refresh();
		return 0;
	} else if (computerBoard[verticalCoordinate][horizontalCoordinate] == 1) {
		computerBoard[verticalCoordinate][horizontalCoordinate] = 2; //Sets the matrix to indicate a hit if you selected a boat
		hit = 1;

		updateBoard(1);

		clearString();
		mvprintw((boardRows * 2) + 5, 0, "AI 1 hit AI 2!");
		refresh();
		return 1;
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
	mvprintw((boardRows * 2) + 5, 0, "AI 2 fired a missile at AI 1");
	refresh();
	usleep(sleepTimeBetweenMovesInMicroseconds);

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
		mvprintw((boardRows * 2) + 5, 0, "AI 2 missed AI 1.");
		refresh();
		return 0;
	} else if (playerBoard[verticalCoordinate][horizontalCoordinate] == 1) {
		playerBoard[verticalCoordinate][horizontalCoordinate] = 2; //Sets the matrix to indicate a hit if you selected a boat
		hit = 1;

		updateBoard(0);

		clearString();
		mvprintw((boardRows * 2) + 5, 0, "AI 2 hit AI 1!");
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

/*
* Updates the timer based on a starting time
*
* @param int startTime - The time to count from
* @return void
*/
void updateTime(int startTime) {
	mvprintw(boardRows + 4, (boardColumns * 2) + 7, "Days:\t         ");
	mvprintw(boardRows + 5, (boardColumns * 2) + 7, "Hours:\t         ");
	mvprintw(boardRows + 6, (boardColumns * 2) + 7, "Minutes:\t         ");
	mvprintw(boardRows + 4, (boardColumns * 2) + 7, "Days:\t%d", (time(0) - startTime) / 60 / 60 / 24);
	mvprintw(boardRows + 5, (boardColumns * 2) + 7, "Hours:\t%d", ((time(0) - startTime) / 60 / 60) % 24);
	mvprintw(boardRows + 6, (boardColumns * 2) + 7, "Minutes:\t%d", ((time(0) - startTime) / 60) % 60);
}

/*
* Finds the number of hits on a given board
*
* @param int whichBoard - 0 finds the number of hits on playerBoard, 1 finds the number of hits on computerBoard
* @return int - a number between 0 and 6 that represents the number of hits on the given board
*/
int returnScore(int whichBoard) {
	int score = 0;

	for (int i = 0; i < boardRows; i++) {
		for (int j = 0; j < boardColumns; j++) {
			if (whichBoard == 0) {
				if (playerBoard[i][j] == 2) {
					score++;
				}
			} else if (whichBoard == 1) {
				if (computerBoard[i][j] == 2) {
					score++;
				}
			}
		}
	}

	return score;
}
