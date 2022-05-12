#ifndef DATABASE_H
    #define DATABASE_H
    #define STUDENT_PATH "./db/studentTable.csv"
    #define FACULTY_PATH "./db/facultyTable.csv"
    #include "Faculty.h"
    #include "Student.h"
    #include "BST.h"
    #include "GenStack.h"
    #include "DBTrx.h"
    using namespace std;

    class Database {
        private:
            BST<Faculty*> masterFaculty;
            BST<Student*> masterStudent;
            GenStack<DBTrx*> trxHistory;
        public:
            Database();
            void setup();
            void parseTable(string path);
            void interfaceLoop();
            void printOptions();
            void ingestChoice(int choiceInt);
    };

#endif