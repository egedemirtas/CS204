#include <iostream>
#include <string>
using namespace std;

//taken from HW description
#define SIZE 4
struct complexNode{
	int num;
	string type; // Can be "S"(standard) or "M"(merged)
	complexNode* nexts[SIZE];
	complexNode(int n = 0)
		: num(n) {
			for(int i = 0; i < SIZE; i++)
				nexts[i] = NULL;
			type = "S";
		}
};

//adds the element into the given index of the list
void insertion(complexNode * & initial, int listIndex, int element){
	//if the pointer(with the given index) in the list points to NULL, create a new complexNode, pointer now points to that
	if((initial->nexts[listIndex]) == NULL){
		complexNode * temp = new complexNode;
		initial -> nexts[listIndex] = temp;
	}
	//add new complexNode to the 2nd complexNode, if the pointer points to NULL( S1(correct index)-> S2 -> S3 )
	//and store the element as 3rd complexNode's num ( S1(correct index)-> S2 -> S3 (num = element))
	for(int i=0; i<SIZE; i++){
		if(((initial->nexts[listIndex])->nexts[i]) == NULL){
			complexNode * temp1 = new complexNode;
			(initial->nexts[listIndex])->nexts[i] = temp1;
			temp1->num = element;
			break;
		}
	}
}
//gets two lists(comparedList, comparedWith), compare their available linked lists, if an equal num is found merge them
//comaredWith and comparedList are the indexes of initial complex node, use k and i to reach their consequtive complexNodes
void comparer(complexNode * & initial, int comparedList, int comparedWith){
	for(int i=0; i<SIZE; i++){
		for(int k=0; k<SIZE; k++){
			//check if the list exist, and check if that list has linked lists
			if( ((initial->nexts[comparedList]) != NULL) &&
				((initial->nexts[comparedWith]) != NULL) &&
				((initial->nexts[comparedList]->nexts[i]) != NULL) && 
				((initial->nexts[comparedWith]->nexts[k]) != NULL) &&
				((initial->nexts[comparedList]->nexts[i]->num) == (initial->nexts[comparedWith]->nexts[k]->num)) ){ //check if num is equal
					if( (initial->nexts[comparedList]->nexts[i]) != (initial->nexts[comparedWith]->nexts[k]) ){ //if they are not already merged, merge them
						delete initial->nexts[comparedWith]->nexts[k]; //delete the node pointed by the index(comparedWith)
						initial->nexts[comparedWith]->nexts[k] = initial->nexts[comparedList]->nexts[i]; //set the address of comparedWith as same as comparedLsit
						initial->nexts[comparedList]->nexts[i]->type = "M" + to_string(comparedList); //set their type to merged
					}
			}
		}
	}
}
//pick 2 different lists to be compared each time and send them to void comparer() to find and merge nodes
void mergeLists(complexNode * & initial){
	int comparedList = 0, comparedWith = 1;
	while(1){
		if(comparedList < comparedWith){ //eliminates unnecessary instances of calling void comparer(initial,3,3), 
										 //or if void comparer(initial,1,3) is called before, void comparer(initial,3,1) wont be called again
			comparer(initial, comparedList, comparedWith);
		}
		if(comparedWith != 3){
			comparedWith++;
		}else if((comparedList == 3) && (comparedWith ==3)){ //end the loop when all lists were compared
			break;
		}else if(comparedWith == 3){
			comparedList++;
			comparedWith = 0;
		}
	}
}

//prints the selected list's contents(type, num)
void printList(complexNode * & initial, int listIndex){
	for(int i=0; i< SIZE; i++){
		if((initial->nexts[listIndex]->nexts[i]) != NULL){ //if a pointer in the initial node points to NULL skip the procces
			cout << (initial->nexts[listIndex]->nexts[i]->type) << "-" << (initial->nexts[listIndex]->nexts[i]->num); //output in correct format
			if((initial->nexts[listIndex]->nexts[i+1]) != NULL){ //outputs a space to seperate contents, prevents occurance of a space after the last content of a list
				cout << " ";
			}
		}
	}
	cout << endl;
}

//prints all the content of the list, type and num
void printAllLists(complexNode * & initial){
	for(int i=0; i<SIZE; i++){
		cout << "***** LIST " << i << " *****\n";
		//if pointer points to NULL, prompt that the list is empty 
		if(initial->nexts[i] == NULL){
			cout << "The list is empty";
		}else{
			//if pointer doesnt points to NULL print the contents
			for(int j=0; j<SIZE; j++){
				if((initial->nexts[i]->nexts[j]) != NULL){
					cout << (initial->nexts[i]->nexts[j]->type) << "-" << (initial->nexts[i]->nexts[j]->num);
					//for formatting purposes, add a single space if next linked list exists
					if((initial->nexts[i]->nexts[j+1]) != NULL){
						cout << " ";
					}
				}else if((initial->nexts[i]->nexts[j+1]) != NULL){ //if the pointer points to NULL, print a space for it since it wont be taken int consideration
					cout << " ";
				}
			}
		}
		cout << endl;
	}
}

