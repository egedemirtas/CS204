//Ege Demirtas 25401


#include <iostream>
using namespace std;

//a node struct to create linked list, dynamic queue and stack
struct Nodes{
	int value;
	Nodes *next;
	Nodes(int x=0, Nodes *next=NULL): value(x), next(next){};
};

//abstract class, no member variables
class Container
{
public:
	Container();
	virtual ~Container();
	virtual void insertElement(int) = 0;
	virtual void deleteElement(int) = 0;
	virtual void print() = 0;
};
//empty destructor and constructor
Container :: Container(){}
Container ::~Container(){}


////////////////////// LINKED LIST ///////////////////////////
 //inherited from container class
class LinkedList : public Container
{
public:
	LinkedList();
	virtual ~LinkedList();
	virtual void insertElement(int);
	virtual void deleteElement(int);
	virtual void print();
private:
	Nodes *head; //tail is not necessaryly needed since the element is added according to the order
};

//constructor, head pointing to null since no elemet is added yet
LinkedList::LinkedList()
{
	head = NULL;
}
//destructor, deletes dynamically created heap space
LinkedList::~LinkedList()
{
	cout << "Destructing linked list.\n";
	Nodes *temp = head;
	while(temp){
		head = head->next;
		delete temp;
		temp = head;
	}
}

//gets an int as parameter and puts it in the linked list according to the order(ascending)
void LinkedList :: insertElement(int element){
	Nodes *newElement = new Nodes(element,NULL);
	Nodes *tracker = head;
	//similar to the codes that we have disussed in week 3-4(?)
	if( !head || (head->value > element)){ //if no element is added or the first element is already bigger than the element to be added
		newElement->next = head;
		head = newElement;
		cout << element << " is inserted in the linked list.\n";
		return;
	}
	Nodes *previous = tracker;
	while(tracker){ //finds the fist node where the element is bigger than the value
		if(tracker->value < element){
			previous = tracker;
			tracker = tracker->next;
		}else{
			break;
		}
	}
	//insert the element into the linked list after previous, and reconnect the list
	previous->next = newElement;
	newElement->next = tracker;
	cout << element << " is inserted in the linked list.\n";
}
//gets an int, and deletes the given int in the linked list
void LinkedList :: deleteElement(int element){
	Nodes *tracker = head;
	Nodes *previous = tracker;
	while(tracker){//iterates untill the element is found in the list
		if(tracker->value != element){
			previous = tracker;
			tracker = tracker ->next;
		}else{
			break;
		}
	}
	previous->next = tracker->next; //get the node out of the lsit and delete it
	delete tracker;
	cout << element << " is deleted from the linked list.\n";
}

//prints the values in the linked list
void LinkedList :: print(){
	cout << "Printing linked list\n";
	Nodes *tracker = head;
	while(tracker){
		cout << tracker->value << " ";
		tracker = tracker->next;
	}
	cout << endl;
}


////////////////////// STACK ///////////////////////////
 //inherited from container class
class Stack  : public Container
{
public:
	Stack();
	virtual ~Stack();
	virtual void insertElement(int);
	virtual void deleteElement(int);
	virtual void print();
private:
	Nodes *head;
	Nodes *tail;
};

//same cosntructor as in linked list
Stack::Stack()
{
	head = NULL;
}

//same destructor as in linked list
Stack::~Stack()
{
	cout << "Destructing stack.\n";
	Nodes *temp = head;
	while(temp){
		head = head->next;
		delete temp;
		temp = head;
	}
}


void Stack :: insertElement(int element){
	Nodes *newElement = new Nodes(element,NULL);
	Nodes *tracker = head;

	if( !head ){ //if no elements are on the stack, create this as first eleemt in the stack
		head = newElement;
		tail = head;
		cout << "Inserting " << element << " to stack.\n";
		return;
	}
	//add the new element and it is added in to the first place in the linked list structure
	head = newElement;
	newElement ->next = tracker;
	cout << "Inserting " << element << " to stack.\n";
}

//same as in linked list
void Stack :: deleteElement(int element){
	Nodes *tracker = head;
	Nodes *previous = tracker;
	while(tracker){
		if(tracker->value != element){
			previous = tracker;
			tracker = tracker ->next;
		}else{
			break;
		}
	}
	previous->next = tracker->next;
	delete tracker;
	cout << element << " is deleted from the stack\n";
}
//same as in linked list print
void Stack :: print(){
	cout << "Printing stack\n";
	Nodes *tracker = head;
	while(tracker){
		cout << tracker->value << " ";
		tracker = tracker->next;
	}
	cout << endl;
}

////////////////////// QUEUE ///////////////////////////
 //inherited from container class
class Queue  : public Container
{
public:
	Queue();
	virtual ~Queue();
	virtual void insertElement(int);
	virtual void deleteElement(int);
	virtual void print();
private:
	Nodes *head;
	Nodes *tail;
};

//same constructor but this time there is also tail pointer for the queue
Queue::Queue()
{
	head = NULL;
	tail = NULL;
}

//same destructor as in linked list
Queue::~Queue()
{
	cout << "Destructing queue.\n";
	Nodes *temp = head;
	while(temp){
		head = head->next;
		delete temp;
		temp = head;
	}
}


void Queue :: insertElement(int element){
	Nodes *newElement = new Nodes(element,NULL);
	Nodes *tracker = head;

	if( !head ){//if the quue is empty, create this element as the first node
		head = newElement;
		tail = head;
		cout << "Inserting " << element << " to queue.\n";
		return;
	}
	tail->next = newElement;//add the new element after the previous one and update the place of the tail
	tail = newElement;
	cout << "Inserting " << element << " to queue.\n";
}

//same as in linked list
void Queue :: deleteElement(int element){
	Nodes *tracker = head;
	Nodes *previous = tracker;
	while(tracker){
		if(tracker->value != element){
			previous = tracker;
			tracker = tracker ->next;
		}else{
			break;
		}
	}
	previous->next = tracker->next;
	delete tracker;
	cout << element << " is deleted from the queue.\n";
}

//same as in linked lsit
void Queue :: print(){
	Nodes *tracker = head;
	cout << "Printing queue\n";
	while(tracker){
		cout << tracker->value << " ";
		tracker = tracker->next;
	}
	cout << endl;
}