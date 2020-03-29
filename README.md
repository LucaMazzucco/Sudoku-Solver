# Sudoku-Solver
A C Sudoku Solver

The Sudoku solver is developed in C language.
Two different solving function has been developed.

1 ) EXCLUSION_SOLVE()
Solving part of sudoku with smart logic, as much as possible,
reducing the overload of the sequent brutal solving solution.

This exclusion_solve can teoritically let the sudoku semi-solved, for this reason a brutal solver is developed and can be called after this.
The brutal solver is always able to solve the sudoku in any situation.

The exclusion solve use a 3 dimensional matrix called "exclusion" for saving for each square the possible values assignable.
Every time a new value is added into the sudoku scheme, this matrix is reevaluated.

2 ) BRUTAL_SOLVE()
The brutal solver develop a powerset, where every combination of numbers for the missing values is tested up to find the correct one.
The function is developed as a recursive function.
