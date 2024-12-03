#include "header.h"


int main() 
{
    // Local variables
    bool cont = true;

    // Project Title Printout
    cout << "+---------------------------------------------------------------+" << endl;
    cout << "|\tComputer Science and Engineering\t\t\t|" << endl;
    cout << "|\tCSCE 1030 - Project 3\t\t\t\t\t|" << endl;
    cout << "|\tRamon Lopez rjl0157 ramonlopez2@my.unt.edu\t\t|" << endl;
    cout << "|\tEnrique Gutierrez eeg012 enriqueGutierrez@my.unt.edu\t|" << endl;
    cout << "|\tChris Mataya cdm0499 chrismataya@my.unt.edu\t\t|" << endl;
    cout << "|\tKenneth Roland ker0238 kennethroland@my.unt.edu\t\t|" << endl;
    cout << "+---------------------------------------------------------------+" << endl;

    // Application loop, ends when cont is set to false
    while (cont) 
    {
        cout << "\n1. Add\n2. Remove\n3. Display\n4. Search\n5. Results\n6. Quit\n";
        int choice;
        cout << "What do you want to do? ";
        cin >> choice;

        switch (choice) 
        {
            case Add: 
            {
                add_student(); // Call the add student function
                break;
            }

            case Remove: 
            {
                int studentID;
                cout << "Enter ID of student to remove: ";
                cin >> studentID;
                remove_student(studentID); // Pass the student ID to remove function
                break;
            }

            case Display: 
            {
                display(); // Call the display function
                break;
            }

            case Search: 
            {
                int studentID;
                cout << "Enter ID of student to find: ";
                cin >> studentID;
                search(studentID); // Pass the student ID to the search function
                break;
            }

            case Results: 
            {
                exportResults(); // Call the export results function
                break;
            }

            case Quit: 
            {
                cont = false; // Exit the loop
                cout << "BYE!!!\n";
                break;
            }

            default: 
            {
                cout << "Invalid choice. Please select again.\n";
                break;
            }
        }
    }

    return 0;
}
