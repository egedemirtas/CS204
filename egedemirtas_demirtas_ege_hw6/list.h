//Ege Demirtas 25401 HW6

#include <iostream>
using namespace std;

template <class T>
struct Node{
	Node<T> *nextElement; //pass to next element
	Node<T> *setofSet; //pass to the set of elements
	T value;
	bool empty;
	Node(Node *x = NULL, Node *y = NULL, bool m = true) : //initially the value is 0, meaning it is empty. Value = 1 means it has been filled
		nextElement(x), setofSet(y), empty(m){}
};

template <class T>
class Set{
private:
	Node<T> * setHead; //to access to the set
	Node<T> * setTail; //to be able to add elemets to the set
public:
	Set();
	Set(const Set &);
	~Set();
	Set<T> & addSet(const T [], const int);
	const Set<T> & operator = (const Set &);
	Set<T> operator %(const Set &);
	Set<T> operator /(const Set &);
	Set<T> operator +(const Set &);
	friend ostream & operator<< <>(ostream &, Set &);//it has not been thaught in class but I found out that with "<>" I can still use this function as friend, so I dont nedd to add getHead() or somethign else
};

//functions for the class are listed here below since template is used they must be in the same file
template <class T>
Set<T> :: Set(){ // constructor
	setHead = new Node<T>(); // NULL, NULL, 0, false as described in struct
	setTail = setHead;
}

template <class T>
Set<T> :: ~Set(){ //destructor
	while(setHead){ //delete sets
		Node<T> *temp = setHead; // to delete sets
		Node<T> *temp1 = setHead->setofSet; //to delete the elements in set
		while(temp1){ //delete the elements in set of set
			Node<T> *temp2 = temp1;
			temp1 = temp1->setofSet;
			delete temp2;
		}
		setHead = setHead->nextElement;
		delete temp;
	}
}

