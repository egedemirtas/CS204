#include <iostream>
using namespace std;

struct Node{
	Node *nextElement; //pass to next element
	Node *setofSet; //pass to the set of elements
	int value;
	bool empty;
	Node(Node *x = NULL, Node *y = NULL, int z = 0, bool m = true) : //initially the value is 0, meaning it is empty. Value = 1 means it has been filled
		nextElement(x), setofSet(y), value(z), empty(m){}
};

class Set{
private:
	Node * setHead; //to access to the set
	Node * setTail; //to be able to add elemets to the set
public:
	Set();
	Set(const Set &);
	~Set();
	Set & addSet(const int [], const int);
	const Set & operator = (const Set &);
	Set & operator %(const Set &);
	Set & operator /(const Set &);
	Set & operator +(const Set &);
	friend ostream & operator<<(ostream &, Set &);
};