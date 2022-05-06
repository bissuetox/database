#include "Student.h"

// Default Constructor
Student::Student() {
    level = "";
    major = "";
    gpa = 0.0;
    advisor_id = 0;
}

// Overloaded Constructor
Student::Student(int new_id, string new_name, string new_level, string new_major, double new_gpa, int new_advisor_id) : Person(new_id, new_name) {
    level = new_level;
    major = new_major;
    gpa = new_gpa;
    advisor_id = new_advisor_id;
}

void Student::print() {
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Grade: " << level << endl;
    cout << "Major: " << major << endl;
    cout << "GPA: " << gpa << endl;

    // Advisor id is -1 if unset (only in chicken or egg situation)
    if (advisor_id == -1) {
        cout << "No advisor assigned!" << endl;
    } else {
        cout << "Advisor ID: " << advisor_id << endl;
    }

    cout << endl;
}