#ifndef PERSON_H
    #define PERSON_H
    #include <iostream>
    using namespace std;
    
    // Faculty class - inherits Person
    class Person {
        public:
            int id;
            string name;
            Person();
            Person(int new_id, string new_name);
            void print();
            friend bool operator== (const Person& argPerson, const Person& thisPerson);
            friend bool operator< (const Person& argPerson, const Person& thisPerson);
            friend bool operator> (const Person& argPerson, const Person& thisPerson);
    };

#endif