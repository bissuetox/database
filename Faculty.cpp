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
        os << "Student IDs:" << endl;
        for (auto i = advisee_ids.begin(); i != advisee_ids.end(); ++i) {
            os << "ID: " << advisee_ids.at(*i) << endl;
        }
    }

    os << endl;
}