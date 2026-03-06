#include <stdio.h>
#include <gmp.h>
#include <omp.h>
#include <time.h>

void parallel_fib(unsigned long n, mpz_t a, mpz_t b) {
    if (n == 0) {
        mpz_set_ui(a, 0);
        mpz_set_ui(b, 1);
        return;
    }

    mpz_t f_k, f_k1, t1, t2;
    mpz_inits(f_k, f_k1, t1, t2, NULL);

    parallel_fib(n >> 1, f_k, f_k1);

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            mpz_mul_2exp(t1, f_k1, 1);
            mpz_sub(t1, t1, f_k);
            mpz_mul(t1, t1, f_k); 
        }
        #pragma omp section
        {
            mpz_t f_k_sq, f_k1_sq;
            mpz_inits(f_k_sq, f_k1_sq, NULL);
            mpz_mul(f_k_sq, f_k, f_k);
            mpz_mul(f_k1_sq, f_k1, f_k1);
            mpz_add(t2, f_k1_sq, f_k_sq);
            mpz_clears(f_k_sq, f_k1_sq, NULL);
        }
    }

    if (n & 1) {
        mpz_set(a, t2);
        mpz_add(b, t1, t2);
    } else {
        mpz_set(a, t1);
        mpz_set(b, t2);
    }

    mpz_clears(f_k, f_k1, t1, t2, NULL);
}

int main() {
    unsigned long n;
    if (scanf("%lu", &n) != 1) return 1;

    mpz_t result, next;
    mpz_inits(result, next, NULL);

    double start = omp_get_wtime();
    parallel_fib(n, result, next);
    double end = omp_get_wtime();

    FILE *f = fopen("fibo.txt", "w");
    if (f) {
        gmp_fprintf(f, "%Zd\n", result);
        fclose(f);
    }

    printf("Time: %f s\n", end - start);
    printf("Digits: %zu\n", mpz_sizeinbase(result, 10));

    mpz_clears(result, next, NULL);
    return 0;
}
