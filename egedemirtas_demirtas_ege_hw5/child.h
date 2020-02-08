#ifndef children //to prevent class redefinition if another Child object is created
#define children
#include "account.h" //share the account
#include "parent.h" //share the parent
#include <string>
#include <iostream>
using namespace std;

class Child{
private:
	string name;
	Parent &parent;//both account and parent is shared to able to access to parent's account, 
					//also in the source.cpp apperantly the consturcter for child takes Parent object as a paremeter, 
					//thus we must access account through parent
	Account &account;
public:
	Child(string, Parent &);
	void spendMoney(double);
	void displayAccountInfo();
};
#endif
