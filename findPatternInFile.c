#include <stdio.h>
#include <string.h>

/* Globals */
int bufSize;

/* Stubs */
void roll(char buffer[], char nextChar);
long findSizeOfFile(char fileName[]);
int doMatch(char string1[], char string2[]);

/*
 * Analyzes input file to find patterns. No arguments necessary
 */
void main(int argc, char *argv[]) {
	// Get inputs
	char filename[1000];
	char pattern[1000];
	if (argc == 1) {
		printf("File to analyze: ");
		scanf("%s", filename);

		printf("Pattern to find in file: ");
		scanf("%s", pattern);
	} else if (argc == 3) {
		strcpy(filename, argv[1]);
		strcpy(pattern, argv[2]);
	} else {
		printf("ERROR: Arguments not recognized.\nRun as either `./findPatternInFile` or `./findPatternInFile input.txt pattern`\n");
		return;
	}

	// Initialize variables
	bufSize = strlen(pattern);
	char buffer[bufSize];
	long fileLength = findSizeOfFile(filename);
	FILE *fptr = fopen(filename, "r");

	// Sanity check
	if (fptr == NULL) {
		printf("Unable to open file. Are you sure you spelled it right?\n");
	} else if (strlen(pattern) == 0) {
		printf("Pattern was blank. Try entering a string you want to find in the file.\n");
	}

	// Load up the buffer with the first few chars of input file
	for (int i = 0; i < bufSize; i++) {
		buffer[i] = fgetc(fptr);
	}

	// Main loop, finds patterns until file end
	for (long i = 0; i < fileLength; i++) {
		if (doMatch(buffer, pattern)) {
			printf("Pattern match found at byte offset:\t%ld\n", i);
		}
		roll(buffer, fgetc(fptr)); // Shifts the buffer, adding next char to end
	}

	fclose(fptr);
}

/*
 * The rolling buffer algorithm, shifts all elements left and adds nextChar to end of buffer
 */
void roll(char buffer[], char nextChar) {
	// Shift all elements left 1
	for (int i = 0; i < bufSize; i++) {
		buffer[i] = buffer[i + 1];
	}

	// Add new element to end
	buffer[(bufSize) - 1] = nextChar;
}

/*
 * Returns the size of input file in bytes
 */
long findSizeOfFile(char fileName[]) {
	// Open file, seek until end is found
	FILE *fptr = fopen(fileName, "r");
	fseek(fptr, 0L, SEEK_END);

	// Close pointer, return end value
	long size = ftell(fptr);
	fclose(fptr);

	return size;
}

/*
 * Implemented my own strcmp() function to avoid scanning through the whole string, which would be unnecessary in this application.
 * Assumes string1 and string2 are the same length. If they are not, partial matches may return true if the end of the smaller string is reached before a mismatch is found
 * Returns 1 or 0 (true or false respectively)
*/
int doMatch(char string1[], char string2[]) {
	int isStringEnd = 0; // Boolean int isMatch = 1; // Boolean int ptr = 0; // Keeps track of iterations through both strings
	int ptr = 0; // Keeps track of iterative progress through both strings

	// Loop through both strings, comparing chars. If match is not found, return early.
	while (!isStringEnd) { // Break loop if either string1 or string2 ends
		if (string1[ptr] != string2[ptr]) {
			return 0; // You don't need to keep comparing the strings if a mismatch is already found. This is an optimization of the most common case
		} else if (string1[ptr] == '\0' || string2[ptr] == '\0') {
			isStringEnd = 1;
		}
		ptr++;
	}

	return isStringEnd; // Only return true if the strings have matched and at least one string ended
}
