#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

typedef struct {
	int lin, col;
	TElem value;
} MatrixElement;

class MatrixIterator;

class Matrix {
	friend class MatrixIterator;
private:
	//TODO - Representation
	int nr_lines;
	int nr_columns;
	int size;
	int capacity;
	MatrixElement* elems;

	//returns the position of the element (i, j) if this was already initialized
	//if the position was not initialized, it will return the position where it should be 
	int searchPosition(int i, int j) const;

	//check if the position (i, j) is valid in the matrix
	//return true if the position is valid, false otherwise
	bool isValidPosition(int i, int j) const;

	//check if two Matrix Elements have a relation between them
	//returns true if the coordinates of element1 < coordinates of element2, false otherwise
	bool relation(MatrixElement element1, MatrixElement element2) const;

	//check if two Matrix Elements has the same line and column
	//returns true if they have the same coordinates, false otherwise
	bool equals(MatrixElement element1, MatrixElement element2) const;

public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	MatrixIterator iterator(int column) const;
};
