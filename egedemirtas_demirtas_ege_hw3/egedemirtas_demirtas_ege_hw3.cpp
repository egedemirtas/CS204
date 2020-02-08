#include <iostream>
#include <string>
#include <fstream> //for getLine(), creating ifstream inputs
#include <sstream> 
using namespace std;

//taken from hw3 description
//modification:deleted the constructor with parameter since it is not needed
struct lectureNode{
	string lectureName;
	lectureNode *next;
	lectureNode()
	{
		lectureName = "";
		next = NULL;
	}
};
//taken from hw3 description, 
//modifications: changed type of id to string type, 
			   //added another pointer(with type Student) to create a linked list(used for queue) of students
			   //deleted constructor with parameters, since it is not needed
struct Student{
	string name;
	string id;
	lectureNode *lectures;
	Student *next; //for student queue
	Student()
	{
		name = "";
		id = "0";
		lectures = NULL;
		next = NULL;
	}
};
//constructor to build a linked list for the lectures(lectures in the lecture file)
struct LectureList{
	string nameCode;
	int capacity;
	LectureList *next;

	LectureList(){
		nameCode = "";
		next= NULL;
		capacity = 0;
	}
};

// assignes students to their lectures with round robin algorithm
void roundRobinQueue(Student * & initialS, LectureList * & initialL){
	Student *tailStudent = initialS; //created a tail for student queue to pass to the next student when the lecture has been assigned
	while(1){ //this loop will end only if all the students' lectures has been processed/assigned
		LectureList *ptr = initialL; //a pointer pointing to head of LectureList, to find the desired lecture for the student
		if(tailStudent->lectures != NULL){ //continue assigning operation if the student has a lectureNode
			while(ptr){
				if(tailStudent->lectures->lectureName == ptr->nameCode){ //if the ptr shows the same lecture as the student's lecture,
					if(ptr->capacity > 0){ //assign if capacity left
						cout << ptr->nameCode << " is assigned to " << tailStudent->name << "(" << tailStudent->id << ")\n"; //proper prompt
						ptr->capacity = (ptr->capacity) - 1; //decrease capacity of the lecture
						tailStudent->lectures = tailStudent->lectures->next; //since the student's lecture has been assigned, student should show his/her next wished lecture for the next queue round
						break; //stop searching for the lecture since student is assigned
					}else{//dont assign if no capacity left
						cout << ptr->nameCode << " can not be assigned to " << tailStudent->name << "(" << tailStudent->id << ")\n";//proper prompt
						tailStudent->lectures = tailStudent->lectures->next; //since the student's lecture can not assigned, student now should show his/her next wished lecture for the next queue round
						break; //stop searching for the lecture since student can not be assigned
					}
				}else{
					LectureList *ptr2 = initialL;
					bool nameChecker = false;
					while(ptr2){ //if there is no matching lectures between student's and lectureList, record it in nameChecker
						if(tailStudent->lectures->lectureName == ptr2->nameCode){
							nameChecker = true;
						}
						ptr2 = ptr2 -> next;
					}
					if(!nameChecker){ //if no matchign names are found between student's and lectureList, prompt that student can not be assigned to his/her lecture
						cout << tailStudent->lectures->lectureName << " can not be assigned to " << tailStudent->name << "(" << tailStudent->id << ")\n";
						tailStudent->lectures = tailStudent->lectures->next;
						break;
					}
				}
				ptr = ptr->next; //seek for the next lecture in LectureList
			}
		}
		if(tailStudent->next == NULL){ //if tail reached the end of the list of students, make the last student point to head of the student list.
									   //Otherwise we would go through the student queue once, matching only one lecture per student
			tailStudent->next = initialS; 
		}
		bool checker = false;
		Student *lectureChecker = tailStudent; 
		while(!checker){ //check if all students' lectures has been assigned/ or processed.
			if(lectureChecker->lectures != NULL){// lectureChecker->lectures would show NULL if a student's desired lectures has been all processed
				checker = true;
			}
			lectureChecker = lectureChecker->next;
		}
		if(!checker){ //if all the student's lectures has been processed end the while loop
			break;
		}
		tailStudent = tailStudent->next; //go to the next student for matching
	}
}

