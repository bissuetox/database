#include "Database.h"
#include <exception>
// #include <string.h>
#include <sstream>
#define STUDENT_PATH "./db/studentTable.csv"
#define FACULTY_PATH "./db/facultyTable.csv"

Database::Database() {

}

void Database::setup() {
    string read;

    // Import student data
    fp.openRead(STUDENT_PATH);
    // If file exists and is open, try to scan it in
    if (fp.isOpenRead()) {
        while(fp.getLine(read)) {
            // Ignore comments with '#'
            if (read.at(0) == '#') {
                continue;
            } else {
                parseAddStudent(read);
            }
        }
    }

    // Import faculty data
    fp.openRead(FACULTY_PATH);
    // If file exists and is open, try to scan it in
    if (fp.isOpenRead()) {
        while(fp.getLine(read)) {
            // Ignore comments with '#'
            if (read.at(0) == '#') {
                continue;
            } else {
                // parseAddFaculty(read);
            }
        }
    }
}

void Database::interfaceLoop() {
    int choiceInt;
    string choiceStr;

    // Main Loop
    do {
        printOptions();

        // Catch invalid input
        try {
            getline(cin, choiceStr);
            choiceInt = stoi(choiceStr);
            ingestChoice(choiceInt);
        } catch(invalid_argument) {
            cout << "ERROR: Invalid input!" << endl;
            choiceInt = -1; // Set to -1 to re prompt
        }

    } while(choiceInt != 14);
}

// Processes the user's choice
void Database::ingestChoice(int choiceInt) {
    switch(choiceInt) {
        case 1:
            printAllStudents();
            break;
        case 2:
            printAllFaculty();
            break;
        case 3:
            // findStudent();
            break;
        case 4:
            // findFaculty();
            break;
        case 5:
           // findStudentsAdvisor(); 
           break;
        case 6:
            // findFacultysAdvisees();
            break;
        case 7:
            promptAddStudent();
            break;
        case 8:
            // deleteStudentById();
            break;
        case 9:
            promptAddFaculty();
            break;
        case 10:
            // deleteFacultyById();
            break;
        case 11:
            // changeStudentsAdvisor();
            break;
        case 12:
            // removeAdviseeFromFaculty();
            break;
        case 13:
            // rollback();
            break;
        case 14:
            // Outside function will exit
            break;
        default:
            throw invalid_argument("Invalid choice entered.");
    }
}

// Helper function to return string of options
void Database::printOptions() {
    string options = "Enter an option below:\n";
    options += "1. Print all students and their information (sorted by ascending id #)\n";
    options += "2. Print all faculty and their information (sorted by ascending id #)\n";
    options += "3. Find and display student information given the students id\n";
    options += "4. Find and display faculty information given the faculty id\n";
    options += "5. Given a student’s id, print the name and info of their faculty advisor\n";
    options += "6. Given a faculty id, print ALL the names and info of his/her advisees.\n";
    options += "7. Add a new student\n";
    options += "8. Delete a student given the id\n";
    options += "9. Add a new faculty member\n";
    options += "10. Delete a faculty member given the id.\n";
    options += "11. Change a student’s advisor given the student id and the new faculty id.\n";
    options += "12. Remove an advisee from a faculty member given the ids\n";
    options += "13. Rollback\n";
    options += "14. Exit\n";
    cout << options << "> ";
}

// Prints all students in masterStudent
void Database::printAllStudents() {
    if (masterStudent.getNumNodes() == 0) {
        cout << "No Students in the Database!" << endl;
    } else {
        masterStudent.printNodes();
    }
}

// Prints all faculty in masterFaculty
void Database::printAllFaculty() {
    if (masterFaculty.getNumNodes() == 0) {
        cout << "No Faculty in the Database!" << endl;
    } else {
        masterFaculty.printNodes();
    }
}

// Adds a student to masterStudent
void Database::addStudent(int id, string name, string level, string major, double gpa, int advisor_id) {
    Student* newStudent = new Student(id, name, level, major, gpa, advisor_id);
    masterStudent.insert(newStudent);
}

// Prompts user for student data then adds it to masterStudent
void Database::promptAddStudent() {
    string name, level, major, id_str, advisor_id_str, gpa_str;
    int id, advisor_id;
    double gpa;
    bool success = false;
    while (!success) {
        try {
            success = true;
            cout << "Enter student ID: \n> ";
            getline(cin, id_str);
            id = stoi(id_str);

            cout << "Enter student name: \n> ";
            getline(cin, name);

            cout << "Enter student grade: \n> ";
            getline(cin, level);

            cout << "Enter student major: \n> ";
            getline(cin, major);

            cout << "Enter student GPA: \n> ";
            getline(cin, gpa_str);
            gpa = stod(gpa_str);

            if (masterFaculty.getNumNodes() == 0) {
                cout << "No faculty available, assigning -1 for advisor ID." << endl;
                advisor_id = -1;
            } else {
                cout << "Enter student's advisor ID: \n> ";
                getline(cin, advisor_id_str);
                advisor_id = stoi(advisor_id_str);
                Faculty dummyFaculty(advisor_id, "", "", "");
                if (!masterFaculty.contains(&dummyFaculty)) {
                    throw(invalid_argument("Faculty ID not in masterFaculty"));
                }
            }

            addStudent(id, name, level, major, gpa, advisor_id);
        } catch (invalid_argument) {
            cout << "Invalid input! Try again." << endl << endl;
            success = false;
        }
    }
}

void Database::parseAddStudent(string line) {
    stringstream lineStream(line);
    string name, level, major, id_str, advisor_id_str, gpa_str;
    int id, advisor_id;
    double gpa;

    // We could detect corrupted files with invalid data, but we already built some character
    // csv format - id,name,level,major,gpa,advisor_id
    getline(lineStream, id_str, ',');
    getline(lineStream, name, ',');
    getline(lineStream, level, ',');
    getline(lineStream, major, ',');
    getline(lineStream, gpa_str, ',');
    getline(lineStream, advisor_id_str, ',');

    gpa = stod(gpa_str);
    id = stoi(id_str);
    advisor_id = stoi(advisor_id_str);

    addStudent(id, name, level, major, gpa, advisor_id);
}

void Database::addFaculty(int id, string name, string level, string department) {
    Faculty* newFaculty = new Faculty(id, name, level, department);
    // If first faculty, update all student's ID's to this faculty? Dependent on custom iterator
    masterFaculty.insert(newFaculty);
}

void Database::promptAddFaculty() {
    string id_str, name, level, department;
    int id;
    bool success = false;
    while (!success) {
        try {
            success = true;
            cout << "Enter faculty ID: \n> ";
            getline(cin, id_str);
            id = stoi(id_str);

            cout << "Enter faculty name: \n> ";
            getline(cin, name);

            cout << "Enter faculty level: \n> ";
            getline(cin, level);

            cout << "Enter faculty department: \n> ";
            getline(cin, department);

            addFaculty(id, name, level, department);
        } catch (invalid_argument) {
            cout << "Invalid input! Try again." << endl << endl;
            success = false;
        }
    }
}

void Database::parseAddFaculty(string line) {

}
