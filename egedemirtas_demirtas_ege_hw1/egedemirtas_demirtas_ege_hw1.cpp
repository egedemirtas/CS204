//Ege Demirtas 25401
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

//return true if the the matrices are in correct size and number, also stores them in 3Dvector(matrices)
bool checkMatrices(int sizeRow, int numberMatrices, ifstream & input, vector<vector<vector<int>>> & matrices){
	string line;
	int temp;
	//perform the same operations for each matrice in file
	for(int i=0; i < numberMatrices; i++){
		getline(input,line);
		istringstream input1(line);
		//check whether if the 3rd line is empty and the is and empty line between matrices(correct column size)
		//return false if incorrect column size
		if(input1 >> temp){
			return false;
		}
		//increment the counter each time a value is read from the same row
		//return false if the counter is not equal to row size
		for(int j=0; j < sizeRow; j++){
			int counter = 0;
			getline(input,line);
			istringstream input2(line);
			int columnIndex = 0;
			while(input2 >> temp){
				counter+=1;
				if(counter > sizeRow){
					return false;
				}
				//store the value in 3D vector(matrices)
				matrices[j][columnIndex][i] = temp;
				columnIndex++; //increment the column index to store the next value in the next column
			}
		}
	}
	return true;
}
//checks the sum of k number of matrixes in matrice(3Dvector)
//if atleast 1 sum is found return true
//if non combination is found return false
bool checkSum(vector<vector<vector<int>>> & matrices, vector<vector<vector<int>>> & temp, int firstNum, int secNum, int thirdNum, int fourthNum, int k){
	int counter = 0;
	bool checker = false;
	for(int i =0; i<matrices[0][0].size();i++){ //check sum for all matrixes 1 at a time
		for(int m=0;m<matrices[0].size();m++){ //look to next element in the column
			for(int j=0;j<matrices.size();j++){ //look to next elemt in the row
				//check sum depending on k
				//increament counter by 1 for each correct sum
				if(((temp[j][m][firstNum] + temp[j][m][secNum]) == matrices[j][m][i]) && (k==2)){
					counter++;
				}
				if(((temp[j][m][firstNum] + temp[j][m][secNum] + temp[j][m][thirdNum]) == matrices[j][m][i]) && (k==3)){
					counter++;
				}
				if(((temp[j][m][firstNum] + temp[j][m][secNum]+ temp[j][m][thirdNum] + temp[j][m][fourthNum]) == matrices[j][m][i]) && (k==4)){
					counter++;
				}
			}
		}
		//if there is a correct combination then the sum of all the elements of one matrix should be equal to the counter
		//prompt for correct k and increasing order only
		if(counter == (matrices[0].size() * matrices.size())){
			if((k==2) && (secNum > firstNum)){
				cout << "Matrix "<< i <<" can be written as the sum of matrices " << firstNum << " " << secNum << endl;
				checker = true;
			}
			if((k==3) && (secNum > firstNum) && (thirdNum > secNum)){
				cout << "Matrix "<< i <<" can be written as the sum of matrices " << firstNum << " " << secNum << " " << thirdNum << endl;
				checker = true;
			}
			if((k==4) && (secNum > firstNum) && (thirdNum > secNum) && (fourthNum > secNum)){
				cout << "Matrix "<< i <<" can be written as the sum of matrices " << firstNum << " " << secNum << " " << thirdNum << " " << fourthNum <<endl;
				checker = true;
			}
			counter =0;
		}
		counter=0;
	}
	return checker;
}
//copies the 1st parameter(3D vector) to the 2nd one(3D vector)
void matrixCopier(int num, vector<vector<vector<int>>> & matrices, vector<vector<vector<int>>> & temp){
	for(int i=0; i<matrices[0].size(); i++){
		for(int j=0;j<matrices.size();j++){
			temp[j][i][num]=matrices[j][i][num];
		}
	}
}

