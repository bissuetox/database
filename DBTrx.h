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
#endif