#ifndef PERSON_H
    #define PERSON_H
    #include <iostream>
    using namespace std;
    
    class Person {
        public:
            int id;
            string name;
            Person();
            Person(int new_id, string new_name);
            void print();
    };

#endif