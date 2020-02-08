//all the class functions in the given order:
#include "account.h"
#include "parent.h"
#include "child.h"

//////////////////////////////////ACCOUNT////////////////////////////////////////////////////
Account :: Account(double b, double l, double d) : balance(b), limit(l), debt(d){} //constructor

void Account :: depositMoney(double depo, string name){ //deposits the money(given in the parameter) and prompts an appropiate message with the given name(as parameter)
	if(debt > 0){ //if there is a debt, debt should be paid first with the deposit money
		if(debt > depo){ //if depopist is less than debt, only debt is decreased
			debt -= depo;
		}else{ //if deposit is more than debt than the remaining must be added to balance
			balance = depo - debt;
			debt = 0;
		}
	}else{ // if no debt, deposit to the balance
		balance += depo;
	}
	cout << name << " has deposited " << depo << "TL.\n";
}

void Account :: spendMoney(double spend, string name){ //spends the money(given in the parameter) and prompts an appropiate message with the given name(as parameter)
	if((spend + debt - balance) <= limit){ //first check if the money will be spent exceed the avalable account limit (this was not on the hw, but I thought it was need)
		if(balance >= spend){ //if balance has enough money, withdraw from it
			balance -= spend;
		}else{
			debt += (spend - balance); //if balance is less than withdrawel, then process the withdrawel as debt and set balance to 0
			balance = 0;
		}
	}else{
		cout << "Can not exceed available account limit.\n";
	}
	cout << name << " has succesfully spent " << spend << "TL.\n";
}

void Account :: printAccountInfo(bool isChild){ //takes a bool parameter, and prompts bank info accordingly
	cout << "\n******************************\n";
	cout << "The account balance is: " << balance << "TL.\n";
	if(isChild == false){ //if it is not a child these messages will be also prompted
	cout << "The account debt is: " << debt << "TL.\n";
	cout << "The account limit is " << limit <<"TL.\n";
	}
	cout << "The available account limit is:" << limit-debt << "TL.\n";
	cout << "******************************\n";
}

void Account :: payDebt(double pay, string name){ //pays debt with the given paramater(double) and prompts with the given parameter(string)
	if(debt >= pay){ //to pay the debt the deposit money should be less or equal to debt
		debt -= pay;
		cout << name <<" payed " << pay << " of debt.\n";
	}else{
		cout << name <<" attempts to pay more than debt. No payment is done.\n";
	}
}
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////PARENT/////////////////////////////////////////////
Parent::Parent(string myName, Account &myAccount) : name(myName), account(myAccount){} //constructor
//all the functions given below sends their data to account class for processing. Since account is shared object, any parent can access it and the changes will be the same for all parents
void Parent :: depositMoney(double depo){ //Ex:parent sends how much he/she wants to pay and his/her name as parameters to account class, and the processing is done in account class
	account.depositMoney(depo, name);
}

void Parent :: spendMoney(double spend){
	account.spendMoney(spend, name);
}

void Parent :: printAccountInfo(){
	account.printAccountInfo(false);
}

void Parent :: payDebt(double pay){
	account.payDebt(pay, name);
}
//////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////CHILD///////////////////////////////////////////////////////
Child::Child(string myName,Parent & myParent): name(myName), parent(myParent), account(parent.account){}//constructor, a child shares the parent and the account of the parent

void Child::spendMoney(double spend){ //spend money function for only child
	if(spend <= 200){ //children cannot spend more than 200
		account.spendMoney(spend, name);
	}else{
		cout << "Harry can not spend " << spend <<"TL. Children can spend up to 200TL.\n";
	}
}

void Child::displayAccountInfo(){ //display info special for child
	bool isChild = true;
	account.printAccountInfo(isChild);//since it is a child, a "true" bool is send for account class to identify and prompt messages accordingly
}