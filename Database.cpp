#include "Database.h"
#include <exception>
#define STUDENT_PATH "./db/studentTable.csv"
#define FACULTY_PATH "./db/facultyTable.csv"

Database::Database() {

}

void Database::setup() {
    string read;
    fp.openRead(STUDENT_PATH);
    // If file exists and is open, try to scan it in
    if (fp.isOpenRead()) {
        cout << "Is open!" << endl;
        while(fp.getLine(read)) {
            cout << read << endl;
        }
    } else {
        cout << "Not open" << endl;
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
            // printAllStudents();
            masterStudent.printNodes();
            break;
        case 2:
            // printAllFaculty();
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
            // addStudent();
            break;
        case 8:
            // deleteStudentById();
            break;
        case 9:
            // addFaculty();
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