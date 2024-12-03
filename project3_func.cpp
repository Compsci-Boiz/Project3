#include "header.h"


// Functions

void add_student() 
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

    fout << endl<< newStudent.name << "," << newStudent.studentID << "," << newStudent.numTests;
    for (int i = 0; i < newStudent.numTests; i++) 
    {
        fout << "," << newStudent.testScores[i];
    }
    fout << "," << endl;

    delete[] newStudent.testScores;
    fout.close();
}

void remove_student(int studentID) 
{
     ifstream fin("student.dat");
    ofstream fout("temp.dat");
    if (fin.fail() || fout.fail()) 
    {
        cout << "File error." << endl;
        return;
    }

    int numStudents = getNumber();  // Get the number of students
    if (numStudents <= 0)
    {
        cout << "No student records to process.\n";
        fin.close();
        fout.close();
        return;
    }

    bool found = false;
    string line;
    Student* students = new Student[numStudents];

    // Read all student data from file
    for (int i = 0; i < numStudents; i++) {
        if (!getline(fin, line)) {
            cout << "Error: Unable to read data for student #" << (i + 1) << ".\n";
            break;
        }

        stringstream ss(line);
        string temp;

        // Parse name
        students[i].name.clear();
        while (getline(ss, temp, ',')) {
            try {
                students[i].studentID = stoi(temp);  // If it's a number, it's the student ID
                break;  // Stop appending to the name once the ID is found
            } catch (const invalid_argument&) {
                if (!students[i].name.empty())
                    students[i].name += ", ";
                students[i].name += temp;
            }
        }

        // Parse number of tests
        if (!getline(ss, temp, ',') || temp.empty()) {
            cout << "Error: Missing or invalid number of tests for student #" << (i + 1) << ".\n";
            continue;
        }
        try {
            students[i].numTests = stoi(temp);
        } catch (const invalid_argument&) {
            cout << "Error: Invalid number of tests for student #" << (i + 1) << ".\n";
            continue;
        }

        // Parse test scores
        students[i].testScores = new int[students[i].numTests];
        for (int j = 0; j < students[i].numTests; j++) {
            if (!getline(ss, temp, ',') || temp.empty()) {
                students[i].testScores[j] = 0; // Default to 0 for missing scores
                continue;
            }
            try {
                students[i].testScores[j] = stoi(temp);
            } catch (const invalid_argument&) {
                students[i].testScores[j] = 0; // Default to 0 for invalid scores
            }
        }

        // If the current student ID matches the one to be removed, skip writing to the file
        if (students[i].studentID == studentID) {
            found = true;
        } else {
            fout << students[i].name << "," << students[i].studentID << "," << students[i].numTests;
            for (int j = 0; j < students[i].numTests; j++) {
                fout << "," << students[i].testScores[j];
            }
            fout << endl;
        }

        delete[] students[i].testScores; // Clean up memory
    }

    if (!found) {
        cout << "Student with ID " << studentID << " does not exist.\n";
    }

    fin.close();  // Close the input file
    fout.close(); // Close the output file
    delete[] students; // Free the dynamic array of students

    // Replace the original file with the temp file
    remove("student.dat");  // Delete the original file
    rename("temp.dat", "student.dat");  // Rename the temp file to the original name
}

void display()
{
    ifstream fin("student.dat");
    if (fin.fail())
    {
        cout << "Error: Could not open the file for reading.\n";
        return;
    }

    int numStudents = getNumber();
    if (numStudents <= 0)
    {
        cout << "No student records to display.\n";
        fin.close();
        return;
    }

    Student* students = new Student[numStudents];
    string line;

    // Read student data
    for (int i = 0; i < numStudents; i++)
    {
        if (!getline(fin, line))
        {
            cout << "Error: Unable to read data for student #" << (i + 1) << ".\n";
            break;
        }

        stringstream ss(line);
        string temp;

        // Parse name
        students[i].name.clear();
        while (getline(ss, temp, ','))
        {
            // Check if the current `temp` is a numeric value (student ID)
            try
            {
                students[i].studentID = stoi(temp); // If this works, it's the ID
                break; // Stop appending to the name once the ID is found
            }
            catch (const invalid_argument&)
            {
                // If it's not a number, append it to the name
                if (!students[i].name.empty())
                    students[i].name += ", ";
                students[i].name += temp;
            }
        }

        // Parse number of tests
        if (!getline(ss, temp, ',') || temp.empty())
        {
            cout << "Error: Missing or invalid number of tests for student #" << (i + 1) << ".\n";
            continue;
        }
        try
        {
            students[i].numTests = stoi(temp);
        }
        catch (const invalid_argument&)
        {
            cout << "Error: Invalid number of tests for student #" << (i + 1) << ".\n";
            continue;
        }

        // Parse test scores
        students[i].testScores = new int[students[i].numTests];
        for (int j = 0; j < students[i].numTests; j++)
        {
            if (!getline(ss, temp, ',') || temp.empty())
            {
                cout << "Error: Missing or invalid test score for student #" << (i + 1) << ".\n";
                students[i].testScores[j] = 0; // Default to 0 for missing scores
                continue;
            }
            try
            {
                students[i].testScores[j] = stoi(temp);
            }
            catch (const invalid_argument&)
            {
                cout << "Error: Invalid test score for student #" << (i + 1) << ".\n";
                students[i].testScores[j] = 0; // Default to 0 for invalid scores
            }
        }
    }

    // Display student data
    cout << left << setw(30) << "Name"
         << setw(15) << "Student ID"
         << setw(5) << "Scores\n";
    cout << string(60, '-') << endl;

    for (int i = 0; i < numStudents; i++)
    {
        if (students[i].testScores == nullptr) continue; // Skip invalid students

        cout << left << setw(30) << students[i].name
             << setw(15) << students[i].studentID;

        for (int j = 0; j < students[i].numTests; j++)
        {
            cout << setw(5) << students[i].testScores[j];
        }
        cout << endl;

        delete[] students[i].testScores; // Free memory for test scores
    }

    delete[] students; // Free memory for student array
    fin.close(); // Close the file
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

int findMinimum(const int* scores, int size) 
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

int getNumber()
{
	ifstream fin;
	fin.open("student.dat");
	if (fin.fail())
	{
		cout<<"File error."<<endl;
		exit(1);
	}
	int count=0;
	string line;
	while(!fin.eof())
	{
		getline(fin, line);
		++count;
	}
	
	fin.close();
	
	cout << "Number of students = " << count << endl;
	return(count);
	
}
