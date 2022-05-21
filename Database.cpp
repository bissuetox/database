#include "Database.h"
#include <exception>
#include <sstream>
#define STUDENT_PATH "./db/studentTable.csv"
#define FACULTY_PATH "./db/facultyTable.csv"

// Constructor
Database::Database() {

}

// Load database files if they exist
void Database::setup() {
    string read;

    // Import student data
    fp.openRead(STUDENT_PATH);
    // If file exists and is open, try to scan it in
    if (fp.isOpenRead()) {
        while(fp.getLine(read) && read != "") {
            // Ignore comments starting with '#'
            if (read.at(0) == '#') continue;
            else parseAddStudent(read);
        }
    }

    // Import faculty data
    fp.closeRead();
    fp.openRead(FACULTY_PATH);
    // If file exists and is open, try to scan it in
    if (fp.isOpenRead()) {
        while(fp.getLine(read) && read != "") {
            // Ignore comments with '#'
            if (read.at(0) == '#') continue;
            else {
                parseAddFaculty(read);
            }
        }
    }
    fp.closeRead(); 
}

// Save database files
void Database::save() {
    // Save Student DB
    fp.openWrite(STUDENT_PATH);
    traverseSaveStudent(masterStudent.getRoot());
    fp.closeWrite();
    cout << "Saved to " << STUDENT_PATH << endl;
    
    // Save Faculty DB
    fp.openWrite(FACULTY_PATH);
    traverseSaveFaculty(masterFaculty.getRoot());
    fp.closeWrite();
    cout << "Saved to " << FACULTY_PATH << endl;
}

// Recursive function to save faculty in masterFaculty
void Database::traverseSaveFaculty(TreeNode<Faculty>* node) {
    if (node == NULL) {
        return;
    }
    traverseSaveFaculty(node->left);
    string s = formatFaculty(&node->key);
    fp.write(s);
    fp.write("\n");
    traverseSaveFaculty(node->right);
}

// Recursive function to save students in masterStudent
void Database::traverseSaveStudent(TreeNode<Student>* node) {
    if (node == NULL) {
        return;
    }
    traverseSaveStudent(node->left);
    string s = formatStudent(&node->key);
    fp.write(s);
    fp.write("\n");
    traverseSaveStudent(node->right);
}

// Returns string of faculty formatted to file save format
string Database::formatFaculty(Faculty* f) {
    string str = "";
    str += to_string(f->id) + ",";
    str += f->name + ",";
    str += f->level + ",";
    str += f->department;

    // Only add comma if there are advisees
    if (f->advisee_ids.size() > 0) {
        str += ",";
    }

    for (int i = 0; i < f->advisee_ids.size(); ++i) {
        str += to_string(f->advisee_ids[i]);
        // Only add semicolon if not the last id
        if (i != f->advisee_ids.size() - 1) {
            str+= ";";
        }
    }
    return str;
}

// Returns string of student formatted to file save format
string Database::formatStudent(Student* f) {
    string str = to_string(f->id) + ",";
    str += f->name + ",";
    str += f->level + ",";
    str += f->major + ",";
    str += to_string(f->gpa) + ",";
    str += to_string(f->advisor_id);
    return str;
}

// Main Loop
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
            promptPrintStudent();
            break;
        case 4:
            promptPrintFaculty();
            break;
        case 5:
           promptPrintStudentAdvisor(); 
           break;
        case 6:
            promptPrintFacultysAdvisees();
            break;
        case 7:
            promptAddStudent(); // Add / remove
            break;
        case 8:
            promptDeleteStudent(); // remove / add
            break;
        case 9:
            promptAddFaculty(); // Add / remove
            break;
        case 10:
            promptDeleteFaculty(); // remove / add
            break;
        case 11:
            promptChangeStudentsAdvisor(); // mod / mod
            break;
        case 12:
            promptRemoveAdviseeFromFaculty(); // mod / mod
            break;
        case 13:
            rollback();
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
    string options = "";
    options += "\nEnter an option below:\n";
    options += "\t1. Print all students\n";
    options += "\t2. Print all faculty\n";
    options += "\t3. Find Student by ID\n";
    options += "\t4. Find Faculty by ID\n";
    options += "\t5. Print Student's Advisor\n";
    options += "\t6. Print Faculty's Advisee\n";
    options += "\t7. Add Student\n";
    options += "\t8. Delete Student\n";
    options += "\t9. Add Faculty Member\n";
    options += "\t10. Delete Faculty Member\n";
    options += "\t11. Change Student's Advisor\n";
    options += "\t12. Remove Faculty's Advisee\n";
    options += "\t13. Rollback last transaction\n";
    options += "\t14. Exit\n";
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

