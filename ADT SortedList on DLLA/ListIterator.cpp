#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

//BC = WC = AC = Theta(1)
ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	//TODO - Implementation
	this->currentPosition = this->list.head;
}

//BC = WC = AC = Theta(1)
void ListIterator::first() {
	//TODO - Implementation
	this->currentPosition = this->list.head;
}

//BC = WC = AC = Theta(1)
void ListIterator::next() {
	//TODO - Implementation
	std::exception myex;

	if (!this->valid())
		throw myex;
	this->currentPosition = this->list.next[this->currentPosition];
}

//BC = WC = AC = Theta(1)
bool ListIterator::valid() const {
	//TODO - Implementation
	if (this->currentPosition == -1)
		return false;
	return true;
}
//BC = WC = AC = Theta(1)
TComp ListIterator::getCurrent() const {
	//TODO - Implementation
	std::exception myex;
	if (!this->valid())
		throw myex;
	return this->list.elems[this->currentPosition];
}


