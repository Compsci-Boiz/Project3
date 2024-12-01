#include "project3_func.h"

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

    cout << "\n1. Match\n2. Display\n3. Giveup\n4. Exit\n";
    int choice;
    cout << "What do you want to do? ";
    cin >> choice;

    switch(choice){

        case Add: // calls the add_Student function
          add_Student();
          break;
          
        case Remove: // calls the remove_student funtion
          cout << "Enter ID of student to remove: ";
          cin << studentID;
          remove_Student(studentID);
          break;
          
        case Display: // calls the display function
          display();
          break;
          
        case Search: // calls the search function
          cout << "Enter ID of student to find: ";
          cin << studentID;
          search(studentID);
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
