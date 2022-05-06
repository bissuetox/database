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

void Faculty::print() {
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Role: " << level << endl;
    cout << "Department: " << department << endl;

    if (advisee_ids.size() == 0) {
        cout << "No Student Advisees!" << endl;
    } else {
        cout << "Student IDs:" << endl;
        for (auto i = advisee_ids.begin(); i != advisee_ids.end(); ++i) {
            cout << "ID: " << advisee_ids.at(*i) << endl;
        }
    }

    cout << endl;
}