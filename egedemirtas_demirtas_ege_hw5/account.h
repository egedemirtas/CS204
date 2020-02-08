/*
Account: This class will implement a basic account object. 
There will be three member variables and they will be double values. 
The members are: balance, limit, debt. 
You need to implement appropriate functions that will make the source file work.
*/
#ifndef acc //to prevent class redefinition
#define acc
#include <string>
#include <iostream>
using namespace std;

class Account{
private:
	double balance;
	double limit;
	double debt;
public://all the fucntions are explained in .cpp file
	Account(double, double, double);
	void depositMoney(double, string);
	void spendMoney(double, string);
	void printAccountInfo(bool);
	void payDebt(double, string);
};
#endif