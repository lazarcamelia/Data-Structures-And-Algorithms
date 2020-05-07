#include "Matrix.h"
#include <exception>
#include "MatrixIterator.h"
using namespace std;

Matrix::Matrix(int nrLines, int nrCols) {

	//TODO - Implementation
	this->nr_lines = nrLines;
	this->nr_columns = nrCols;
	this->size = 0;
	this->capacity = 10;
	this->elems = new MatrixElement[this->capacity];
}

//Best Case = Worst Case = Overall Time complexity: Theta(1)
int Matrix::nrLines() const {
	//TODO - Implementation
	return this->nr_lines;
	//return 0;
}

//Best Case = Worst Case = Overall Time complexity: Theta(1)
int Matrix::nrColumns() const {
	//TODO - Implementation
	return this->nr_columns;
	//return 0;
}

//Best Case = Worst Case = Overall Time complexity:Theta(1)
bool Matrix::relation(MatrixElement element1, MatrixElement element2) const {
	if (element1.lin < element2.lin)
		return true;
	if (element1.lin == element2.lin && element1.col < element2.col)
		return true;
	return false;
}

//Best Case = Worst Case = Overall Time complexity:Theta(1)
bool Matrix::equals(MatrixElement element1, MatrixElement element2) const {
	if (element1.lin == element2.lin && element1.col == element2.col)
		return true;
	return false;
}

MatrixIterator Matrix::iterator(int column) const {
	return MatrixIterator(*this, column);
}

//Best Case = Worst Case = Overall Time complexity: Theta(1)
bool Matrix::isValidPosition(int i, int j) const {
	if (this->nr_lines <= i || this->nr_columns <= j || i < 0 || j < 0)
		return false;
	return true;
}

//Best case complexity: the element is found atfer one comparasion: Theta(1)
//Worst case complexity: the element is not in the dynamic array: Theta(logn)
//Overall Time complexity: O(log2n), where n = size of the dynamic array
int Matrix::searchPosition(int i, int j) const {
	int left = 0, right = this->size - 1, middle;
	MatrixElement searchedElement = { i, j, 0 };

	while (left <= right) {
		middle = (left + right) / 2;

		if (equals(this->elems[middle], searchedElement)) {
			return middle;
		}
		else if (relation(searchedElement, this->elems[middle]) == true)
			right = middle - 1;
		else
			left = middle + 1;
	}
	return left;
}

//Best case complexity: the element is in the middle of the dynamic array(is is found in binary search after only 1 comparation) : Theta(1)
//Worst case complexity: the element is not in the dynamic array(there are logn comparations in binary seach): Theta(logn) 
//Overall Time complexity: O(log2n), n = size of the dynamic array
TElem Matrix::element(int i, int j) const {
	//TODO - Implementation
	exception myex;
	//test if (i, j) is a valid position
	if (!isValidPosition(i, j))
		throw myex;

	int positionOfTheElement = searchPosition(i, j);
	MatrixElement searchedElement = { i, j, 0 };

	if (positionOfTheElement >= this->size)
		return NULL_TELEM;
	else if (!equals(searchedElement, this->elems[positionOfTheElement]))
		return NULL_TELEM;
	else
		return this->elems[positionOfTheElement].value;
}

//Best case complexity: Theta(1) = we find the element on the middle and we only modify it's value
//Worst case complexity: Theta(log2n + n) = Theta(n) = we did not find the element and we add it at the beginning 
//Overall Time complexity: O(n), where n = size of the dynamic array
TElem Matrix::modify(int i, int j, TElem e) {
	//TODO - Implementation
	exception myex;
	if (!isValidPosition(i, j))
		throw myex;

	int positionOfElementInTheArray = searchPosition(i, j);

	//case 1 - the element (i, j) it's not initalized and the value of e is 0 -> return NULL_TELEM
	//Overall Time Complexity: Theta(log2n), where n = size of the dynamic array
	MatrixElement searchedElement = { i, j, 0 };
	if (e == 0 && (positionOfElementInTheArray >= this->size || !equals(this->elems[positionOfElementInTheArray], searchedElement)))
		return NULL_TELEM;

	//case 2 - the element (i, j) is initialized and the value of e is different from 0 -> modify the value of the element
	//Best Case: Theta(1)
	//Worst Case: Theta(log2n)
	//Time Complexity: O(log2n), where n = size of the dynamic array
	if (equals(this->elems[positionOfElementInTheArray], searchedElement) && e != 0) {
		TElem previousValue = this->elems[positionOfElementInTheArray].value;
		this->elems[positionOfElementInTheArray].value = e;
		return previousValue;
	}
	//case 3 - the element (i, j) is not initialized and the value of e is different from 0 -> add the position (i, j) with value 3 in the array
	//Best Case: Theta(logn + 1) = Theta(log2n) - the element is added at the final of the dynamic aray
	//Worst Case: Theta(logn + n) = Theta(n) = the element is added at the beginning of the dynamic array
	//Time Complexity: O(n), where n = size of the dynamic array
	if (e != 0 && (positionOfElementInTheArray >= this->size || !equals(this->elems[positionOfElementInTheArray], searchedElement))) {
		//resize the array in case of having a full array
		if (this->size == this->capacity) {
			this->capacity = this->capacity * 2;
			MatrixElement* newArray = new MatrixElement[this->capacity];

			for (int it = 0; it < this->size; it++)
				newArray[it] = this->elems[it];
			delete[] this->elems;
			this->elems = newArray;
		}
		MatrixElement newElem = { i, j, e };

		this->size += 1;
		for (int j = this->size - 1; j > positionOfElementInTheArray; j--) {
			this->elems[j] = this->elems[j - 1];
		}
		this->elems[positionOfElementInTheArray] = newElem;
	}
	else {
		//case 4 - the position (i, j) is initialized and the value of e is 0 -> we need to delete that position
		//Best Case: Theta(1 + n / 2) = Theta(1) - we find on the middle and we delete from the end of the array
		//Worst Case: Theta(log2n + n) - we find at the last position we search + we delete from beginning
		//Overall Time Complexity: O(n), where n = the size of the dynamic array
		TElem previousValue = this->elems[positionOfElementInTheArray].value;
		for (int i = positionOfElementInTheArray; i < this->size - 1; i++) {
			this->elems[i] = this->elems[i + 1];
		}
		this->size--;
		return previousValue;
	}
	return NULL_TELEM;


}


