#include "Student.h"

Student::Student() {
    level = "";
    major = "";
    gpa = 0.0;
    advisor_id = 0;
}


Student::Student(string new_level, string new_major, double new_gpa, int new_advisor_id) {
    level = new_level;
    major = new_major;
    gpa = new_gpa;
    advisor_id = new_advisor_id;
}