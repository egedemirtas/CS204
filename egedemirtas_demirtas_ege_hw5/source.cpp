#include <iostream>
#include <string>
#include "account.h"
#include "parent.h" 
#include "child.h"

using namespace std;


int main()
{

  Account acc1(500, 2000, 0); // An account with balance: 500TL, debt limit: 2000TL, current debt: 0TL

  Parent father("James", acc1);
  Parent mother("Lily", acc1);
  Child child("Harry", father);

  mother.depositMoney(50);
  mother.spendMoney(250);

  father.spendMoney(2000);
  mother.printAccountInfo();

  child.spendMoney(500);
  child.spendMoney(50);
  child.displayAccountInfo();

  father.payDebt(4000);
  father.payDebt(1000);

  father.printAccountInfo();

  mother.payDebt(750);
  father.depositMoney(500);

  child.spendMoney(250);
  child.spendMoney(150);

  father.printAccountInfo();

  return 0;

}