template <class T>
Set<T> :: Set(const Set<T> & copy){//copy constuctor
	setHead = new Node<T>(NULL, NULL, true);
	setHead->value = copy.setHead->value;
	setTail = setHead;
	Node<T> *tailSetCopy = copy.setHead; //to track the sets in copy
		while(tailSetCopy){
			if(!setTail->empty){
				Node<T> *createSet = new Node<T>(NULL, NULL, false);
				setTail ->nextElement = createSet;
				setTail = createSet;
			}
			setTail->empty = false;
			Node<T> *tailSetofSetCopy = tailSetCopy->setofSet;//to track the set of sets
			Node<T> *tailSetofSet; //= setTail->setofSet;//to track the object's sets of sets
			while(tailSetofSetCopy){
				Node<T> *createElement = new Node<T>(NULL, NULL, false);
				createElement->value = tailSetofSetCopy->value ;
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
}

template <class T>
Set<T> & Set<T> :: addSet(const T arr[], const int size){ //gets an array and creates a set inside the set with the arra's values
	Node<T> *head=new Node<T>();
	Node<T> *tail = head;
	for(int i=0; i<size; i++){ // add values in array to the linked list one by one
		if(head->empty){
			head->value = arr[i];
			head->empty = false;
		}else{
			Node<T> *createElement = new Node<T>(NULL, NULL, false); // the values is stored by a pointer
			createElement->value = arr[i];
			tail->setofSet = createElement;
			tail = createElement;
		}
	}
	//sort the set with selection sort, this will help us in intersection and difference operations
	Node<T> * temp1 = head;
	while(temp1){
		Node<T> * temp2 = temp1->setofSet;
		while(temp2){
			if(temp1->value > temp2->value){
				T tempStore = temp1->value;
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
		Node<T> *newSet = new Node<T>(NULL, NULL, false);
		newSet->value = size;
		setTail->nextElement = newSet;
		setTail = newSet;
		newSet->setofSet = head;
	}
	return *this;
}

template <class T>
const Set<T> & Set<T> :: operator = (const Set<T> & copy){ //basically the same algorith used in copy constructor, the meaning is the same
	if(this == &copy){ //return the same object if both sides are the same object(set1 = set1, returns set1)
		return *this;
	}else{
		Node<T> *temp = setHead;
		(*this).~Set();//we dont need this anymore so it can be deleted
		Node<T> *tailSetCopy = copy.setHead; //to track the sets in copy
		while(tailSetCopy){
			if(setTail->empty){
				Node<T> *createSet = new Node<T>(NULL, NULL, false);
				setTail = setHead = createSet;
			}else{
				Node<T> *createSet = new Node<T>(NULL, NULL, false);
				setTail ->nextElement = createSet;
				setTail = createSet;
			}
			Node<T> *tailSetofSetCopy = tailSetCopy->setofSet;//to track the set of sets
			Node<T> *tailSetofSet; //= setTail->setofSet;//to track the object's sets of sets
			while(tailSetofSetCopy){
				Node<T> *createElement = new Node<T>(NULL, NULL, false);
				createElement->value = tailSetofSetCopy->value ;
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

template <class T>
Set<T> Set<T> :: operator %(const Set<T> & rhs){ //return a set of intersection
	Set<T> intersection;//the object pointed by this pointer will be returned as a result
	Node<T> *IterLHS = setHead;
	while(IterLHS){ //iterate throught the elements of set LHS
		Node<T> *head= NULL;
		Node<T> *tail;
		Node<T> *IterRHS = rhs.setHead;
		while(IterRHS){ //iterating through RHS
			Node<T> *setRHS = IterRHS ->setofSet;
			Node<T> *setLHS = IterLHS ->setofSet;
			bool checker = true;
			while(setRHS && setLHS){ //iterating through the sets of RHS, first check if all the element intersects
				if(setRHS && setLHS){//check if element exists in both sets
					if(setRHS->value != setLHS->value){ //since the sets inside the sets are ordered, the elements must be equal(if intersects)
						checker = false; //if there is a single unmatching the checker is will turn false, and indicate elements do no not match, not instersect
						break;
					}
					setLHS = setLHS->setofSet;
					setRHS = setRHS->setofSet;
					if( (setRHS==NULL && setLHS!=NULL) || (setRHS!=NULL && setLHS==NULL)){
						checker = false;
						break;
					}
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
						head = new Node<T>(NULL,NULL, false);
						head->value = setLHS->value;
						tail = head;
					}else{
						Node<T> *newElement = new Node<T>(NULL,NULL, false);
						newElement->value = setLHS->value;
						tail->setofSet = newElement;
						tail = newElement;
					}
					setLHS = setLHS->setofSet;
				}
				//connect the new linked list to the new class object(intersection)
				if( intersection.setHead->empty ){ // if the intersection object has never been filled before
					intersection.setHead->setofSet = head;
					intersection.setHead->empty = false;
				}else{
					intersection.setTail->nextElement= new Node<T>(NULL, head, false);
					intersection.setTail = intersection.setTail->nextElement;
				}
				break; //since an intersection is added, there is no need to add more of the same intersection if it exists, this way we got to the next set in LHS
			}
			IterRHS = IterRHS->nextElement;
		}
		IterLHS = IterLHS->nextElement;
	}
	return intersection; //returns the new created object
}

template <class T>
Set<T> Set<T> :: operator /(const Set<T> & rhs){ //creates a set consisting of only the elements in this but not rhs
	Set<T> difference;
	Node<T> *IterLHS = setHead;

	while(IterLHS){ //iterte through lhs
		Node<T> *IterRHS = rhs.setHead; //a pointer to iterate through rhs(from the beginning of each LHS set for a complete search each time)
		bool checker = true; //turns false when an unmatching is found
		while(IterRHS){ //iterating through RHS
			Node<T> *setRHS = IterRHS ->setofSet;
			Node<T> *setLHS = IterLHS ->setofSet;
			checker = true; //the checker must be false if the set in LHS is found to be not intersect with any sets in rhs
			while(setRHS && setLHS){ //same algorith used in intersection, only the conditions are different, iterte through rhs
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
			Node<T> *tempSoS = IterLHS->setofSet;
			Node<T> *initial = new Node<T>();
			Node<T> *head = initial;
			Node<T> *tail = head;
			while(tempSoS){ //create a new linked list to store the difference elements, (same algorithm used in difference)
				if(initial->empty){
					initial->value = tempSoS->value;
					initial ->empty = false;
				}else{
					Node<T> *newEl = new Node<T>(NULL,NULL,false);
					newEl->value = tempSoS->value;
					tail->setofSet = newEl;
					tail = newEl;
				}
				tempSoS = tempSoS->setofSet;
			}

			if(difference.setHead->empty){ //connect the difference linked list to the set object, (same algorithm used in difference)
				difference.setHead->setofSet = head;
				difference.setHead->empty = false;
			}else{
				difference.setTail->nextElement = new Node<T>(NULL, head, false);
				difference.setTail->nextElement->value = initial->value;
				difference.setTail = difference.setTail->nextElement;
			}
		}
		IterLHS = IterLHS->nextElement;
	}
	return difference;
}

template <class T>
Set<T> Set<T> :: operator +(const Set<T> & rhs){ //creates a union of two sets
	//the idea is: union = (only set A) + (only set B) + (A intersection B)
	Set<T> *intersection = new Set<T>;//intersection set
	*intersection = (*this)%rhs;

	Set<T> *onlyThis = new Set<T>;//(only set A)
	*onlyThis = (*this)/rhs;
	intersection->setTail->nextElement = onlyThis->setHead; //merge intersection with A

	Set<T> *onlyRHS = new Set<T>;//(only set B)
	*onlyRHS = ((const Set <T>)rhs)/(*this);
	onlyThis->setTail->nextElement = onlyRHS->setHead; //merge B with A

	return *intersection;
}

template <class T>
ostream & operator << (ostream & output, Set<T> & set){
	Node<T> *tailSet = set.setHead; //track the elements in the set
	if(set.setHead->empty){//if set is empty, print empty set
		cout << "{ }";
	}
	output << "{ "; //for set expression(beginning)
	while(tailSet){
		output << "{"; //for set of set expression(beginning)
		Node<T> *tailSetofSet = tailSet->setofSet; //track the elements in the set of set(first node is reserved, so it is passed)
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