#include <stdio.h>
#include <ctype.h>
// Accepts a ciphered input from the user, then iterates it through every possible Caesar Cipher.
// Just sift through the output and look for proper words.
void main(void) {
	char str[1024];
	int i, x;

	/* Accepts user input */
	printf("====================\nCaesar Cipher Cracker\nWritten by Zachary Kline\n====================\n");
	printf("Please enter a ciphered string (max 1024 characters): ");
	scanf("%[^\n]s", str); // The "[^\n] ensures that spaces are scanned in as well, so that you can paste in a whole sentence
	printf("\n");

	for (i = 1; i <= 26; ++i) {
		for (x = 0; str[x] != '\0'; ++x) {
			/*
			I had to make 2 separate if statements for
			whether the character was between a-z or A-Z
			so that we didn't accidentally start overflowing
			into numbers or symbols. This also had the added
			benefit of leaving numbers and symbols from the
			input untouched in the output.
			*/
			if (str[x] >= 'a' && str[x] <= 'z') {
				str[x] = str[x] + 1;
				/*
				Next if statement corrects the output in
				case we accidentally fell outside of the
				alphabet by adding 1
				*/
				if (str[x] > 'z') {
					str[x] = str[x] + 'a' - 'z' - 1;
				}
			}
			/*
			This next if statement is just a copy of
			the previous one, but for the capital alphabet
			*/
			if (str[x] >= 'A' && str[x] <= 'Z') {
				str[x] = str[x] + 1;
				if (str[x] > 'Z') {
					str[x] = str[x] + 'A' - 'Z' - 1;
				}
			}
		}
		printf("+%d:\t%s\n", i, str);
	}
}
