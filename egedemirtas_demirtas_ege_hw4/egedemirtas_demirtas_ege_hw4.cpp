#include <iostream>
#include "set.h"
using namespace std;

Set :: Set(){ // constructor
	setHead = new Node(); // NULL, NULL, 0, false as described in struct
	setTail = setHead;
}

Set :: ~Set(){ //destructor
	while(setHead){ //delete sets
		Node *temp = setHead; // to delete sets
		Node *temp1 = setHead->setofSet; //to delete the elements in set
		while(temp1){ //delete the elements in set of set
			Node *temp2 = temp1;
			temp1 = temp1->setofSet;
			delete temp2;
		}
		setHead = setHead->nextElement;
		delete temp;
	}
}

Set :: Set(const Set & copy){//copy constuctor
	Node *copyTail = copy.setHead;
	setHead = new Node(NULL,NULL, copy.setHead->value, true);
	setTail = setHead;
	while(copyTail){ //iterate through the sets of copy
		if(!setTail->empty){ //if copy has been filled with a set, create a new node to add another set
			Node *newSet = new Node(NULL,NULL, copyTail->value, false); // in here the copyTail->value indicates how many elements inside the set
			setTail->nextElement=newSet;
			setTail = newSet;
		}
		Node *copySetofSet = copyTail->setofSet; //to add to copy iteratively
		Node *setofSetTail = setTail->setofSet; //to go through the elements in the set
		while(copySetofSet){ // add each element in the set to the copy
			if(setofSetTail == NULL){ //if no elements has added to the set of copy before, create a node for elements
				Node *newSetofSet = new Node(NULL,NULL, copySetofSet->value, false);
				setTail->setofSet = newSetofSet; //connec the element to the set
				setofSetTail = newSetofSet; //update to iterate
			}else{ //if there is already elements added, update the tail and connect the element to the sets of sets
				Node *newSetofSet = new Node(NULL,NULL, copySetofSet->value, false);
				setofSetTail->setofSet = newSetofSet;
				setofSetTail = newSetofSet;
			}
			copySetofSet = copySetofSet->setofSet;
		}
		setTail->empty = false;
		copyTail= copyTail->nextElement;
	}
}

Set & Set :: addSet(const int arr[], const int size){ //gets an array and creates a set inside the set with the arra's values
	Node *head=new Node();
	Node *tail = head;
	for(int i=0; i<size; i++){ // add values in array to the linked list one by one
		if(head->empty){
			head->value = arr[i];
			head->empty = false;
		}else{
			Node *createElement = new Node(NULL, NULL, arr[i], false); // the values is stored by a pointer
			tail->setofSet = createElement;
			tail = createElement;
		}
	}
	//sort the set with selection sort, this will help us in intersection and difference operations
	Node * temp1 = head;
	while(temp1){
		Node * temp2 = temp1->setofSet;
		while(temp2){
			if(temp1->value > temp2->value){
				int tempStore = temp1->value;
				temp1->value = temp2->value;
				temp2->value = tempStore;
			}
			temp2 = temp2->setofSet;
		}
		temp1=temp1->setofSet;
	}

	if(setHead->empty){ // if no set is added to the set before
		setTail->setofSet = head; //connect the sorted set
		setTail -> empty = false;//indicating that the current set is filled with a set
		setTail->value = size; //indicates how many elements are inside the set
	}else{ //if a set is added before, add another indicator node and connect it
		Node *newSet = new Node(NULL, NULL, size, false);
		setTail->nextElement = newSet;
		setTail = newSet;
		newSet->setofSet = head;
	}
	return *this;
}

const Set & Set :: operator = (const Set & copy){ //basically the same algorith used in copy constructor, the meaning is the same
	if(this == &copy){ //return the same object if both sides are the same object(set1 = set1, returns set1)
		return *this;
	}else{
		Node *tailSetCopy = copy.setHead; //to track the sets in copy
		while(tailSetCopy){
			if(!setTail->empty){
				Node *createSet = new Node(NULL, NULL, 0, false);
				setTail -> nextElement = createSet; //connect the new node to the set
				setTail = setTail->nextElement;
			}
			setTail->empty = false;
			Node *tailSetofSetCopy = tailSetCopy->setofSet;//to track the set of sets
			Node *tailSetofSet = setTail->setofSet;//to track the object's sets of sets
			while(tailSetofSetCopy){
				Node *createElement = new Node(NULL, NULL, tailSetofSetCopy->value, false);
				if(setTail->setofSet == NULL){ //if set is empty initialize it
					tailSetofSet = createElement; //connect the new node
					setTail->setofSet = createElement;
				}else{
					tailSetofSet -> setofSet = createElement; //connect the elements
					tailSetofSet = createElement;
				}
				tailSetofSetCopy = tailSetofSetCopy->setofSet; // go to the next element in the set of set
			}
			tailSetCopy = tailSetCopy->nextElement; //go to the next set of set
		}
		return *this;
	}
}

