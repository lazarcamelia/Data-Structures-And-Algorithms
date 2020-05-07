#include <exception>
#include "MatrixIterator.h"

using namespace std;

MatrixIterator::MatrixIterator(const Matrix& m, int column) : matrix(m) {
	this->currentPosition = 0;
	this->columnNumber = column;
	this->lineNumber = 1;
	exception myex;

	if (column < 0 || column > this->matrix.nrColumns())
		throw myex;

	while (this->currentPosition < this->matrix.size && this->matrix.elems[this->currentPosition].lin <= this->lineNumber) {
		if (this->matrix.elems[this->currentPosition].lin == this->lineNumber && this->matrix.elems[this->currentPosition].col == this->columnNumber)
			return;
		this->currentPosition++;
	}
	
}

//BC = WC = Overall = Theta(1)
TElem MatrixIterator::getCurrent()
{
	exception myex;
	if (this->valid()) {
		if (this->currentPosition < this->matrix.size && this->matrix.elems[this->currentPosition].lin > this->lineNumber)
			return NULL_TELEM;
		else if (this->currentPosition >= this->matrix.size)
			return NULL_TELEM;
		return this->matrix.elems[this->currentPosition].value;
	}
	else
		throw myex;
}

//BC = WC = Overall = Theta(1)
bool MatrixIterator::valid()
{
	if (this->lineNumber > this->matrix.nrLines())
		return false;
	return true;
}

//BC = Theta(1)
//WC = Theta(nr columns)
//Overall = O(nr_columns)
void MatrixIterator::next() {
	exception myex;
	if (!this->valid())
		throw myex;
	this->lineNumber++;
	
	while (this->currentPosition < this->matrix.size && this->matrix.elems[this->currentPosition].lin <= this->lineNumber) {
		if (this->matrix.elems[this->currentPosition].lin == this->lineNumber && this->matrix.elems[this->currentPosition].col == this->columnNumber)
			return;
		this->currentPosition++;
	}
}

//BC = Theta(1)
//WC = Theta(nr columns)
//Overall = O(nr_columns)
void MatrixIterator::first() {
	this->currentPosition = 0;
	this->lineNumber = 1;

	while (this->currentPosition < this->matrix.size && this->matrix.elems[this->currentPosition].lin <= this->lineNumber) {
		if (this->matrix.elems[this->currentPosition].lin == this->lineNumber && this->matrix.elems[this->currentPosition].col == this->columnNumber)
			return;
		this->currentPosition++;
	}
}
