#ifndef HEADER_H
#define HEADER_H

// Global Constant
const int NUM_TESTS = 5;

// Enum Menu Options
enum MenuChoice {Add, Remove, Display, Search, Results, Quit};

//Struct Definition
struct Student
{
    string name;
    int studentID;
    int numTests;
    int* testScores;
};

// Function Prototypes
int getNumber();
void add_student();
void remove_student(int studentID);
void display();
void search(int studentID);
void exportResults();
int findMinimum(int* scores, int size);

#endif // HEADER_H