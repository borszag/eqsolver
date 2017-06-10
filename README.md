# eqsolver
Linear equation system solver, based on Cramer's rule.

It is not recommended to use for large systems due to the slow algorithm.

The input is the command line arguments. One has to write the augmented matrix by columns.

Example.
The system of equations is the following:

[1 3 | 5]

[2 4 | 6]

The correct way to use the compiled binary to solve the above system:
./eqsolver 1 2 3 4 5 6