//make sets of all possible PERMUTATIONS for k elements of matrices
//the function will call checkSum and this function will only print the correct combination(increasing order)
//prompt message if no combinations found for k number
void combinationFinder(int k, int numberMatrices, int sizeRow, int sizeColumn, vector<vector<vector<int>>> & matrices, vector<vector<vector<int>>> & temp){
	//declared max number of possible k number, representing indexes of matrices
	int firstNum =0;
	int secNum=1;
	int thirdNum =2;
	int fourthNum=3;

	//check if all sets of matrices are tried with the element size of k
	bool kIsReached = false;
	//check if a correct combination is found
	bool combinationFound = false;

	while(!kIsReached){
		//for the entered k(2) value, copy 1st(index =0) and 2nd matrix(1)... to temp(3Dvector)
		//the indexes are initiated with the variables above(firstNum, secNum...)
		matrixCopier(firstNum, matrices, temp);
		matrixCopier(secNum,matrices, temp);
		matrixCopier(thirdNum, matrices, temp);
		matrixCopier(fourthNum,matrices, temp);
		//check the sum of the copied matrices in matrices(3D vector)
		if(checkSum(matrices, temp, firstNum, secNum, thirdNum, fourthNum,k)){
			combinationFound = true;
		}
		//increment the index of 1st matrix
		//the next loop will checkSum(1,1,2,3), continue this until (N,1,2,3)
		firstNum++;
		
		//after 1st matrix reaches N, set the index of 1st matrix(0) and increment the index of 2nd matrix
		//next loop will sumCheck(0,2,2,3)
		if(firstNum == numberMatrices){
			firstNum = 0;
			secNum++;
		}
		//if 2nd matrix reached N, set the index of it to 0
		//next loop will sumCheck(0,0,2,3) or finish the loop depending on k
		if(secNum == numberMatrices){
			secNum = 0;
		}
		//if 1st and 2nd numbers reach N and k=2 no more sets to check, number of k is reached, set it true
		if((secNum == 0) && (firstNum == 0) && (k==2)){ 
			kIsReached = true;
		}
		//if 1st and 2nd numbers reach N and k=3 the same operation wiil be done for 3rd number and 4th
		if((secNum == 0) && (firstNum == 0) && (k==3)){
			thirdNum++;
		}
		if((thirdNum == numberMatrices) && (k==3)){
			thirdNum = 0;
		}
		if((thirdNum == 0) && (secNum == 0) && (firstNum == 0) && (k==3)){
			kIsReached = true;
		}
		if((thirdNum == 0) && (secNum == 0) && (firstNum == 0) && (k==4)){
			fourthNum++;
		}
		if((fourthNum == numberMatrices) && (k==4)){
			fourthNum = 0;
		}
		if((fourthNum == 0) && (thirdNum == 0) && (secNum == 0) && (firstNum == 0) && (k==4)){
			kIsReached = true;
		}
	}
	//prompt for no valid combination found
	if(!combinationFound){
		cout << "There are no valid combinations in the given input file\n";
	}
}

int main(){
	//declared variables to read file
	ifstream input;
	string fileName, line;

	//variables for N, row size, column size and the user input(k)
	int numberMatrices = 0, sizeRow = 0, sizeColumn = 0, k;

	//open the file entered by user, ask for file name until correct one is entered
	cout << "Please enter the input file name: ";
	cin >> fileName;
	input.open(fileName.c_str());
	if(input.fail()){
		do{
			cout << "Invalid file name. Please enter again: ";
			cin >> fileName;
			input.open(fileName.c_str());
		}while(input.fail());
	}

	//read and store N, row and column size
	getline(input,line);
	istringstream input1(line);
	input1 >> numberMatrices;
	getline(input,line);
	istringstream input2(line);
	input2 >> sizeRow >> sizeColumn;

	//create 2, 3D matrices with the stored row,column size and number of matrices
	vector<vector<vector<int>>> matrices(sizeRow, vector<vector<int>>(sizeColumn,vector<int>(numberMatrices)));
	vector<vector<vector<int>>> temp(sizeRow, vector<vector<int>>(sizeColumn,vector<int>(numberMatrices,0)));

	//check if all the matrices are in the right size
	if(!checkMatrices(sizeRow, numberMatrices, input, matrices)){
		cout << "Invalid file.\n";
		return 0;
	}

	//prompt for k
	cout<<"Enter k:";
	cin>>k;

	//find all the combinations(N,k) that k of the matrices are equal to one other matrice.
	combinationFinder(k,numberMatrices,sizeRow, sizeColumn, matrices, temp);
	return 0;
}