Set & Set :: operator %(const Set & rhs){ //return a set of intersection
	Set *intersection = new Set; //the object pointed by this pointer will be returned as a result
	Node *IterLHS = setHead;
	while(IterLHS){ //iterate throught the elements of set LHS
		Node *head= NULL;
		Node *tail;
		Node *IterRHS = rhs.setHead;
		while(IterRHS){ //iterating through RHS
			Node *setRHS = IterRHS ->setofSet;
			Node *setLHS = IterLHS ->setofSet;
			bool checker = true;//
			while(setRHS){ //iterating through the sets of RHS, first check if all the element intersects
				if(setRHS && setLHS){//check if element exists in both sets
					if(setRHS->value != setLHS->value){ //since the sets inside the sets are ordered, the elements must be equal(if intersects)
						checker = false; //if there is a single unmatching the checker is will turn false, and indicate elements do no not match, not instersect
						break;
					}
					setLHS = setLHS->setofSet;
					setRHS = setRHS->setofSet;
				}else{
					checker = false;
					break;
				}
			}
			if(checker){ // if all elements same, store it in a new linked list
				setRHS = IterRHS->setofSet;
				setLHS = IterLHS->setofSet;
				while(setLHS){//create and store the elements in a new linked list
					if(!head){ //if no elements are added to intersection set
						head = new Node(NULL,NULL, setLHS->value, false);
						tail = head;
					}else{
						Node *newElement = new Node(NULL,NULL, setLHS->value, false);
						tail->setofSet = newElement;
						tail = newElement;
					}
					setLHS = setLHS->setofSet;
				}
				//connect the new linked list to the new class object(intersection)
				if(intersection->setHead->empty){ // if the intersection object has never been filled before
					intersection->setHead->setofSet = head;
					intersection->setHead->empty = false;
				}else{
					intersection->setTail->nextElement= new Node(NULL, head,0,false);
					intersection->setTail = intersection->setTail->nextElement;
				}
				break; //since an intersection is added, there is no need to add more of the same intersection if it exists, this way we got to the next set in LHS
			}
			IterRHS = IterRHS->nextElement;
		}
		IterLHS = IterLHS->nextElement;
	}
	return *intersection; //returns the new created object
}

Set & Set :: operator /(const Set & rhs){ //creates a set consisting of only the elements in this but not rhs
	Set *difference = new Set;
	Node *IterLHS = setHead;

	while(IterLHS){ //iterte through lhs
		Node *IterRHS = rhs.setHead; //a pointer to iterate through rhs(from the beginning of each LHS set for a complete search each time)
		bool checker = true; //turns false when an unmatching is found
		while(IterRHS){ //iterating through RHS
			Node *setRHS = IterRHS ->setofSet;
			Node *setLHS = IterLHS ->setofSet;
			checker = true; //the checker must be false if the set in LHS is found to be not intersect with any sets in rhs
			while(setRHS){ //same algorith used in intersection, only the conditions are different, iterte through rhs
				if(setLHS->value == setRHS->value){
					checker = true;
				}else{
					checker = false; //if the values are not the same should be false
					break;
				}
				setLHS = setLHS->setofSet;
				setRHS = setRHS->setofSet;
				if( (setLHS == NULL && setRHS != NULL) || (setRHS == NULL && setLHS != NULL)){ // if the sets has different number of elements
					checker = false;
					break;
				}
			}
			if(checker){ //if all elements match, this set intersects, thus go to the next set in LHS to process the next set in this
				break;
			}
			IterRHS = IterRHS->nextElement;
		}
		if(!checker){ //if the sets in this is unique to this
			Node *tempSoS = IterLHS->setofSet;
			Node *initial = new Node();
			Node *head = initial;
			Node *tail = head;
			while(tempSoS){ //create a new linked list to store the difference elements, (same algorithm used in difference)
				if(initial->empty){
					initial->value = tempSoS->value;
					initial ->empty = false;
				}else{
					Node *newEl = new Node(NULL,NULL,tempSoS->value, false);
					tail->setofSet = newEl;
					tail = newEl;
				}
				tempSoS = tempSoS->setofSet;
			}

			if(difference->setHead->empty){ //connect the difference linked list to the set object, (same algorithm used in difference)
				difference->setHead->setofSet = head;
				difference->setHead->empty = false;
			}else{
				difference->setTail->nextElement = new Node(NULL, head, initial->value, false);
				difference->setTail = difference->setTail->nextElement;
			}
		}
		IterLHS = IterLHS->nextElement;
	}
	return *difference;
}

Set & Set :: operator +(const Set & rhs){ //creates a union of two sets
	//the idea is: union = (only set A) + (only set B) + (A intersection B)
	Set *sum= new Set; //stores the union to be returned
	Set *store= new Set; //stores rhs as rhs can not be send as a parameter in the function that takes constant sets
	Set *onlyThis= new Set; //to store only the sets in this but not in rhs
	Set *onlyRHS= new Set; //to store only the sets in rhs but not in this
	Set *intersect= new Set; //to store intersection

	*store = rhs;
	*intersect = ((*this)%(rhs)); //intersection set
	*onlyThis = ((*this)/(*intersect)); //(only set A)
	*onlyRHS = ((*store)/(*intersect)); //(only set B)
	*onlyRHS = *onlyThis; //connect the opinters to each other
	*intersect = *onlyRHS; //connect the opinters to each other
	*sum = *intersect; //connect the opinters to each other
	return *sum;
}

ostream & operator << (ostream & output, Set & set){
	Node *tailSet = set.setHead; //track the elements in the set
	if(set.setHead->empty){//if set is empty, print empty set
		cout << "{ }";
	}
	output << "{ "; //for set expression(beginning)
	while(tailSet){
		output << "{"; //for set of set expression(beginning)
		Node *tailSetofSet = tailSet->setofSet; //track the elements in the set of set(first node is reserved, so it is passed)
		while(tailSetofSet){ //start the processing of the set from the beginning
			if((tailSetofSet->setofSet) == NULL){ //if it is the last element in the set of set, end the set of set with an output
				if( (tailSet->nextElement) == NULL){ //if it is the last set of the set
					output << tailSetofSet->value << "} }"; //end the set
				}else{
					output << tailSetofSet->value << "}, ";//continuation for the next set
				}
			}else{
				output << tailSetofSet->value << ", "; // print the values
			}
			tailSetofSet = tailSetofSet->setofSet; // go to the next element in the set of set
		}
		tailSet= tailSet->nextElement; //go to the next set of set
	}
	return output;
}