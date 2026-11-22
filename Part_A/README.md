# Part A — OpenMP

These seven standalone C programs match the Part A numbering in the lab list.
Run the commands from this directory. Each program has its own `main()`;
compile one source file at a time.

```sh
cd "/Users/Nithish/Desktop/7th Sem/DC/Internal Lab Test/Part_A"
export OMP_NUM_THREADS=4
```

Use `gcc-16` with `-fopenmp`. For example:

```sh
gcc-16 -fopenmp 01a_array_sum.c -o array_sum
./array_sum
```

| Question | File | Compile | Run |
| --- | --- | --- | --- |
| 1(a) Array sum | `01a_array_sum.c` | `gcc-16 -fopenmp 01a_array_sum.c -o array_sum` | `./array_sum` |
| 1(b) Static chunks of 2 | `01b_static_schedule.c` | `gcc-16 -fopenmp 01b_static_schedule.c -o schedule` | `OMP_NUM_THREADS=2 OMP_SCHEDULE=static,2 ./schedule` |
| 2 Merge sort using sections | `02_merge_sort.c` | `gcc-16 -fopenmp 02_merge_sort.c -o merge_sort` | `./merge_sort` |
| 3(a) Fibonacci using tasks | `03a_fibonacci_tasks.c` | `gcc-16 -fopenmp 03a_fibonacci_tasks.c -o fibonacci` | `./fibonacci` |
| 3(b) Maximum element | `03b_array_maximum.c` | `gcc-16 -fopenmp 03b_array_maximum.c -o maximum` | `./maximum` |
| 4 Pi using Leibniz series | `04_pi_series.c` | `gcc-16 -fopenmp 04_pi_series.c -o pi` | `./pi` |
| 5 Prime numbers | `05_prime_numbers.c` | `gcc-16 -fopenmp 05_prime_numbers.c -o primes` | `./primes` |

## Practice inputs and expected answers

For array questions, enter `n` first, then the `n` integers. Spaces and newlines
both work as input separators. Timing values vary on each run.

| Program | Input | Expected answer |
| --- | --- | --- |
| Sum | `5` then `1 2 3 4 5` | `Sum = 15` |
| Schedule | `8`, with 2 threads and `static,2` | Thread 0 handles 0, 1, 4, 5; thread 1 handles 2, 3, 6, 7 |
| Merge sort | `6` then `9 3 7 1 8 2` | Both arrays: `1 2 3 7 8 9` |
| Fibonacci | `10` | `0 1 1 2 3 5 8 13 21 34` |
| Maximum | `5` then `-8 -3 -10 -1 -6` | `Maximum = -1` |
| Pi | `1000000` | Both estimates approximately `3.141591653590` |
| Primes | `20` | `2 3 5 7 11 13 17 19`; both counts are 8 |

## What to remember for the test

| Program | Main idea to remember |
| --- | --- |
| Sum | Initialize `sum = 0`; use `parallel for reduction(+:sum)`. |
| Schedule | Use `schedule(runtime)` so `OMP_SCHEDULE=static,2` controls scheduling. Chunks of two iterations go to threads in round-robin order. |
| Merge sort | Divide, recursively sort, merge. Two `section` blocks sort the two halves independently. The sections finish before the final merge. |
| Fibonacci | `parallel` creates the team, `single` creates tasks once, `task` computes each term, `taskwait` waits. `firstprivate(i)` captures the correct term index. |
| Maximum | Initialize from `a[0]`; use `reduction(max:maximum)`. |
| Pi | Formula: `4 * sum((-1)^k / (2*k+1))`. In parallel, compute the sign from `k % 2` and use `reduction(+:sum)`. |
| Primes | Try divisors up to the square root. `i <= n / i` avoids overflow from `i*i`. Parallelize the candidate loop. |

The Fibonacci program creates one task per term and uses a small iterative helper
to calculate that term. It prints the first `n` terms starting at F(0) = 0.
The limit of 93 terms means the largest value is F(92), which fits in `long long`.

The scheduling output prints one iteration per line; its line order can vary.
`critical` keeps each print statement together. For the exact four-iteration
example in the question, run with two threads and enter `4`.

The merge sort uses two parallel sections at the top split, so it uses at most
two threads for sorting. Both versions start with the same unsorted input.
Its printed time difference is **serial time minus parallel time**.

Timing uses `omp_get_wtime()`. Parallel execution can take longer for small
inputs because starting threads and tasks takes time. Report the measured
times; a negative time difference is valid. Pi estimates can differ slightly
because threads add floating-point numbers in a different order.

Input limits keep the code short: array programs accept 1–1000 elements,
Fibonacci accepts 1–93 terms, and primes accepts 1–100000. Pi accepts a positive
`int` term count. Invalid input causes the program to return 1.
