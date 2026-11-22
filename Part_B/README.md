# Part B — MPI

These five standalone C programs match the Part B numbering in the lab list.
Compile with `mpicc`, then launch with `mpirun`. Run these commands from this
directory. Each file has its own `main()`.

```sh
cd "/Users/Nithish/Desktop/7th Sem/DC/Internal Lab Test/Part_B"
```

| Question | Compile | Run |
| --- | --- | --- |
| 1 Scatter and Gather | `mpicc 01_scatter_gather.c -o scatter_gather` | `mpirun -np 4 ./scatter_gather` |
| 2 Reduce and Allreduce | `mpicc 02_reduce_allreduce.c -o reduce_allreduce` | `mpirun -np 4 ./reduce_allreduce` |
| 3 Send, Recv and Bcast | `mpicc 03_send_recv_bcast.c -o send_recv_bcast` | `mpirun -np 4 ./send_recv_bcast` |
| 4 Send strings to root | `mpicc 04_send_strings.c -o send_strings` | `mpirun -np 4 ./send_strings` |
| 5 Barrier and squares | `mpicc 05_barrier_squares.c -o barrier_squares` | `mpirun -np 4 ./barrier_squares` |

No keyboard input is needed. `-np 4` launches four processes with ranks 0–3.
Rank 0 is the root in these examples. If Open MPI reports insufficient slots on
your machine, use `mpirun --oversubscribe -np 4 ./program_name`.

## Expected results with four processes

| Program | Expected result |
| --- | --- |
| Scatter/Gather | Rank 0 starts with `1 2 3 4`. Each process receives one number and squares it. Root gathers `1 4 9 16`. |
| Reduce/Allreduce | Each process contributes `rank + 1`. MAX = 4, MIN = 1, SUM = 10, PROD = 24. Reduce prints at root; Allreduce prints at every process. |
| Send/Recv/Bcast | Rank 0 sends `10` to rank 1. Then rank 0 broadcasts `100` to all four processes, including itself. |
| Strings | Root prints `Bangalore`, `Ramaiah Institute of Technology`, and `Information Science and Engineering`, received from ranks 1, 2 and 3. |
| Barrier | After all four processes finish calculating, each prints its square: 1, 4, 9 or 16. |

## What to remember for the test

Every MPI program follows this outline:

```c
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
/* communication and calculation */
MPI_Finalize();
```

| Operation | Meaning / argument order |
| --- | --- |
| `MPI_Scatter` | Root distributes equal-sized pieces. Send buffer, send count per process, send type, receive buffer, receive count, receive type, root, communicator. |
| `MPI_Gather` | Root collects pieces in rank order. Send buffer, send count, send type, receive buffer, receive count per process, receive type, root, communicator. |
| `MPI_Reduce` | Combine values at root: send buffer, receive buffer, count, type, operation, root, communicator. |
| `MPI_Allreduce` | Combine values at every process. Same as Reduce but without a root argument. |
| `MPI_Send` | Buffer, count, type, destination rank, tag, communicator. |
| `MPI_Recv` | Buffer, capacity, type, source rank, tag, communicator, status. Use `MPI_STATUS_IGNORE` when status is unnecessary. |
| `MPI_Bcast` | Buffer, count, type, root, communicator. All processes call it. |
| `MPI_Barrier` | Communicator only. Wait until every process reaches the barrier. |

Remember `&value` for a scalar; use the array name directly for arrays and strings.
String sends use `strlen(message) + 1` to include the terminating null character.
The tag in matching Send and Recv calls is `0` in these examples.

Every process must call each collective operation in the same order. Only root
uses the full Scatter send buffer or Gather receive buffer, and only root reads
the result of Reduce. Allreduce provides its result to every process.

Output from different processes can appear in any order. Barrier synchronizes
processes; it does not sort output lines. The strings program receives and prints
at root in source order to make its output easier to read.

Programs 4 and 5 require exactly four processes. Program 3 needs at least two.
Program 1 supports up to 100 processes. Program 2 supports up to 12 because the
product is `size!` and must fit in a 32-bit `int`. Use four for all lab examples.
