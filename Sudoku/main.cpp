// Sudoku.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Sudoku.h"
#include<iostream>
#include<ctime>

int main()
{
	Sudoku s(9);
	clock_t begin = clock();
	s.solveSudoku();
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "This problem is solved in " << elapsed_secs << " seconds.\n";
	// new commit from ubuntu
    return 0;
}

