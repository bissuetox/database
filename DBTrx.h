#ifndef DBTRX_H
    #define DBTRX_H
    #include "Person.h"
    #include "Database.h"
    using namespace std;
    
    class DBTrx {
        public:
            string action;
            string type;
            string revertAction;
            Person personCopy;
            // Student -> Person
            // Person -> Student
            DBTrx(string thatAction, string thatType, Person p);
    };
#endif