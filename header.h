#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

// Global Constant
const int NUM_TESTS = 5;

// Enum Menu Options
enum MenuChoice { Add = 1, Remove, Display, Search, Results, Quit };

// Struct Definition
struct Student
{
    string name;
    int studentID;
    int numTests;
    int* testScores;
    float average;
};

// Function Prototypes
int getNumber();
void add_student();                          
void remove_student(int studentID);
void display();
void search(int studentID);
void exportResults();
int findMinimum(const int* scores, int size);

#endif // HEADER_H
