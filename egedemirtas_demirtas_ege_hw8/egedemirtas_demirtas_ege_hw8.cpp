#include <iostream>
#include <string>

#include "container.h"

using namespace std;


int main()
{
  Container *containers[3];
  containers[0] = new LinkedList();
  containers[1] = new Stack();
  containers[2] = new Queue();
  int selection = -1;
  int operation = -1;
  int num ;
  
  while(selection != 3){
    cout << "Enter your selection(0-LinkedList, 1-Stack, 2-Queue, 3-Exit): ";
    cin >> selection;
    if(selection != 3) {
      cout << "Enter the operation(0-insert, 1-delete, 2-print): ";
      cin >> operation;
      if(operation == 0){
	cout << "Enter the number to be inserted: ";
	cin >> num;
	containers[selection]->insertElement(num);
      }
      else if(operation == 1) {
	cout << "Enter the number to be deleted: ";
	cin >> num;
	containers[selection]->deleteElement(num);
	
      }
      else if(operation == 2)
	containers[selection]->print();
    }
  }

  for(int i = 0; i < 3; i++)
  delete containers[i];

  cout << "Exiting.." << endl;

}
