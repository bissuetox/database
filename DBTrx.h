#ifndef DBTRX_H
    #define DBTRX_H
    #include "Student.h"
    #include "Faculty.h"
    using namespace std;
    
    class DBTrx {
        public:
            string action;          // add, remove, mod
            string type;            // Student / Faculty
            string revertAction;    // add, remove, mod
            Student studentCopy;      // copy of student object for reference
            Faculty facultyCopy;      // copy of faculty object for reference
            // vector<DBTrx> dependencies;
            // Student -> Person
            // Person -> Student
            DBTrx(string thatAction, string thatType, Student p);
            DBTrx(string thatAction, string thatType, Faculty p);
            DBTrx();
    };
#endif