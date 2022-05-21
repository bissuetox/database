#include "Faculty.h"

// Default Constructor
Faculty::Faculty() : Person() {
    level = "";
    department = "";
    // foo = 5;
}

// Overloaded Constructor
Faculty::Faculty(int new_id, string new_name, string new_level, string new_department) : Person(new_id, new_name) {
    level = new_level;
    department = new_department;
    // Leave advisee_ids empty
}

void Faculty::print(ostream& os) const {
    os << "ID: " << id << endl;
    os << "Name: " << name << endl;
    os << "Role: " << level << endl;
    os << "Department: " << department << endl;

    if (advisee_ids.size() == 0) {
        os << "No Student Advisees!" << endl;
    } else {
        cout << "Student IDs:" << endl;
        for (auto i = advisee_ids.begin(); i != advisee_ids.end(); ++i) {
            cout << *i << endl;
        }
    }
}

void Faculty::addAdviseeId(int id) {
    advisee_ids.push_back(id);
}

void Faculty::printAdvisees(BST<Student>& masterStudent) {
    int thisId;
    Student *thisStudent;
    if (advisee_ids.size() == 0) {
        cout << "Faculty has no advisees!" << endl;
        return;
    }

    for (int i=0; i < advisee_ids.size(); ++i) {
        thisId = advisee_ids[i];
        Student dummyStudent(thisId, "", "", "", 0, 0); // Dummy student with id to search
        thisStudent = masterStudent.search(dummyStudent);
        cout << thisStudent->id << " - " << thisStudent->name << endl;
    }
}

bool Faculty::hasAdviseeId(int id) {
    bool valid = false;
    for (int i = 0; i < advisee_ids.size(); ++i) {
        if (advisee_ids.at(i) == id)
            valid = true;
    }
    return valid;
}

// Removes id value from advisee id vector
void Faculty::removeAdviseeId(int advisee_id) {
    if (!hasAdviseeId(advisee_id)) {
        cout << "ERROR: Does not contain advisee ID" << endl;
        return;
    }
    advisee_ids.erase(std::remove(advisee_ids.begin(), advisee_ids.end(), advisee_id), advisee_ids.end());
}