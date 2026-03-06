#include <stdio.h>
#include <gmp.h>
#include <time.h>

// For calculating unreasonably high fibonacci numbers for whatever reason

int main() {
    unsigned long n;
    printf("Enter Fibonacci index: ");
    if (scanf("%lu", &n) != 1) return 1;

    mpz_t result;
    mpz_init(result);

    clock_t start = clock();
    mpz_fib_ui(result, n);
    clock_t end = clock();

    FILE *f = fopen("fibo.txt", "w");
    if (f == NULL) {
        fprintf(stderr, "Error: Could not open fibo.txt for writing.\n");
        mpz_clear(result);
        return 1;
    }

    gmp_fprintf(f, "%Zd\n", result);
    fclose(f);

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    size_t digits = mpz_sizeinbase(result, 10);

    printf("\nSuccess! Result written to fibo.txt\n");
    printf("Digits: %zu\n", digits);
    printf("Calculation time: %f seconds\n", time_spent);

    mpz_clear(result);
    return 0;
}
