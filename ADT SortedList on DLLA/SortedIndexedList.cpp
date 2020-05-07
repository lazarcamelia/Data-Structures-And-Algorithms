#include "ListIterator.h"
#include <iostream>
using namespace std;
#include <exception>
#include "SortedIndexedList.h"

//Complexity: BC = WC = AC = Theta(1)
SortedIndexedList::SortedIndexedList(Relation r) {
	//TODO - Implementation
	this->capacity = 1000;
	this->elems = new TComp[this->capacity];
	this->next = new TComp[this->capacity];
	this->prev = new TComp[this->capacity];
	this->firstEmpty = 0;
	this->head = -1;
	this->tail = -1;
	this->sizeOfList = 0;
	this->relation = r;

	for (int i = 0; i < this->capacity - 1; i++) {
		this->next[i] = i + 1;
		this->prev[i + 1] = i;
	}
	next[this->capacity - 1] = -1;
	prev[0] = -1;
}

//BC = WC = AC = Theta(1)
int SortedIndexedList::size() const {
	//TODO - Implementation
	return this->sizeOfList;
}

//BC = WC = AC = Theta(1)
bool SortedIndexedList::isEmpty() const {
	//TODO - Implementation
	if (this->sizeOfList == 0)
		return true;
	return false;
}

//BC: Theta(1)
//WC: Theta(n), where n = the size of the list
//AC: O(n), where n = the size of the list
TComp SortedIndexedList::getElement(int i) const {
	//TODO - Implementation
	std::exception myex;
	if (i < 0 || i >= this->sizeOfList)
		throw myex;

	int contor = 0;
	int node = this->head;

	while (contor < i && node != -1) {
		node = this->next[node];
		contor++;
	}
	if (node == -1)
		return NULL_TCOMP;
	return this->elems[node];
}

//BC: Theta(1)
//WC: Theta(n), where n = the size of the list
//AC: O(n), where n = the size of the list
TComp SortedIndexedList::remove(int i) {
	//TODO - Implementation
	std::exception myex;
	if (i < 0 || i >= this->sizeOfList)
		throw myex;

	int contor = 0;
	int node = this->head;

	while (contor < i && node != -1) {
		node = this->next[node];
		contor++;
	}

	if (contor == i) {
		this->sizeOfList--;
		TComp value = this->elems[node];
		if (this->prev[node] == -1) {
			//it is the head
			if (this->next[node] == -1) {
				//it is also the tail
				this->next[node] = this->firstEmpty;
				if (this->firstEmpty != -1)
					this->prev[this->firstEmpty] = node;
				this->prev[node] = -1;
				this->head = this->tail = -1;
				this->firstEmpty = node;
			}
			else {
				//it is the head, but not the tail
				this->prev[this->next[node]] = -1;
				this->head = this->next[this->head];
				this->next[node] = this->firstEmpty;
				if (this->firstEmpty != -1)
					this->prev[this->firstEmpty] = node;
				this->firstEmpty = node;
			}
		}
		else if (this->next[node] == -1) {
			//it is only the tail
			this->next[this->prev[node]] = -1;
			this->tail = this->prev[node];
			this->prev[node] = -1;
			this->next[node] = this->firstEmpty;
			if (this->firstEmpty != -1)
				this->prev[this->firstEmpty] = node;
			this->firstEmpty = node;
		}
		else {
			//it is not the tail and also not the head
			this->next[this->prev[node]] = this->next[node];
			this->prev[this->next[node]] = this->prev[node];
			this->next[node] = this->firstEmpty;
			this->prev[node] = -1;
			if (this->firstEmpty != -1)
				this->prev[this->firstEmpty] = node;
			this->firstEmpty = node;
		}

		return value;
	}
}

//BC: Theta(1)
//WC: Theta(n), where n = the size of the list
//AC: O(n), where n = the size of the list
int SortedIndexedList::search(TComp e) const {
	//TODO - Implementation
	int node = this->head, contor = 0;

	while (node != -1 && this->elems[node] != e && this->relation(this->elems[node], e)) {
		node = this->next[node];
		contor += 1;
	}
	if (node == -1)
		return -1;
	if (this->elems[node] == e)
		return contor;
	return -1;
}

//BC: Theta(1)
//WC: Theta(n), where n = the size of the list
//AC: O(n), where n = the size of the list
void SortedIndexedList::add(TComp e) {
	//TODO - Implementation
	if (this->sizeOfList == this->capacity)
		this->resize();
	
	int node = this->head;

	while (node != -1 && this->relation(this->elems[node], e))
		node = this->next[node];

	int newFirstEmpty = this->next[this->firstEmpty];
	this->prev[this->firstEmpty] = -1;

	this->sizeOfList++;
	this->elems[this->firstEmpty] = e;
	this->next[this->firstEmpty] = this->prev[this->firstEmpty] = -1;

	if (this->sizeOfList == 1) {
		this->head = this->tail = this->firstEmpty;
		this->next[this->firstEmpty] = this->prev[this->firstEmpty] = -1;
	}
	else {
		if (this->head == node) {
			this->prev[this->head] = this->firstEmpty;
			this->next[this->firstEmpty] = this->head;
			this->head = this->firstEmpty;
		}
		else if (node == -1) {
			//the node after the tail
			this->next[this->tail] = this->firstEmpty;
			this->prev[this->firstEmpty] = this->tail;
			this->tail = this->firstEmpty;
			this->next[this->firstEmpty] = -1;
		}
		else {
			this->next[this->prev[node]] = this->firstEmpty;
			this->prev[this->firstEmpty] = this->prev[node];
			this->prev[node] = this->firstEmpty;
			this->next[this->firstEmpty] = node;
 		}
	}
	this->firstEmpty = newFirstEmpty;
}

ListIterator SortedIndexedList::iterator() {
	return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
	//TODO - Implementation
	delete[] this->elems;
	delete[] this->next;
	delete[] this->prev;
}

//BC=WC=AC = Theta(n), where n = the size of the list
void SortedIndexedList::resize() {
	this->capacity *= 2;
	//resize elems
	TComp* aux = new TComp[this->capacity];

	for (int i = 0; i < this->sizeOfList; i++)
		aux[i] = this->elems[i];

	delete[] this->elems;
	this->elems = aux;
	//resize next
	aux = new TComp[this->capacity];
	for (int i = 0; i < this->sizeOfList; i++)
		aux[i] = this->next[i];

	delete[] this->next;

	this->next = aux;
	//resize prev
	aux = new TComp[this->capacity];
	for (int i = 0; i < this->sizeOfList; i++)
		aux[i] = this->prev[i];

	delete[] this->prev;
	this->prev = aux;

	for (int i = this->sizeOfList; i < this->capacity - 1; i++) {
		this->next[i] = i + 1;
		this->prev[i + 1] = i;
	}
	//this->prev[this->sizeOfList] = -1;
	this->next[this->capacity - 1] = -1;
	this->firstEmpty = this->sizeOfList;
}
