#ifndef STUDENT_H
    #define STUDENT_H
    #include <iostream>
    #include "Person.h"
    using namespace std;
    
    class Student : public Person {
        public:
            string level;
            string major;
            double gpa;
            int advisor_id;
            Student();
            Student(string new_level, string new_major, double new_gpa, int new_advisor_id);
    };

#endif