//gets 2 indexes: listIndex is for initial complex node, numIndex is for the next complexNode
//find how many times the address of the given indexes is merged and return it
int findMergedNum(complexNode * & initial, int listIndex, int numIndex){
	int mergedCounter =0;
	for(int k=0; k<SIZE; k++){
		for(int m=0; m<SIZE; m++){
			if( ((initial->nexts[k]) != NULL) && ((initial->nexts[k]->nexts[m]) != NULL) ){
				if( (initial->nexts[listIndex]->nexts[numIndex]) == (initial->nexts[k]->nexts[m]) ){ //if they are merged their addresses must be the same
					mergedCounter++;
				}
			}
		}
	}
	return mergedCounter;
}

//finds the element in the list(with index = listIndex) and deletes it
//changes the type of the other nodes if they are effected by deletion of a merged node
void deleteNode(complexNode * & initial, int listIndex, int element){
	int counter = 0;
	bool exists = false; //to check if element exists in the list
	bool checkMerged = false; //to check if a merged pointer is found

	if( (initial->nexts[listIndex]) != NULL ){//check if list exists
		while(counter < 4){
			if(initial->nexts[listIndex]->nexts[counter] != NULL){ //check if the linkedlist exists
				if((initial->nexts[listIndex]->nexts[counter]->num) == element){ //find the element in the linked list
					if((initial->nexts[listIndex]->nexts[counter]->type) == "S"){ //seperate deletion for S types
						delete (initial->nexts[listIndex]->nexts[counter]);
						initial->nexts[listIndex]->nexts[counter] = NULL;
						exists = true; //confirm that an element is found
					}else{ //seperate deletion for M, since it contains a merged location, we can move the target pointer to NULL, so other merged pointers wont be affected
						for(int i=0; i<SIZE; i++){ //if the "to be deleted" node is merged, find the other merged pointers
							if(i != listIndex){ //dont search in the same list, saves time and unneccessary
								for(int j=0; j<SIZE; j++){
									if( ((initial->nexts[i]) != NULL) && ((initial->nexts[i]->nexts[j]) != NULL) && (!checkMerged) ){ //check if pointers point somewhere and if a merged one is found
											if( element == (initial->nexts[i]->nexts[j]->num) ){ //if element is found
												if(findMergedNum(initial, i, j) > 2){ //if merged number of pointers are bigger than 2, find the smallest merged pointer 
													                                  //and change every pointers type as same as that first pointer
													initial->nexts[i]->nexts[j]->type = "M" + to_string(i);
													checkMerged = true; //check that pointers' types are correct now, dont do it again
													exists = true;
												}else{ //if merged number is smaller or equals to 2 than when a merged pointer is deleted other one should be changed to type "S"
													initial->nexts[i]->nexts[j]->type = "S";
													exists = true;
												}
											}
									}
								}
							}
						}
						initial->nexts[listIndex]->nexts[counter] = NULL; //"to be deleted" pointer now points to NULL(in the instance of merged nodes)
						exists = true;
					}
				}
			}
			counter++;
		}if(!exists){ //if the element is not found in given index
			cout << "Element could not found in List " << listIndex <<endl;
		}
	}else{ //if list points to NULL then there is no linked list, it is empty
		cout << "The list is empty" << endl;
	}
}

//taken from HW
void message(){
	cout << "1 - Insert a new node\n" << 
	"2 - Merge lists\n" << 
	"3 - Print list\n" << 
	"4 - Print all lists\n" <<
	"5 - Delete node\n" <<
	"6 - Exit\n\n" <<
	"Enter your choice:";
}

int main(){
	//create an initia complex node
	complexNode * initial = new complexNode;

	while(1){
		int menuChoice;
		int listIndex, element;
		message(); //show message
		cin >> menuChoice;
		//do appropiate action depending on entered menu choice
		if(menuChoice == 1){ //insertion
			cout << "Please enter which list you want to add to: ";
			cin >> listIndex;
			if((listIndex < 4) && (listIndex >= 0)){
				cout << "Please enter the element you want to add: ";
				cin >> element;
				insertion(initial, listIndex, element);
			}else{
				cout << "Selection out of range.\n\n";
			}
		}else if(menuChoice == 2){ //merge lists
			mergeLists(initial);
		}else if(menuChoice == 3){ //prints an enetred list
			cout << "Please enter which list you want print: ";
			cin >> listIndex;
			if((listIndex < 4) && (listIndex >= 0)){
				printList(initial, listIndex);
			}else{
				cout << "Selection out of range.\n\n";
			}
		}else if(menuChoice == 4){ //prints all lists
			printAllLists(initial);
		}else if(menuChoice == 5){ //deletes an enetered element in a given node
			cout << "Please enter which list you want delete from: ";
			cin >> listIndex;
			if((listIndex < 4) && (listIndex >= 0)){
				cout << "Please enter the number to be deleted: ";
				cin >> element;
				deleteNode(initial, listIndex, element);
			}else{
				cout << "Selection out of range.\n\n";
			}
		}else if(menuChoice == 6){ //exit program
			break;
		}
		cout << endl;
	}
	return 0;
}






