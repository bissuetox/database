#ifndef DBTRX_H
    #define DBTRX_H
    #include "Person.h"
    using namespace std;
    
    class DBTrx {
        public:
            string action;          // add, remove, mod
            string type;            // Student / Faculty
            string revertAction;    // add, remove, mod
            Person personCopy;      // copy of person object for reference
            // vector<DBTrx> dependencies;
            // Student -> Person
            // Person -> Student
            DBTrx(string thatAction, string thatType, Person p);
            DBTrx();
    };
#endif