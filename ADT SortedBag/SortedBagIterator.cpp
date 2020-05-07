#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

//BC = WC = Overall Case: Theta(1)
SortedBagIterator::SortedBagIterator(SortedBag& b) : bag(b) {
	//TODO - Implementation
	this->currentFrequency = 1;
	this->currentPosition = this->bag.head;
}

//BC = WC = Overall Case: Theta(1)
TComp SortedBagIterator::getCurrent() {
	//TODO - Implementation
	exception myex;
	if (this->valid())
		return this->currentPosition->value;
	throw myex;
}

//BC = WC = Overall Case: Theta(1)
bool SortedBagIterator::valid() {
	//TODO - Implementation
	if (this->currentPosition == NIL)
		return false;
	return true;
}

//BC = WC = Overall Case: Theta(1)
void SortedBagIterator::next() {
	//TODO - Implementation
	exception myex;
	if (!this->valid())
		throw myex;
	this->currentFrequency++;

	if (this->currentFrequency > this->currentPosition->frecv) {
		this->currentPosition = this->currentPosition->next;
		this->currentFrequency = 1;
	}
}

//BC = WC = Overall Case: Theta(1)
void SortedBagIterator::first() {
	//TODO - Implementation
	currentPosition = this->bag.head;
	currentFrequency = 1;
}

//BC = Theta(1)
//WC = Theta(n), where n = the number of distinct elements in the bag
//Overall complexity = O(n), where n = the number of distinct elements in the bag
TComp SortedBagIterator::remove()
{
	std::exception myex;
	if (!this->valid())
		throw myex;

	TComp currentElement = this->currentPosition->value;

	if (this->currentPosition->frecv == 1) {
		this->currentPosition = this->currentPosition->next;
		this->currentFrequency = 1;
	}
	this->bag.remove(currentElement);
	return currentElement;

	/*

	this->currentPosition->frecv--;

	if (this->currentPosition->frecv == 0) {
		Node* current = this->bag.head;

		if (current == this->currentPosition) {
			//we have to change the head
			this->bag.head = this->currentPosition->next;
			this->currentPosition = this->currentPosition->next;
			this->currentFrequency = 1;
			delete current;
		}
		else {
			while (current->next != this->currentPosition) {
				current = current->next;
			}
			current->next = this->currentPosition->next;
			current = this->currentPosition;
			this->currentPosition = this->currentPosition->next;
			this->currentFrequency = 1;
			delete current;
		}
	}
	else {
		if (this->currentFrequency > this->currentPosition->frecv) {
			this->currentPosition = this->currentPosition->next;
			this->currentFrequency = 1;
		}
	}

	return currentElement; */
}

