#ifndef FACULTY_H
    #define FACULTY_H
    #include <iostream>
    #include <vector>
    #include "Person.h"
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
    };

#endif