// Record a revertable transaction to the transaction history
void Database::studentTransaction(string action, Student s) {
    DBTrx trans(action, "student", s);
    trxHistory.push(trans);
}

// Record a revertable transaction to the transaction history
void Database::facultyTransaction(string action, Faculty f) {
    DBTrx trans(action, "faculty", f);
    trxHistory.push(trans);
}

// Roll's back last transaction
void Database::rollback() {
    if (trxHistory.size() <= 0) {
        cout << "No previous transactions!" << endl;
        return;
    }

    DBTrx trans = trxHistory.pop();
    if (trans.type == "student") {
        Student *s = &trans.studentCopy;

        // Remove added student
        if (trans.revertAction == "remove") {
            removeAdviseeFromFaculty(s->advisor_id, s->id);
            deleteStudent(s->id);
            cout << "Rolled back addition of student " << s->id << " - " << s->name << endl;
        }
        // Re-adding removed student
        else if (trans.revertAction == "add") {
            addStudent(s->id, s->name, s->level, s->major, s->gpa, s->advisor_id);
            Faculty* foundFaculty = findFaculty(s->advisor_id);
            foundFaculty->addAdviseeId(s->id);
            cout << "Rolled back removal of student " << s->id << " - " << s->name << endl;
        }
        // Revert mod to student's advisor
        else if (trans.revertAction == "mod") {
            Student* currStudent = findStudent(s->id);
            Faculty* currAdvisor = findFaculty(currStudent->advisor_id);
            Faculty* origAdvisor = findFaculty(s->advisor_id);
            currAdvisor->removeAdviseeId(s->id);
            origAdvisor->addAdviseeId(s->id);
            currStudent->advisor_id = s->advisor_id;
            cout << "Rolled back advisor change for student " << s->id << " - " << s->name << endl;
        }
    } else if (trans.type == "faculty") {
        Faculty *f = &trans.facultyCopy;
        if (trans.revertAction == "remove") {
            deleteFaculty(f->id);
        }
        // Re-adding removed faculty
        else if (trans.revertAction == "add") {
            addFaculty(f->id, f->name, f->level, f->department);
            Faculty* restoredFaculty = findFaculty(f->id);
            vector<int>* old_ids = &f->advisee_ids;
            if (old_ids->size() > 0) {
                // Get sample student to fetch current Advisor
                Student* sampleStudent = findStudent(old_ids->at(0)); 
                Faculty* currFaculty = findFaculty(sampleStudent->advisor_id);

                // Migrate advisees
                int thisId;
                Student* thisStudent = NULL;
                for (int i=0; i < old_ids->size(); ++i) {
                    thisId = old_ids->at(i);
                    thisStudent = findStudent(thisId);

                    currFaculty->removeAdviseeId(thisId);
                    thisStudent->advisor_id = restoredFaculty->id;  // Change student's advisor_id
                    restoredFaculty->addAdviseeId(thisId);      // Add student to advisee list
                }
            }

        }
        // Revert mod to student's advisor
        else if (trans.revertAction == "mod") {

        }
    } else {
        cout << "Bad Transaction type!" << endl;
    }
}

// Adds a student to masterStudent
Student* Database::addStudent(int id, string name, string level, string major, double gpa, int advisor_id) {
    Student* newStudent = new Student(id, name, level, major, gpa, advisor_id);
    masterStudent.insert(*newStudent);
    return newStudent;
}

