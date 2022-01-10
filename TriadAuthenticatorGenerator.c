#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Generates authentication tables used in triad authentication.
 * These tables are used in much the same way as a one-time-pad.
 *
 * Triad authentication how-to:
 * Authentication is two-way, both parties should authenticate each other
 * with different triads. Pick 3 characters in the alphabet. The first
 * character is either A/B/C, which determines whether you should use table
 * Alpha, Bravo, or Charlie. The second character determines the row you
 * should look in. Finally, look for the third character in that row, then
 * send the other party the character under it. They should be able to
 * follow that same algorithm, and if you both come to the same character,
 * you can be reasonably confident that you both have the same randomized
 * tables.
 *
 * For more context, see
 * https://en.wikipedia.org/wiki/Challenge%E2%80%93response_authentication
*/

// Globals
char table[27][26];

// Stubs
void resetTable(void);
void printTable(void);
void randomizeTable(int seed);

// Main
void main() {
	resetTable();

	printf("[ ALPHA ]\n");
	srand(time(0) + rand());
	randomizeTable(time(0));
	printTable();

	printf("[ BRAVO ]\n");
	srand(time(0) + rand());
	randomizeTable(time(0));
	printTable();

	printf("[ CHARLIE ]\n");
	srand(time(0) + rand());
	randomizeTable(time(0));
	printTable();
}

// Reset table to standard alphabet
void resetTable(void) {
	for (int i = 0; i < 28; i++) {
		for (int j = 0; j < 26; j++) {
			table[i][j] = (char)(65 + j);
		}
	}
}

// Prints the table
void printTable(void) {
	for (int i = 0; i < 29; i++) {
		if (i > 0 && i <= 26) {
			printf("%c ", (char)(65 + (i - 1)));
		} else {
			printf("  ");
		}

		for (int j = 0; j < 26; j++) {
			if (i == 0) {
				printf("%c ", (char)(65 + j));
			} else {
				printf("%c ", table[i][j]);
			}
		}
		printf("\n");
	}
}

// (helper) Swap two characters in a row i
void swap(int i, int j1, int j2) {
	char tmp;
	tmp = table[i][j1];
	table[i][j1] = table[i][j2];
	table[i][j2] = tmp;
}

// Randomize the contents of the table
void randomizeTable(int seed) {
	srand(seed);

	for (int i = 0; i < 28; i++) {
		for (int j = 0; j < 26; j++) {
			swap(i, j, (rand() % 26));
		}
	}
}

