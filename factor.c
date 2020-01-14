#include <stdio.h>

/* A proof of concept factoring program; not
 * very efficient or optimized.
 *
 * Generically brute force factors an integer between 0 < n < 18446744073709551616
 */
void main(void) {
        unsigned long long int i = 2;
        unsigned long long int input = 0;
        unsigned long long int max = 18446744073709551615;

        printf("Enter an integer (whole number > 0) to factor: ");
        scanf("%llu", &input);

        if (input == max) {
                printf("Error: max bit size is %d\n", (sizeof(unsigned long long int)*8)-1);
                return;
        }

        printf("The factors of %llu are:\n\n", input);
        fflush(stdout);

        while (i <= input) {
                while ((input % i) == 0) {
                        printf("%llu ", i);
                        input = input / i;
                        fflush(stdout);
                }

                i++;
        }
        printf("\n");
}
