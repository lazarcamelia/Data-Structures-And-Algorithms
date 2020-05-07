#include "SortedBag.h"
#include "SortedBagIterator.h"

//BC = WC = Overall Case: Theta(1)
SortedBag::SortedBag(Relation r) {
	//TODO - Implementation
	this->relation = r;
	this->head = NIL;
}

//BC = WC = Overall Case: Theta(1)
void SortedBag::initializeNode(Node*& node, TComp e)
{
	node->value = e;
	node->frecv = 1;
	node->next = NIL;
}

//BC: Theta(1), when the element has to be added at the beginning
//WC: Theta(n), when the element has to be added at the end
//Overall complexity: O(n), where n - number of the distinct elements in the sorted bag
void SortedBag::add(TComp e) {
	//TODO - Implementation 
	if (this->head == NIL) {
		//the bag is empty
		Node* newNode = new Node;
		initializeNode(newNode, e);
		this->head = newNode;
		return;
	}
	if (this->relation(this->head->value, e) == false) {
		//we add it at the beginning
		Node* newNode = new Node;
		initializeNode(newNode, e);
		newNode->next = this->head;
		this->head = newNode;
		return;
	}
	
	Node* current = this->head;
	while (current->next != NIL && this->relation(current->next->value, e) == true)
		current = current->next;
	if (current->value == e) {
		//we already have this element so we only increase the frequency
		current->frecv += 1;
		return;
	}
	Node* newNode = new Node;
	initializeNode(newNode, e);

	if (current->next == NIL) {
		//we add it at the end
		current->next = newNode;
	}
	else {
		newNode->next = current->next;
		current->next = newNode;
	}
}

//BC: Theta(1), when the element to be removed is the first
//WC: Theta(n), when the element to be removed is the last
//Overall complexity: O(n), where n - number of the distinct elements in the sorted bag
bool SortedBag::remove(TComp e) {
	//TODO - Implementation
	if (this->head == NIL)
		return false;
	if (this->relation(this->head->value, e) == false)
		return false;
	if (this->head->value == e) {
		this->head->frecv--;
		if (this->head->frecv == 0) {
			if (this->head == NIL)
				this->head = NIL;
			else {
				Node* tmp = this->head;
				this->head = this->head->next;
				delete tmp;
			}
		}
		return true;
	}
	Node* current = this->head;

	while (current->next != NIL && this->relation(current->next->value, e) == true && current->next->value != e)
		current = current->next;
	if (current->next == NIL)
		return false;
	if (current->next->value != e)
		return false;
	else {
		current->next->frecv--;
		if (current->next->frecv == 0) {
			Node* tmp = current->next;
			if (tmp->next != NIL) {
				current->next = tmp->next;
			}
			else
				current->next = NIL;
			delete tmp;
		}
		return true;
	}
}

//BC: Theta(1), when the searched element is the first
//WC: Theta(n), when the searched element is not in the list
//Overall complexity: O(n), where n - number of the distinct elements in the sorted bag
bool SortedBag::search(TComp elem) const {
	//TODO - Implementation
	Node* current = this->head;
	while (current != NIL && this->relation(current->value, elem) == true && current->value != elem) {
		current = current->next;
	}
	if (current != NIL && current->value == elem)
		return true;
	return false;
}

//BC: Theta(1), when the searched element is the first
//WC: Theta(n), when the searched element is not in the list
//Overall complexity: O(n), where n - number of the distinct elements in the sorted bag
int SortedBag::nrOccurrences(TComp elem) const {
	//TODO - Implementation
	Node* current = this->head;
	
	while (current != NIL && this->relation(current->value, elem) == true && current->value != elem) {
		current = current->next;
	}
	if (current != NIL && current->value == elem)
		return current->frecv;

	return 0;
}

//BC = WC = Overall Case: Theta(n), where n = no of distinct elements in the bag
int SortedBag::size() const {
	//TODO - Implementation
	int sizeOfBag = 0;
	Node* current = this->head;

	while (current != NIL) {
		sizeOfBag += current->frecv;
		current = current->next;
	}

	return sizeOfBag;
}

//BC = WC = Overall Case: Theta(1)
bool SortedBag::isEmpty() const {
	//TODO - Implementation
	if (this->head == NIL)
		return true;
	return false;
}

//BC = WC = Overall Case: Theta(1)
SortedBagIterator SortedBag::iterator() {
	return SortedBagIterator(*this);
}

//BC = WC = Overall Case: Theta(n), where n = no of distinct elements in the bag
SortedBag::~SortedBag() {
	//TODO - Implementation
	Node* current = this->head;
	Node* prev = NIL;
	while (current != NIL) {
		prev = current;
		current = current->next;
		delete prev;
	}
}