void parseLectureFile(ifstream & inputLectures, LectureList * & initial){
	string lines;
	LectureList *tailforLectureList = initial;
	while (getline(inputLectures, lines)){
		if(lines == "<lecture>"){ //indication that a lecture is defined in file
			if(initial->capacity == 0){//if initial node is empty, first fill it
				while(getline(inputLectures, lines)){
					if(lines.find("<name>") != string::npos){
						tailforLectureList->nameCode = lines.substr(7, lines.find("</name>") - 7); //store name
					}
					if(lines.find("<capacity>") != string::npos){
						tailforLectureList->capacity = stoi(lines.substr(11, lines.find("</capacity>") - 11)); //store capacity
					}
					if(lines.find("</lecture>") != string::npos){
						break;
					}
				}
			}else{ //if the lectureList is not empty, create a new node and connect to the list
				LectureList *latestLecture = new LectureList;//create a new node
				while(getline(inputLectures, lines)){
					if(lines.find("<name>") != string::npos){
						latestLecture->nameCode = lines.substr(7, lines.find("</name>") - 7);
					}
					if(lines.find("<capacity>") != string::npos){
						latestLecture->capacity = stoi(lines.substr(11, lines.find("</capacity>") - 11));
					}
					if(lines.find("</lecture>") != string::npos){
						tailforLectureList->next = latestLecture; //connect to the list
						tailforLectureList = latestLecture;
						break;
					}
				}
			}
		}
	}
}

void parseStudentFile(ifstream & inputStudent, Student * & initial){
	string lines;
	string id;
	string name;
	Student *tailforStu = initial;//a tail to track students, beggign with the head of the student linked list

	while (getline(inputStudent,lines)){ //iterate until a student declaration is found
		if(lines == "<student>"){ //meaning that a student has been declared in the file
			if(initial->id == "0"){ //if the head of student list is empty, this should be filled first
				lectureNode *latestLecture = new lectureNode; //since a student has been declared in the file, a pointer of type lectureNode is created to store the student's wished lectures in a linked list
				lectureNode *tailforLec = latestLecture;
				while (getline(inputStudent,lines)){ //iterate until a name or an id or a course declaration is found
					if(lines.find("<name>") != string::npos){
						tailforStu->name = lines.substr(7, lines.find("</name>") - 7); //store name
					}
					if(lines.find("<id>") != string::npos){
						tailforStu->id = lines.substr(5, lines.find("</id>") - 5); //store id
					}
					if(lines.find("<lecture>") != string::npos){
						if(latestLecture->lectureName == ""){ //if a lectureNode has been created but empty, this should be processed first
							tailforLec->lectureName = lines.substr(10, lines.find("</lecture>") - 10); //store lecture's name
							tailforStu->lectures = tailforLec; //connect the student to the it's lectureNode
						}else{ //add a node to student's lectureNode
							lectureNode *addLecture = new lectureNode;
							addLecture->lectureName = lines.substr(10, lines.find("</lecture>") - 10); //store course
							tailforLec->next = addLecture;
							tailforLec = addLecture;
						}
					}
					if(lines.find("</student>") != string::npos){ // end the loop if the student declarion has ended
						break;
					}
				}
			}else{ //if the head of student list has already been processed(filled with info)
				Student *latestStudent = new Student; //create a new student to store id, name, and connect a lecture node
				lectureNode *latestLecture1 = new lectureNode; //create a sigly linked list for lectures
				latestStudent->lectures = latestLecture1; //connect student to lecture list
				lectureNode *tailforLec1 = latestLecture1; //trace the end point of lecture list to add a new lecture to the end
				tailforStu->next = latestStudent; //connect the new created student to the linked list of students(for queue)
				tailforStu = latestStudent;
				while (getline(inputStudent,lines)){ //iterate until a name or an id or a course declaration is found
					if(lines.find("<name>") != string::npos){
						tailforStu->name = lines.substr(7, lines.find("</name>") - 7); //store name
					}
					if(lines.find("<id>") != string::npos){
						tailforStu->id = lines.substr(5, lines.find("</id>") - 5); //store id
					}
					if(lines.find("<lecture>") != string::npos){
						if(latestLecture1->lectureName == ""){
							tailforLec1->lectureName = lines.substr(10, lines.find("</lecture>") - 10); //store course
							tailforStu->lectures = tailforLec1;
						}else{
							lectureNode *addLecture = new lectureNode;
							addLecture->lectureName = lines.substr(10, lines.find("</lecture>") - 10); //store course
							tailforLec1->next = addLecture;
							tailforLec1 = addLecture;
						}
					}
					if(lines.find("</student>") != string::npos){ // end the loop if the student declarion has ended
						break;
					}
				}
			}
		}
	}
}

