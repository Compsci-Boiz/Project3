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

 // Open the student.dat file for reading.
    std::ifstream inFile("student.dat");
    if (!inFile) {
        std::cerr << "Error opening student.dat for reading." << std::endl;
        return;
    }

    // Open the averages.dat file for writing.
    std::ofstream outFile("averages.dat");
    if (!outFile) {
        std::cerr << "Error opening averages.dat for writing." << std::endl;
        return;
    }

    // Get the number of students from the getNumber function
    int numStudents = getNumber();

    // Create a dynamic array to store all student records
    Student* students = new Student[numStudents];

    // Read the student records from student.dat
    for (int i = 0; i < numStudents; ++i) {
        std::string line;
        std::getline(inFile, line); // Read each full line
        
        // Create a stringstream from the line for easier parsing
        std::stringstream ss(line);
        
        // Read the name (first name and last name)
        std::getline(ss, students[i].name, ',');
        
        // Read the student ID
        ss >> students[i].studentID;
        ss.ignore();  // Skip the comma after student ID
        
        // Read the number of tests
        ss >> students[i].numTests;
        ss.ignore();  // Skip the comma after numTests
        
        // Dynamically allocate memory for the test scores
        students[i].scores = new int[students[i].numTests];
        
        // Read the test scores
        for (int j = 0; j < students[i].numTests; ++j) {
            ss >> students[i].scores[j];
            ss.ignore();  // Skip the comma after each test score
        }
    }

    // Process each student record and calculate the average (excluding the minimum score)
    for (int i = 0; i < numStudents; ++i) {
        // Find the minimum score
        int minScore = findMinimum(students[i].scores, students[i].numTests);

        // Calculate the sum of the test scores, excluding the minimum score
        int totalScore = 0;
        for (int j = 0; j < students[i].numTests; ++j) {
            if (students[i].scores[j] != minScore) {
                totalScore += students[i].scores[j];
            }
        }

        // Compute the average (rounding to one decimal point)
        double average = static_cast<double>(totalScore) / (students[i].numTests - 1);
        
        // Write the student ID and the average to the averages.dat file
        outFile << students[i].studentID << " " << std::fixed << std::setprecision(1) << average << std::endl;
    }

    // Close the files
    inFile.close();
    outFile.close();

    // Clean up dynamically allocated memory
    for (int i = 0; i < numStudents; ++i) {
        delete[] students[i].scores;
    }
    delete[] students;

    std::cout << "Results exported to file." << std::endl;


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