// Prompts user for student data then adds it to masterStudent
void Database::promptAddStudent() {
    string name, level, major, id_str, advisor_id_str, gpa_str;
    int id, advisor_id;
    double gpa;
    try {
        cout << "Enter student ID: \n> ";
        getline(cin, id_str);
        id = stoi(id_str);

        if (findStudent(id)) {
            throw invalid_argument("Student with that ID already exists!");
        }

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
            cout << "No faculty available, add one first!" << endl;
            return;
            // advisor_id = -1;
        } else {
            Faculty* foundFaculty = promptFindFaculty("Enter student's advisor ID: \n> ");
            if (!foundFaculty) return;
            advisor_id = foundFaculty->id;
        }

        addStudent(id, name, level, major, gpa, advisor_id);
        Student* newStudent = findStudent(id);
        Faculty* newAdvisor = findFaculty(advisor_id);
        newAdvisor->addAdviseeId(id);
        
        studentTransaction("add", *newStudent);
    } catch (invalid_argument e) {
        handleException(e);
    }
}

// Parses student data from a file line
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

// Adds a faculty to masterFaculty
Faculty* Database::addFaculty(int id, string name, string level, string department) {
    Faculty* newFaculty = new Faculty(id, name, level, department);
    // If first faculty, update all student's ID's to this faculty? Dependent on custom iterator
    masterFaculty.insert(*newFaculty);
    return newFaculty;
}

// Prompts user for faculty data then adds it to masterFaculty
void Database::promptAddFaculty() {
    string id_str, name, level, department;
    int id;
    try {
        cout << "Enter faculty ID: \n> ";
        getline(cin, id_str);
        id = stoi(id_str);

        if (findFaculty(id)) {
            throw invalid_argument("Faculty with that ID already exists!");
        }

        cout << "Enter faculty name: \n> ";
        getline(cin, name);

        cout << "Enter faculty level: \n> ";
        getline(cin, level);

        cout << "Enter faculty department: \n> ";
        getline(cin, department);

        addFaculty(id, name, level, department);
        Faculty* newFaculty = findFaculty(id);
        facultyTransaction("add", *newFaculty);
    } catch (invalid_argument e) {
        handleException(e);
    }
}

// Parses faculty data from a file line
void Database::parseAddFaculty(string line) {
    stringstream lineStream(line);
    string id_str, name, level, department, advisee_ids;
    int id;

    // id,name,level,department,a_id1;a_id1;a_id1;a_id1;

    getline(lineStream, id_str, ',');
    getline(lineStream, name, ',');
    getline(lineStream, level, ',');
    getline(lineStream, department, ',');
    getline(lineStream, advisee_ids, ',');

    id = stoi(id_str);
    addFaculty(id, name, level, department);
    Faculty* newFaculty = findFaculty(id);

    // Iterate through advisee_ids (variable amt)
    if (!(advisee_ids == "")) {
        stringstream idStream(advisee_ids);
        string read;
        while (getline(idStream, read, ';')) {
            newFaculty->advisee_ids.push_back(stoi(read));
        }
    }
}

// Prompts user for a Student ID and returns it if found, otherwise NULL
Student* Database::promptFindStudent(string prompt) {
    Student* foundStudent = NULL;
    try {
        string read;
        int id;
        cout << "Enter Student ID\n> ";
        getline(cin, read);
        id = stoi(read);
        foundStudent = findStudent(id);
        if (foundStudent == NULL) throw invalid_argument("Student ID doesn't exist.");
    } catch (invalid_argument e) {
        handleException(e);
    }
    return foundStudent;
}

// Prompts user for a Faculty ID and returns it if found, otherwise NULL
Faculty* Database::promptFindFaculty(string prompt) {
    Faculty* foundFaculty = NULL;
    try {
        string read;
        int id;
        cout << prompt;
        getline(cin, read);
        id = stoi(read);
        foundFaculty = findFaculty(id);
        if (foundFaculty == NULL) throw invalid_argument("Faculty ID doesn't exist.");
    } catch (invalid_argument e) {
        string what = e.what();
        if (what == "stoi") {
            cout << "Invalid Input!" << endl;
        } else {
            cout << e.what() << endl;
        }
    }
    return foundFaculty;
}

