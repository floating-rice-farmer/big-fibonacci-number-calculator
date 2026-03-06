# Very large fibonacci number calculator

A high-performance Fibonacci calculator using the GNU Multiple Precision (GMP) library.

## How It Works

Calculating Fibonacci numbers at scale requires more than just a simple loop. This program uses several layers of optimization to achieve maximum speed:

1. **Fast Doubling Algorithm**: Instead of calculating every number in the sequence (F1, F2, F3...), the program uses the Fast Doubling identities:
   - $F_{2k} = F_k(2F_{k+1} - F_k)$
   - $F_{2k+1} = F_{k+1}^2 + F_k^2$
   This allows the program to reach the $N$-th index in $O(\log N)$ steps.

2. **Arbitrary Precision (GMP)**: Standard integers (64-bit) overflow at $F_{93}$. GMP uses "limbs" (arrays of 64-bit integers) to represent numbers with millions of digits.

3. **Multiplication Optimization**: For massive numbers, multiplication is the bottleneck. GMP automatically switches between:
   - **Karatsuba**: For medium numbers.
   - **Schönhage-Strassen (FFT)**: For massive numbers, treating large integers like signals to perform multiplication in $O(n \log n \log \log n)$ time.

## Performance
1. Basically the only bottleneck to this is your RAM, and nothing else.
2. Recommended maximum size is 1 billion, as anything above that:
  a. Your OS may terminate the process
  b. It will write a pretty substantial file to your disk

The unsigned long n used for the index is a 64-bit integer on your system. This means the theoretical maximum index you could request is $2^64−1$. However, you would run out of atoms in the known universe to store that number long before you reached it, so no need to worry about the maximum limit!

It's also multi core

## Compilation
`gcc -O3 -march=native -fopenmp fib.c -o fibo -lgmp`

## Usage
1. Run: `./fibo`
2. Enter index: (e.g., 1000000)
3. Output: View result in `fibo.txt`
