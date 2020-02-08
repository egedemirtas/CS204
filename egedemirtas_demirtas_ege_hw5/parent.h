#ifndef par //to prevent class redefinition
#define par
#include <string>
#include "account.h"
#include <iostream>
using namespace std;

class Parent{
private:
	string name;
	Account &account;
public:
	Parent(string, Account &);
	void printAccountInfo();
	void depositMoney(double);
	void spendMoney(double);
	void payDebt(double);
	friend class Child; //to access child's private data
};
#endif