#include "stdafx.h"
#include "Sudoku.h"
#include <iostream>
#include<vector>
#include<set>

Sudoku::Sudoku(int size) : n(size), cellSize((int)sqrt(size))
{
	for (int i = 1; i <= n; i++)
	{
		setOfPossibleValues.insert(i);
	}
	// declare a square matrix of size n*n
	givenEntries = new int*[n];
	for (int i = 0; i < n; ++i)
		givenEntries[i] = new int[n];
	// init array = 0
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			givenEntries[i][j] = 0;
		}
	}

	/*
	int number = 0;
	std::cout << "Input number of given entries: ";
	std::cin >> number;
	int x, y;
	int value;
	for (size_t i = 0; i < number; i++)
	{
		std::cout << "Enter an entry's position: ";
		std::cin >> x >> y;
		std::cout << "Value: ";
		std::cin >> value;
		givenEntries[x][y] = value;
	}*/

	// for n = 4
	/*int numberOfEntriesOnEachRow[4] = { 3,2,3,3 };
	int columnPositionOfEntriesOnEachRow[11] = { 0,1,3,0,2,1,2,3,0,2,3 };
	int value[11] = { 1,3,4,4,3,1,4,2,2,1,3 };*/

	/*int numberOfEntriesOnEachRow[4] = { 3,2,2,4 };
	int columnPositionOfEntriesOnEachRow[11] = { 0,1,3,0,2,1,2,0,1,2,3 };
	int value[11] = { 1,3,4,4,3,1,4,2,4,1,3 };*/

	/*int numberOfEntriesOnEachRow[4] = { 1,1,1,1 };
	int columnPositionOfEntriesOnEachRow[4] = { 3,2,3,0 };
	int value[4] = { 1,2,3,3 };*/

	/*int numberOfEntriesOnEachRow[4] = { 4,4,4,4 };
	int columnPositionOfEntriesOnEachRow[16] = { 0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3 };
	int value[16] = { 1,3,2,4,4,2,3,1,3,1,4,2,2,4,1,3 };*/

	// for n = 9
	/*int numberOfEntriesOnEachRow[9] = { 4,2,0,4,3,4,2,5,7 };
	int columnPositionOfEntriesOnEachRow[50] = {1,3,5,7,2,6,2,3,5,6,0,4,8,0,3,5,8,0,8,0,2,4,6,8,0,1,3,4,5,7,8};
	int value[50] = { 4,2,9,8,9,4,2,5,6,8,5,8,3,6,7,2,4,7,8,8,4,1,5,6,9,5,8,2,4,3,1 };*/

	/*int numberOfEntriesOnEachRow[9] = { 4,4,1,2,6,1,4,7,3};
	int columnPositionOfEntriesOnEachRow[33] = { 0,2,6,8,0,3,5,8,4,0,8,0,1,3,5,7,8,4,2,3,5,6,0,2,3,4,5,6,8,3,4,5 };
	int value[33] = { 0,2,6,9,3,4,9,8,1,2,5,5,1,8,2,3,7,4,1,9,3,7,9,4,7,2,5,8,1,1,6,4 };*/
	
	int numberOfEntriesOnEachRow[9] = { 0,0,0,0,0,0,0,0,0 };
	int columnPositionOfEntriesOnEachRow[1];
	int value[1];

	int pos = 0;
	int count;
	for (size_t i = 0; i < n; i++)
	{
		// assign the i-th row of givenEntries
		for (count = pos; count < pos + numberOfEntriesOnEachRow[i]; count++)
		{
			givenEntries[i][columnPositionOfEntriesOnEachRow[count]] = value[count];
		}
		pos = count;
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (givenEntries[i][j] == 0) remainingEntries.insert(std::pair<int, int>(i, j)); // this multimap contains all unassigned entries
		}
	}

	/*std::cout << "Remaining entries: ";
	for (std::map<int, int>::iterator it = remainingEntries.begin(); it != remainingEntries.end(); it++) {
		std::cout << "(" << it->first << ", " << it->second << ") ";
	}
	std::cout << "\n";*/
}


Sudoku::~Sudoku()
{
	for (int i = 0; i < n; ++i) {
		delete[] givenEntries[i];
	}
	delete[] givenEntries;
}

Sudoku::Sudoku(const Sudoku& other) {
	n = other.n;
	int** givenEntries = new int*[n];
	for (int i = 0; i < n; ++i)
		givenEntries[i] = new int[n];

	for (int i = 0; i < n; ++i)
		for (size_t j = 0; j < n; j++)
		{
			givenEntries[i][j] = other.givenEntries[i][j];
		}
}

Sudoku& Sudoku::operator=(const Sudoku& rhs) {
	if (this == &rhs) return *this;
	n = rhs.n;
	for (int i = 0; i < n; ++i)
		for (size_t j = 0; j < n; j++)
		{
			givenEntries[i][j] = rhs.givenEntries[i][j];
		}
	return *this;
}

