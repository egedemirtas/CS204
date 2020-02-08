#include <iostream>
#include <string>
#include "list.h"

using namespace std;


int main()
{
	Set<int> set1, set2;

	int arr1[4] = {0,1,2,3};
	int arr2[3] = {0,1,2};
	int arr3[2] = {0,1};
	int arr4[5] = {0,1,2,3,4};

	set1.addSet(arr1,4);
	set1.addSet(arr3,2);
	set1.addSet(arr4,5);

	set2.addSet(arr2,3);
	set2.addSet(arr3,2);

	cout << "Set1: " << set1 << endl;
	cout << "Set2: " << set2 << endl;

	Set<int> set3 = set2;
	cout <<"Set3 = Set2: " << set3 << endl;

	set3 = set2 % set1;

	Set<int> set4 = set2 + set1;
	Set<int> set5 = set4 / set1;
	Set<int> set6 = set4 / set5;

	cout << "Set3 = Set2 % Set1 : " << set3 << endl;
	cout << "Set4 = Set2 + set1 : " << set4 << endl;
	cout << "Set5 = Set4 / set1 : " << set5 << endl;
	cout << "Set6 = Set4 / set5 : " << set6 << endl;


	//*****************************STRING PART	

	string sarr1[4] = {"Aragorn", "Legolas", "Gimli", "Boromir"};
	string sarr2[3] = {"Radagast", "Saruman", "Gandalf"};
	string sarr3[3] = {"Arwen", "Eowyn", "Galadriel"};
	string sarr4[4] = {"Frodo", "Sam", "Merry", "Pippin"};

	Set<string> sset1, sset2;

	
	sset1.addSet(sarr1,4);
	sset1.addSet(sarr3,3);
	sset1.addSet(sarr4,4);

	sset2.addSet(sarr2,3);
	sset2.addSet(sarr3,3);


	cout << "**********STRINGS*************" << endl;

	cout << "Set1: " << sset1 << endl;
	cout << "Set2: " << sset2 << endl;

	Set<string> sset3 = sset2;
	cout <<"Set3 = Set2: " << sset3 << endl;

	sset3 = sset2 % sset1;//corrected as a remark from Mustafa Kemal Tas

	Set<string> sset4 = sset2 + sset1;
	Set<string> sset5 = sset4 / sset1;
	Set<string> sset6 = sset4 / sset5;

	cout << "Set3 = Set2 % Set1 : " << sset3 << endl;
	cout << "Set4 = Set2 + set1 : " << sset4 << endl;
	cout << "Set5 = Set4 / set1 : " << sset5 << endl;
	cout << "Set6 = Set4 / set5 : " << sset6 << endl;




	return 0;
}
