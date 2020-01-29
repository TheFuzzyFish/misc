#include <stdio.h>
#include <math.h>

/*
 * Estimates an integral using Riemann Sums; gives you the ability to watch previous iterations get closer to the true answer
 * Replace the return line in function() with the equation of your choice.
 */

long double function(long double x) {
	return -pow(x,2) + 100; //This is the function that the sum is calculated for. You must change this at compile-time, as it can not be changed at run-time
}

void main(void) {
	unsigned long long int n; //The number of subintervals to use
	int a; //Lower bound
	int b; //Upper bound
	char iterative; //Boolean; determines whether or not the program will loop through all previous values of n, or just give you the approximation for the n you gave

	printf("\n===============================\nLeft-Hand Riemann Sum calculator\n===============================\n\n");

	printf("Left bound (a): ");
	scanf("%d", &a);
	printf("Right bound (b): ");
	scanf("%d", &b);
	printf("Number of subintervals (n < 18446744073709551616): ");
	scanf("%llu", &n);
	printf("Do you want to see all iterations leading up to your n? (y/n): ");
	scanf(" %c", &iterative);

	if (iterative == 'n') {
		unsigned long long int tmpn = n;
		long double area = 0;
		for (long double offset = 0; offset < b; offset += (b-a)/(long double)tmpn) {
			area += ((b-a)/(long double)tmpn) * function(a + offset);
		}

		printf("n = %llu; Area = %0.57Lf\n", tmpn, area);
	} else if (iterative == 'y') {
		for (unsigned long long int tmpn = 2; tmpn <= n; tmpn++) {
			long double area = 0;
			for (long double offset = 0; offset < b; offset += (b-a)/(long double)tmpn) {
				area += ((b-a)/(long double)tmpn) * function(a + offset);
			}

			printf("n = %llu; Area = %0.57Lf\n", tmpn, area);
		}
	} else {
		printf("Error: did not recognize answer to last question: %c", iterative);
	}
}
