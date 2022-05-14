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

            void printAllStudents();
            void printAllFaculty();
            void addStudent(int id, string name, string level, string major, double gpa, int advisor_id);
            void promptAddStudent();
            void parseAddStudent(string line);

            void addFaculty(int id, string name, string level, string department);
            void promptAddFaculty();
            void parseAddFaculty(string line);
    };

#endif