// Searches and returns Faculty by ID, NULL if not found
Faculty* Database::findFaculty(int id) {
    Faculty dummyFaculty(id, "", "", ""); // Dummy Faculty object for searching
    return masterFaculty.search(dummyFaculty);
} 

// Searches and returns Student by ID, NULL if not found
Student* Database::findStudent(int id) {
    Student dummyStudent(id, "", "", "", 0, 0); // Dummy Student object for searching
    return masterStudent.search(dummyStudent);
} 

// Prompts for Faculty ID and prints its advisees
void Database::promptPrintFacultysAdvisees() {
    Faculty* foundFaculty = promptFindFaculty();
    if (foundFaculty)
        foundFaculty->printAdvisees(masterStudent);
}

// Prompts user for student ID and prints the info if found
void Database::promptPrintStudent() {
    Student* foundStudent = promptFindStudent();
    if (foundStudent)
        cout << *foundStudent;
}

// Prompts user for faculty ID and prints the info if found
void Database::promptPrintFaculty() {
    Faculty* foundFaculty = promptFindFaculty();
    if (foundFaculty)
        cout << *foundFaculty;
}

// Prompts for Student ID and prints its advisees
void Database::promptPrintStudentAdvisor() {
    Student* foundStudent = promptFindStudent();
    if (foundStudent) {
        // TODO - remove this functionality? no more -1 chicken/egg
        if (foundStudent->advisor_id == -1) {
            cout << "Advisor ID not assigned to " << foundStudent->name << "!" << endl;
        } else {
            // Faculty dummyFaculty(foundStudent->advisor_id, "", "", ""); // Dummy Faculty object for searching
            // Faculty sFac = *masterFaculty.search(dummyFaculty);
            Faculty *foundFaculty = findFaculty(foundStudent->advisor_id);
            cout << foundStudent->name << "'s advisor: " << endl;
            cout << *foundFaculty; // TODO - only print name and ID?
        }
    }
}

// Prompt for Student ID and delets the student if found - TODO migrate / ref int.
void Database::promptDeleteStudent() {
    Student* foundStudent = promptFindStudent();
    if (foundStudent) {
        studentTransaction("remove", *foundStudent);
        Faculty* foundFaculty = findFaculty(foundStudent->advisor_id);
        foundFaculty->removeAdviseeId(foundStudent->id);
        masterStudent.deleteNode(*foundStudent);
        cout << foundStudent->name << " (" << foundStudent->id << ") removed!" << endl;
    }
}

// Prompt for Faculty ID and delets the student if found - TODO migrate / ref int.
void Database::promptDeleteFaculty() {
    Faculty* foundFaculty = promptFindFaculty();
    if (foundFaculty) {
        // If students exist and no other advisors available, reject
        if (masterFaculty.getNumNodes() == 1 && masterStudent.getNumNodes() > 0) {
            cout << "There are no other advisors available to migrate advisee(s) to." << endl;
            return;
        }

        facultyTransaction("remove", *foundFaculty);

        // Prompt for replace advisor if advisees exist
        if (foundFaculty->advisee_ids.size() > 0) {
            try {
                string read;
                int id;
                cout << "Warning: Faculty has advisee's linked!" << endl;
                cout << "Enter replacement advisor ID\n> ";
                getline(cin, read);
                id = stoi(read);
                Faculty* newAdvisor = findFaculty(id);
                if (!newAdvisor) throw invalid_argument("Faculty ID doesn't exist.");

                // Scrub through advisee's and migrate them
                vector<int>* ids = &foundFaculty->advisee_ids;
                int thisId;
                Student* thisStudent = NULL;
                for (int i=0; i < ids->size(); ++i) {
                    thisId = ids->at(i);
                    thisStudent = findStudent(thisId);
                    thisStudent->advisor_id = newAdvisor->id;
                    newAdvisor->addAdviseeId(thisId);
                }
            } catch (invalid_argument e) {
                handleException(e);
            }
        }

        // Delete from faculty table
        masterFaculty.deleteNode(*foundFaculty);
        cout << foundFaculty->name << " (" << foundFaculty->id << ") removed!" << endl;
    }
}