/*
	Return options for an entry.
*/
std::set<int> Sudoku::optionsForAnEntry(int x, int y) {
	std::set<int> result = setOfPossibleValues;
	// candiates according to row
	for (size_t j = 0; j < n; j++)
		if (givenEntries[x][j] != 0) result.erase(givenEntries[x][j]);
	// candiates according to col
	for (size_t i = 0; i < n; i++)
		if (givenEntries[i][y] != 0) result.erase(givenEntries[i][y]);
	// candiates according to cell
	int cellId = getCellId(x, y);
	int row = cellId / cellSize;
	int col = (cellId - cellSize*row);
	for (size_t i = row*cellSize; i < row*cellSize + cellSize; i++)
	{
		for (size_t j = col*cellSize; j < col*cellSize + cellSize; j++)
		{
			if (givenEntries[i][j] != 0) result.erase(givenEntries[i][j]);
		}
	}
	return result;
}

static int count = 0;

/*
	The best entry to try. That entry is found from the set of remaining unassigned entries of the matrix.
	bestSetOfOpts: set of options for the best candidate
*/
void Sudoku::bestCandidate(int* x, int* y,std::set<int>* bestSetOfOpts) {
	size_t minOptions = n + 1;
	std::set<int> tmp;
	
	for (std::multimap<int, int>::iterator it = remainingEntries.begin(); it != remainingEntries.end(); it++) {
		tmp = optionsForAnEntry(it->first, it->second);
		if (tmp.size() < minOptions) {
			minOptions = tmp.size();
			*bestSetOfOpts = tmp;
			*x = it->first;
			*y = it->second;
		}
	}
	/*std::cout << "Best candidiate by the " << count++ << " try: " << *x << " " << *y << "\n";
	std::cout << "Options: ";
	for (std::set<int>::iterator it = bestSetOfOpts->begin(); it != bestSetOfOpts->end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << "\n";*/
}

bool Sudoku::tryEntry(int x, int y,std::set<int> opts) {
	if ((remainingEntries.size() == 1) && (opts.size() == 1)) {
		givenEntries[x][y] = *opts.begin();
		return true;
	}
	int* newX = new int();
	int* newY = new int();
	std::set<int>* newOpts = new std::set<int>();
	// sequentially try each options in opts
	for (std::set<int>::iterator it = opts.begin(); it != opts.end(); it++) {
		givenEntries[x][y] = *it;
		deleteEntry(x, y);
		bestCandidate(newX, newY, newOpts);
		if (!tryEntry(*newX, *newY, *newOpts)) {
			givenEntries[x][y] = 0;
			remainingEntries.insert(std::pair<int, int>(x, y));
		}
		else return true;
	}
	return false;
}

/*
	Delete an entry determined by (x,y) from the set of remaining unassigned entries.
*/
void Sudoku::deleteEntry(int x, int y) {
	auto ret = remainingEntries.equal_range(x);
	for (std::multimap<int, int>::iterator it = ret.first; it != ret.second; it++) {
		if (it->second == y) {
			remainingEntries.erase(it);
			break;
		}
	}
}

/*
	Given an entry's position in the matrix.
	Return which cellId the given entry belongs to.
*/
int Sudoku::getCellId(int x, int y) {
	return (x / cellSize)*cellSize + y / cellSize;
}

void Sudoku::printMatrix() {
	// print matrix
	for (int i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++)
		{
			std::cout << givenEntries[i][j] << " ";
		}
		std::cout << "\n";
	}
}

bool Sudoku::testSolution() {
	// check rows
	std::set<int> values;
	for (int i = 0; i < n; i++) {
		values.clear();
		for (size_t j = 0; j < n; j++)
		{
			values.insert(givenEntries[i][j]);
		}
		if (values.size() != n) return false;
	}
	// check cols
	for (int j = 0; j < n; j++) {
		values.clear();
		for (size_t i = 0; i < n; i++)
		{
			values.insert(givenEntries[i][j]);
		}
		if (values.size() != n) return false;
	}
	// check cells
	for (int cellId = 0; cellId < n; cellId++) {
		values.clear();
		int row = cellId / cellSize;
		int col = (cellId - cellSize*row);
		for (size_t i = row*cellSize; i < row*cellSize + cellSize; i++)
		{
			for (size_t j = col*cellSize; j < col*cellSize + cellSize; j++)
			{
				values.insert(givenEntries[i][j]);
			}
		}
		if (values.size() != n) return false;
	}
	return true;
}

void Sudoku::solveSudoku() {
	std::cout << "Suduko problem for n = " << n << ":\n";
	printMatrix();
	if (remainingEntries.size() == 0) {
		if (testSolution())
			std::cout << "Solution correct!\n";
		else
			std::cout << "Solution NOT correct!\n";
	}
	else {
		int* x = new int();
		int* y = new int();
		std::set<int>* opts = new std::set<int>();
		bestCandidate(x, y, opts);
		if (tryEntry(*x, *y, *opts)) {
			//OK
			std::cout << "Solution: \n";
			printMatrix();
			if (testSolution())
				std::cout << "Solution correct!\n";
			else
				std::cout << "Solution NOT correct!\n";
		}
		else {
			// Not OK
			std::cout << "No solution found!\n";
		}
	}
}

