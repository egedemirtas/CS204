#include <iostream>
#include <string>
#include "set.h"

using namespace std;

int main()
{
	Set set1, set2;

	int arr1[6] = {0,1,2,3,4,5};
	int arr2[5] = {0,1,2,3,4};
	int arr3[4] = {0,1,2,3};
	int arr4[3] = {0,1,2};
	int arr5[2] = {0,1};


	set1.addSet(arr1,6);
	set1.addSet(arr2,5);
	set1.addSet(arr3,4);

	set2.addSet(arr2,5);
	set2.addSet(arr3,4);
	set2.addSet(arr4,3);
	set2.addSet(arr5,2);


	cout << "Set1: " << set1 << endl;
	cout << "Set2: " << set2 << endl;


	// Assignment Test
	Set set3 = set2;
	cout <<"Set3 = Set2: " << set3 << endl;

	//Self assignment test
	set3 = set3;
	cout <<"Set3 = Set3: " << set3 << endl;

	//Intersection test
	Set set4 = set2 % set1;
	cout << "Set4 = Set2 % Set1: " << set4 << endl;

	//Difference test
	Set set5 = set2 / set1;
	cout << "Set5 = Set2 / Set1: " << set5 << endl;
	
	//Union test
	Set set6 = set2 + set1;
	cout << "Set6 = Set2 + Set1: " << set6 << endl;

	return 0;
}