bool checkFileFormatStudent(ifstream & input){
	string lines;
	while(getline(input,lines)){
		if(lines == "<student>"){ //means that a student has been declared in file
			int idCounter =0, nameCounter =0;
			while(getline(input,lines)){
				if(lines.find("<name>") != string::npos){ //if a line has been started with <name>, must finish with </name>, other wise return false
					nameCounter++;
					if(lines.find("</name>") == string::npos){
						return false;
					}
				}else if(lines.find("<id>") != string::npos){ //if a line has been started with <id>, must finish with </id>, other wise return false
					idCounter++;
					if(lines.find("</id>") == string::npos){
						return false;
					}
				}else if(lines.find("<lecture>") != string::npos){ //if a line has been started with <lecture>, must finish with </lecture>, other wise return false
					if(lines.find("</lecture>") == string::npos){
						return false;
					}
				}else if(idCounter>1){ //return false if there is more than 1 id(a student can only have 1 id)
					return false;
				}else if(nameCounter>1){//return false if there is more than 1 name(a student can only have 1 name)
					return false;
				}else if(lines == "</student>" && (idCounter ==0) &&(nameCounter==0)){//if student declariton is finished but there is no id or name return false
					return false;
				}else if(lines == "<student>"){ //return false if a student is declared before the previous student finished(reached </student>)
					return false;
				}else if(lines == "</student>"){//if student declariton is finished search for the next student
					break;
				}
			}
		}
	}
	input.clear();//go to the beginning of the file
	input.seekg(0);
}

bool checkFileFormatLecture(ifstream & input){
	string lines;
	while(getline(input,lines)){
		if(lines == "<lecture>"){ //a lecture has been defined in the file
			int countCapacity =0, nameCounter =0;
			while(getline(input,lines)){
				if(lines.find("<name>") != string::npos){//if a line has been started with <name>, must finish with </name>, other wise return false
					nameCounter++;
					if(lines.find("</name>") == string::npos){
						return false;
					}
				}else if(lines.find("<capacity>") != string::npos){//if a line has been started with <capacity>, must finish with </capacity>, other wise return false
					countCapacity++;
					if(lines.find("</capacity>") == string::npos){
						return false;
					}
				}else if(countCapacity>1){ //return false if there is more than 1 capacity declared
					return false;
				}else if(nameCounter>1){//return false if there is more than 1 name for a single lecture
					return false;
				}else if(lines == "</lecture>" && (countCapacity ==0) &&(nameCounter==0)){//if student declariton is finished but there is no capacity or name return false
					return false;
				}else if(lines == "<lecture>"){ //return false if a lecture is declared before the previous lecture finished
					return false;
				}else if(lines == "</lecture>"){//if lecture declariton is finished search for the next lecture
					break;
				}
			}
		}
	}
	input.clear();//go to the beginning of the file
	input.seekg(0);
}

int main(){
	string studentFile, lectureFile;
	ifstream inputStudent, inputLectures;
	Student *initialS = new Student; //create an head pointer, pointing to first student with empty info
	LectureList *initialL = new LectureList; 

	do{
		cout << "Please enter the name of the Student XML file: "; //propmt to ask for a file to open until correct one has been entered
		cin >> studentFile;
		inputStudent.open(studentFile.c_str());
		if(inputStudent.fail()){
			cout << "Invalid file name.\n";
		}
	}while(inputStudent.fail());

	do{
		cout << "Please enter the name of the Lectures XML file: "; //propmt to ask for a file to open until correct one has been entered
		cin >> lectureFile;
		inputLectures.open(lectureFile.c_str());
		if(inputLectures.fail()){
			cout << "Invalid file name.\n";
		}
	}while(inputLectures.fail());

	if(!checkFileFormatStudent(inputStudent)){ //check if student file is in right format
		cout << "Invalid XML format!.. Exiting." ;
		cin.get();
		cin.ignore();
		return 0;
	}
	if(!checkFileFormatLecture(inputLectures)){//check if lecture file is in right format
		cout << "Invalid XML format!.. Exiting." ;
		cin.get();
		cin.ignore();
		return 0;
	}
	parseStudentFile(inputStudent, initialS);
	parseLectureFile(inputLectures, initialL);
	roundRobinQueue(initialS, initialL);

	cin.get();
	cin.ignore();
	return 0;
}