# DC Lab Internal Test Programs

C programs for the DC lab CIE1/internal test, organized according to the
[lab program list](DC%20lab%20program%20list%20for%20Test.docx). Part A covers
shared-memory parallel programming with OpenMP; Part B covers communication
between processes with MPI.

The repository contains 12 standalone programs. Each source file has its own
`main()` and must be compiled separately.

## Repository layout

- [Part_A](Part_A/): seven OpenMP programs, with [compilation commands, practice inputs, and study notes](Part_A/README.md).
- [Part_B](Part_B/): five MPI programs, with [compilation commands, expected results, and study notes](Part_B/README.md).
- [DC lab program list for Test.docx](DC%20lab%20program%20list%20for%20Test.docx): original test requirements.

## Program list

### Part A — OpenMP

| Question | Requirement | Source |
| --- | --- | --- |
| 1(a) | Find the sum of array elements using parallel execution. | [01a_array_sum.c](Part_A/01a_array_sum.c) |
| 1(b) | Divide loop iterations into static chunks of two using `OMP_SCHEDULE=static,2`; read the iteration count and print which thread executes each iteration. | [01b_static_schedule.c](Part_A/01b_static_schedule.c) |
| 2 | Sort an array of `n` elements using sequential merge sort and parallel merge sort with sections; record the execution-time difference. | [02_merge_sort.c](Part_A/02_merge_sort.c) |
| 3(a) | Calculate `n` Fibonacci numbers using tasks. | [03a_fibonacci_tasks.c](Part_A/03a_fibonacci_tasks.c) |
| 3(b) | Find the maximum element in an array. | [03b_array_maximum.c](Part_A/03b_array_maximum.c) |
| 4 | Estimate pi using the Leibniz series, remove the loop-carried dependency to parallelize it, and record serial and parallel execution times. | [04_pi_series.c](Part_A/04_pi_series.c) |
| 5 | Find prime numbers from 1 to `n` using the parallel-for directive; record serial and parallel execution times. | [05_prime_numbers.c](Part_A/05_prime_numbers.c) |

The pi series is `pi = 4 * sum((-1)^k / (2*k + 1))` for `k = 0` to infinity.
The program approximates it using a finite number of terms.

### Part B — MPI

| Question | Requirement | Source |
| --- | --- | --- |
| 1 | Distribute data among processes with `MPI_Scatter` and collect results at root with `MPI_Gather`. | [01_scatter_gather.c](Part_B/01_scatter_gather.c) |
| 2 | Demonstrate `MPI_Reduce` and `MPI_Allreduce` with `MPI_MAX`, `MPI_MIN`, `MPI_SUM`, and `MPI_PROD`. | [02_reduce_allreduce.c](Part_B/02_reduce_allreduce.c) |
| 3 | Demonstrate point-to-point communication with `MPI_Send`/`MPI_Recv` and one-to-all communication with `MPI_Bcast`. | [03_send_recv_bcast.c](Part_B/03_send_recv_bcast.c) |
| 4 | Send “Bangalore” from process 1, “Ramaiah Institute of Technology” from process 2, and “Information Science and Engineering” from process 3 to root. | [04_send_strings.c](Part_B/04_send_strings.c) |
| 5 | Synchronize four processes using `MPI_Barrier` while calculating squares of different numbers. | [05_barrier_squares.c](Part_B/05_barrier_squares.c) |

## Prerequisites

- A C compiler with OpenMP support. The Part A examples use `gcc-16` with
  `-fopenmp`; substitute your installed OpenMP-capable GCC executable if needed.
- An MPI implementation providing `mpicc` and `mpirun` for Part B.

## Quick start

Run these commands from the repository root after the required tools are installed.

### OpenMP array sum

```sh
gcc-16 -fopenmp Part_A/01a_array_sum.c -o /tmp/dc_array_sum
OMP_NUM_THREADS=4 /tmp/dc_array_sum
```

Enter `5` for the array size, followed by `1 2 3 4 5`. The expected sum is `15`.

### OpenMP static scheduling

```sh
gcc-16 -fopenmp Part_A/01b_static_schedule.c -o /tmp/dc_schedule
OMP_NUM_THREADS=2 OMP_SCHEDULE=static,2 /tmp/dc_schedule
```

Enter `4` iterations for the example in the lab list. Thread 0 executes
iterations 0 and 1; thread 1 executes iterations 2 and 3. Printed lines can
appear in a different order.

### MPI scatter and gather

```sh
mpicc Part_B/01_scatter_gather.c -o /tmp/dc_scatter_gather
mpirun -np 4 /tmp/dc_scatter_gather
```

No keyboard input is required for Part B. In this example, root distributes
`1 2 3 4` and gathers the squares `1 4 9 16`.

## Execution notes

- Use four MPI processes for all lab examples. Programs B4 and B5 require
  exactly four; B3 needs at least two.
- Rank 0 is the root process in these MPI examples. Output from different
  processes may appear in any order; a barrier does not order printed lines.
- If Open MPI reports insufficient slots, add `--oversubscribe` to `mpirun`.
- Execution times vary with input size, thread count, and machine load.
  Parallel versions can be slower for small inputs. Merge sort reports
  serial time minus parallel time, so a negative difference is valid.
- See the [Part A guide](Part_A/README.md) and [Part B guide](Part_B/README.md)
  for commands for every program, input limits, expected results, and concepts
  to revise before the test.
