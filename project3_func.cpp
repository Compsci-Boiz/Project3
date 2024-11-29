#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
using namespace std;

// Global constants
const int NUM_TESTS = 5;

enum MenuChoice { Add = 1, Remove, Display, Search, Results, Quit };

// Structure definition
struct Student 
{
    string name;
    int studentID;
    int numTests;
    int* testScores;
};

// Function prototypes
int getNumber();
void add_Student();
void remove_Student(int studentID);
void display();
void search(int studentID);
void exportResults();
int findMinimum(int* scores, int size);

// Functions

void add_Student() 
{
    ofstream fout;
    fout.open("student.dat", ios::app);
    if (fout.fail()) 
    {
        cout << "Error opening file." << endl;
        return;
    }

    Student newStudent;
    cout << "Enter last name of the student: ";
    cin >> newStudent.name;
    cout << "Enter first name of the student: ";
    string firstName;
    cin.ignore();
    getline(cin, firstName);
    newStudent.name += " " + firstName;

    cout << "Enter student ID: ";
    cin >> newStudent.studentID;

    cout << "How many tests did this student take? ";
    cin >> newStudent.numTests;

    newStudent.testScores = new int[newStudent.numTests];
    for (int i = 0; i < newStudent.numTests; i++) 
    {
        cout << "Enter score #" << i + 1 << ": ";
        cin >> newStudent.testScores[i];
    }

    fout << newStudent.name << "," << newStudent.studentID << "," << newStudent.numTests;
    for (int i = 0; i < newStudent.numTests; i++) 
    {
        fout << "," << newStudent.testScores[i];
    }
    fout << "," << endl;

    delete[] newStudent.testScores;
    fout.close();
}

void remove_Student(int studentID) 
{
    ifstream fin("student.dat");
    ofstream fout("temp.dat");
    if (fin.fail() || fout.fail()) 
    {
        cout << "File error." << endl;
        return;
    }

    bool found = false;
    int numStudents = getNumber();
    Student* students = new Student[numStudents];

    for (int i = 0; i < numStudents; i++) {
        fin >> students[i].name >> students[i].studentID >> students[i].numTests;
        students[i].testScores = new int[students[i].numTests];
        for (int j = 0; j < students[i].numTests; j++) 
        {
            fin >> students[i].testScores[j];
        }

        if (students[i].studentID == studentID) 
        {
            found = true;
        } else 
        {
            fout << students[i].name << "," << students[i].studentID << "," << students[i].numTests;
            for (int j = 0; j < students[i].numTests; j++) 
            {
                fout << "," << students[i].testScores[j];
            }
            fout << "," << endl;
        }

        delete[] students[i].testScores;
    }

    if (!found) 
    {
        cout << "Student does not exist." << endl;
    }

    fin.close();
    fout.close();
    delete[] students;

    remove("student.dat");
    rename("temp.dat", "student.dat");
}

void display() 
{
    ifstream fin("student.dat");
    if (fin.fail()) 
    {
        cout << "File error." << endl;
        return;
    }

    int numStudents = getNumber();
    Student* students = new Student[numStudents];

    for (int i = 0; i < numStudents; i++) 
    {
        fin >> students[i].name >> students[i].studentID >> students[i].numTests;
        students[i].testScores = new int[students[i].numTests];
        for (int j = 0; j < students[i].numTests; j++) 
        {
            fin >> students[i].testScores[j];
        }

        cout << left << setw(30) << students[i].name
             << setw(15) << students[i].studentID;
        for (int j = 0; j < students[i].numTests; j++) 
        {
            cout << setw(5) << students[i].testScores[j];
        }
        cout << endl;

        delete[] students[i].testScores;
    }

    delete[] students;
    fin.close();
}

void search(int studentID) 
{
    ifstream fin("student.dat");
    if (fin.fail()) 
    {
        cout << "File error." << endl;
        return;
    }

    bool found = false;
    Student student;
    while (fin >> student.name >> student.studentID >> student.numTests) 
    {
        student.testScores = new int[student.numTests];
        for (int i = 0; i < student.numTests; i++) 
        {
            fin >> student.testScores[i];
        }

        if (student.studentID == studentID) 
        {
            found = true;
            cout << left << setw(30) << student.name
                 << setw(15) << student.studentID;
            for (int i = 0; i < student.numTests; i++) 
            {
                cout << setw(5) << student.testScores[i];
            }
            cout << endl;
        }

        delete[] student.testScores;
        if (found) break;
    }

    if (!found) 
    {
        cout << "Student does not exist." << endl;
    }

    fin.close();
}

void exportResults() 
{
    ifstream fin("student.dat");
    ofstream fout("averages.dat");
    if (fin.fail() || fout.fail()) 
    {
        cout << "File error." << endl;
        return;
    }

    int numStudents = getNumber();
    Student* students = new Student[numStudents];

    for (int i = 0; i < numStudents; i++) 
    {
        fin >> students[i].name >> students[i].studentID >> students[i].numTests;
        students[i].testScores = new int[students[i].numTests];
        for (int j = 0; j < students[i].numTests; j++) 
        {
            fin >> students[i].testScores[j];
        }

        int total = 0;
        for (int j = 0; j < students[i].numTests; j++) 
        {
            total += students[i].testScores[j];
        }
        int minScore = findMinimum(students[i].testScores, students[i].numTests);
        float average = (students[i].numTests > 1) ? (total - minScore) / (students[i].numTests - 1) : 0;

        fout << students[i].studentID << " " << fixed << setprecision(1) << average << endl;
        delete[] students[i].testScores;
    }

    delete[] students;
    fin.close();
    fout.close();
}

int findMinimum(int* scores, int size) 
{
    if (size < NUM_TESTS) return 0;

    int minScore = scores[0];
    for (int i = 1; i < size; i++) 
    {
        if (scores[i] < minScore) 
        {
            minScore = scores[i];
        }
    }
    return minScore;
}
