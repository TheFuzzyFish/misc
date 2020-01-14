#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Asks a user to guess a randomly generated number between 1 and 10
int check(double guess) {
	int number;

	/* Generate random number */
	srand(time(0));
	srand(rand());
	number = (rand() % 10) + 1;

	/* Sanity checks */
	if (guess > 10 ) {
		printf("%d isn't between 1 and 10!\n", guess);
		return 0;
	}
	if (guess < 1 ) {
		printf("%d isn't between 1 and 10!\n", guess);
		return 0;
	}

	/* Determine whether the guess is correct */
	if ( guess == number ) {
		printf("Wow, the number WAS %d! Good job!\n", number);
		return 0;
	}
	else {
		printf("Nope, %d is not correct. The number I was thinking of was actually %d. Sorry!\n", guess, number);
		return 0;
	}
}

void main(void) {
	/* Define variables */
	int guess;

	/* Get user input */
	printf("I'm thinking of a number between 1 and 10. Take a guess: "); // This is a lie, we haven't actually generated the random number yet, but shhhh
	scanf("%d", &guess);

	check(guess);
}
