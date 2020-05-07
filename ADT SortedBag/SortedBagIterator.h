#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	SortedBag& bag;
	SortedBagIterator(SortedBag& b);

	//TODO - Representation
	Node* currentPosition;
	int currentFrequency;


public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
	TComp remove();
};
