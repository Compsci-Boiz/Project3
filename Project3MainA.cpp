#include "header.h"
#include<iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
using namespace std;


int main(){
  //local variables
  int studentID = 0;
  bool cont = true;


   // Project Title Printout
	cout<< "+---------------------------------------------------------------+" << endl;
	cout<< "|\tComputer Science and Engineering\t\t\t|" << endl;
	cout<< "|\tCSCE 1030 - Project 3\t\t\t\t\t|" << endl;
	cout<< "|\tRamon Lopez rjl0157 ramonlopez2@my.unt.edu\t\t|" << endl;
	cout<< "|\tEnrique Gutierrez eeg012 enriqueGutierrez@my.unt.edu]\t|" << endl;
	cout<< "|\tChris Mataya cdm0499 chrismataya@my.unt.edu\t\t|" << endl;
	cout<< "|\tKenneth Roland ker0238 kennethroland@my.unt.edu\t\t|" << endl;
	cout<< "+---------------------------------------------------------------+" << endl;


  // application loop, ends when cont is set to false
  while(cont){

    cout << "\n1. Add\n2. Remove\n3. Display\n4. Search\n  \n5. Results \n6.Quit";
    int choice;
    cout << "What do you want to do? ";
    cin >> choice; //would choice instead be MenuOption?

    switch(choice){

        case Add: // calls the add_Student function
          add_Student();
          break;
          
        case Remove: // calls the remove_student funtion
          cout << "Enter ID of student to remove: ";
          cin >> Student.id;
          remove_Student(Student.id);
          break;
          
        case Display: // calls the display function
          display();
          break;
          
        case Search: // calls the search function
          cout << "Enter ID of student to find: ";
          cin >> Student.id;
          search(Student.id);
          break;
          
        case Results: // calls the exportResults function
          exportResults();
          break;
          
        case Quit: // sets cont to false
          cont = false;
          cout << "BYE!!!\n";
          break;
        
        default: // invalid input catch
          cout << "Invalid choice. Please select again.\n";

    }

  }
  

return 0;
  
}


void add_Student()
{
cout << "Enter first and last name" << endl;
getline(cin, Student.name);  //check name variable

cout << "Enter student ID" << endl;
cin >> Student.id;

cout << "Enter number of tests taken" << endl;
cin >> Student.numTests;

student.testScores = new int[student.numTests]; // Initialized dynamic array
	
cout << "Enter test scores" << endl; //perhaps this should go in the for loop
for(int i = 0; i < student.numTests; ++i) //to iterate through i
	{
  cout << "Score " << (i+1) << ": ";
	cin >> student.testScores[i]; //Lowkey having a brain fart since an int pointer was already declared in the project3_func file
		}//fuck ass mystery bracket
	}	
}

void remove_Student(int Student.id//check this)
{
cout << "Enter student ID" << endl;
cin >> Student.id;

getNumber();
//create a dynamic array of student type
//copy all data except the record with the specified ID back to student.dat
}

void display()
{
	ifstream fin; //might need to go elsewhere
  ofstream fout; // May be subjected to change 
	fin.open(//some data file for reading)
		if(fin.fail())
		{
		cout << "File Error" << endl;
		exit(1)
		}

    fout.open(//Desired File Name);
    if(fout.fail()){
      cout << "Error: Could not create output file.";
      exit(1);
    }

    fout << left << setw(30) << "Name:" << setw(15) << "ID:"; 
    // Still need a second loop, and the way I allocated the spaces may be incorrect.
    fin.close();
    fout.close();

    
//using a second loop, display the contents of the array in the following format:
	//allocate 30 spaces for the entire name, allocate 15 spaces for the student id, allocate 5 spaces for each test score
	//you dont need to display the number of tests
}
	
	
	getNumber();

	for() //to print student details in a formatted table
	{
		cout << //go through some array?
	}
	fin.close();	
}


void search(int Student.id//also check this)
{
cout << "Enter student ID" << endl;
//read through the file to find and display matching records
	
}

void exportResults()
{
ifstream fin;   //should this go elsewhere?
fin.open("averages.dat"); //for writing
	if(fin.fail())
	{
	cout << "File Error" << endl;
	exit(1);
	}
//calculate each student's average after removing the lowest score
//write student ID's and averages to averages.dat
}

int findMinimum(//array of integers, size of the array)
{
//return the smallest test score from an array
//if fewer than 5 tests, return 0 as the minimum
	if(numTests < 5) //drafting 
	{
	minimum = 0;
	}
}

