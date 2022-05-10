#ifndef DBTRX_H
    #define DBTRX_H
    #include "Person.h"
    using namespace std;
    
    class DBTrx {
        private:
            string action;
            string revertAction;
            Person *personPtr;
        public:
            // DBTrx();
            DBTrx(Person* p, string action);
    };

    DBTrx::DBTrx(Person* p, string thatAction) {
        personPtr = p;
        if (thatAction == "insert") {
            // To revert, remove inserted entry
            action = "insert";
            revertAction = "remove";
        } else if (thatAction == "remove") {
            // To revert, insert removed entry
            action = "remove";
            revertAction = "insert";
        } else if (thatAction == "mod") {
            // To revert set entry to old values
            action = "mod";
            revertAction = "mod";
        }
    }