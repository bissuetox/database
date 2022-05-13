#ifndef DATABASE_H
    #define DATABASE_H
    #include "Faculty.h"
    #include "Student.h"
    #include "BST.h"
    #include "GenStack.h"
    #include "DBTrx.h"
    #include "FileProcessor.h"
    using namespace std;

    class Database {
        private:
            BST<Faculty*> masterFaculty;
            BST<Student*> masterStudent;
            GenStack<DBTrx*> trxHistory;
            FileProcessor fp;
        public:
            Database();
            void setup();
            void parseTable(string path);
            void interfaceLoop();
            void printOptions();
            void ingestChoice(int choiceInt);
    };

#endif