// INTERNAL USE - Deletes a faculty by ID
void Database::deleteFaculty(int id) {
    Faculty* foundFaculty = findFaculty(id);
    if (foundFaculty) {
        masterFaculty.deleteNode(*foundFaculty);
    }
}

// INTERNAL USE - Deletes a Student by ID
void Database::deleteStudent(int id) {
    Student* foundStudent = findStudent(id);
    if (foundStudent) {
        masterStudent.deleteNode(*foundStudent);
    }
}

// Change a student's advisor ID
void Database::promptChangeStudentsAdvisor() {
    Student* foundStudent = promptFindStudent();
    if (foundStudent) {
        Faculty* newAdvisor = promptFindFaculty("Enter new Faculty ID\n> ");
        if (newAdvisor) {
            studentTransaction("mod", *foundStudent);
            removeAdviseeFromFaculty(foundStudent->advisor_id, foundStudent->id);
            foundStudent->advisor_id = newAdvisor->id;
            newAdvisor->addAdviseeId(foundStudent->id);
            cout << "Changed advisor to " << newAdvisor->name << " (" << newAdvisor->id << ")" << endl;
        }
    }
}

// Remove an Advisee from Faculty - TODO migrate student's new advisor ID
void Database::promptRemoveAdviseeFromFaculty() {
    Faculty* foundFaculty = promptFindFaculty();
    if (foundFaculty) {
        // If have no advisee's, can't remove one!
        if (foundFaculty->advisee_ids.size() == 0) {
            cout << "Advisor has no advisees!" << endl;
            return;
        }

        // If no other advisors available, reject
        if (masterFaculty.getNumNodes() == 1) {
            cout << "There are no other advisors available to migrate advisee to." << endl;
            return;
        }

        // Display advisees
        foundFaculty->printAdvisees(masterStudent);
        try {
            // Fetch ID
            cout << "Enter advisee ID to remove:\n> ";
            string read;
            getline(cin, read);
            int studentId = stoi(read);
            // If ID doesn't belong to Faculty, exit
            if (!foundFaculty->hasAdviseeId(studentId)) {
                throw invalid_argument("Faculty does not have that advisee ID!");
            }
            // Migrate student's advisor
            Faculty* newAdvisor = promptFindFaculty("Select new Advisor ID:\n> ");
            if (!newAdvisor) return;
            Student* foundStudent = findStudent(studentId);

            studentTransaction("mod", *foundStudent);
            changeStudentsAdvisor(studentId, newAdvisor->id);
            removeAdviseeFromFaculty(foundFaculty->id, studentId);
            cout << "Removed advisee " << studentId << endl;

        } catch (invalid_argument e) {
            handleException(e);
        }
    }
}

// INTERNAL USE - Remove advisee from Faculty's advisee list
void Database::removeAdviseeFromFaculty(int id, int advisee_id) {
    Faculty* foundFaculty = findFaculty(id);
    if (foundFaculty) {
        foundFaculty->removeAdviseeId(advisee_id);
    }
    // Otherwise do nothing
}

// INTERNAL USE - Change a student's advisor ID
void Database::changeStudentsAdvisor(int id, int advisor_id) {
    Student* foundStudent = findStudent(id);
    if (foundStudent) {
        Faculty* newAdvisor = findFaculty(advisor_id);
        if (newAdvisor) {
            foundStudent->advisor_id = newAdvisor->id;
            newAdvisor->addAdviseeId(foundStudent->id);
        }
    }
}

// Handles printing of exception messages
void Database::handleException(invalid_argument e) {
    string what = e.what();
    if (what == "stoi") {
        cout << "Invalid Input!" << endl;
    } else {
        cout << e.what() << endl;
    }
}
