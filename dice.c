#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Standard dice roller; takes entropy from a psuedorandom number based on the current unix timestamp
int main(void) {
	int x;
	int y;
	int seed;

	printf("Rolling dice...\n");
	srand(time(0));
	srand(rand()); // This step is completely unnecessary for 99.9% of use cases. We're simply modifying the algorithm used to generate the random number by changing the seed to a random number based on time() so that all subsequent calls of rand() is not based merely on time().
	x = (rand() % 6) + 1;
	y = (rand() % 6) + 1;
	printf("Your dice roll resulted in %d and %d\n", x, y);

	return 0;
}
