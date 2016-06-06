#pragma once
#include<map>
#include<set>

class Sudoku
{
public:
	Sudoku(int);	// constructor
	~Sudoku();
	Sudoku(const Sudoku& other); //copy constructor
	Sudoku& operator=(const Sudoku& rhs); // TODO: mising implementation
	void solveSudoku();
private:
	int n;
	int cellSize;	// the length of a side of a square cell
	int** givenEntries;
	std::set<int> setOfPossibleValues;	// 
	std::multimap<int, int> remainingEntries;
	std::set<int> optionsForAnEntry(int, int);
	void nextTurn(int*, int*);
	int getCellId(int, int);
	void bestCandidate(int*, int*,std::set<int>*);
	bool tryEntry(int, int,std::set<int>);
	void printMatrix();
	void deleteEntry(int, int);
	bool testSolution();
};

