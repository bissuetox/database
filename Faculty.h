#ifndef FACULTY_H
    #define FACULTY_H
    #include <iostream>
    #include <vector>
    #include "Person.h"
    #include "Student.h"
    #include "BST.h"
    using namespace std;
    
    // Faculty class - inherits Person
    class Faculty : public Person {
        public:
            string level;
            string department;
            vector<int> advisee_ids;
            Faculty();
            Faculty(int new_id, string new_name, string new_level, string new_department);
            void print(ostream& os) const;
            void printAdvisees(BST<Student*>& masterStudent);
            void addAdviseeId(int id);

    };

#endif