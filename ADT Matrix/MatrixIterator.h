#pragma once
#include "Matrix.h"

class Matrix;

class MatrixIterator {
	friend class Matrix;

private:
	const Matrix& matrix;
	MatrixIterator(const Matrix& m, int column);
	int currentPosition;
	int columnNumber;
	int lineNumber;

public:
	TElem getCurrent();
	bool valid();
	void next();
	void first();
};