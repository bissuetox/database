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
            BST<Faculty> masterFaculty;
            BST<Student> masterStudent;
            GenStack<DBTrx> trxHistory;
            FileProcessor fp;
        public:
            Database();
            void setup();
            void parseTable(string path);
            void interfaceLoop();
            void printOptions();
            void ingestChoice(int choiceInt);

            void save();
            void traverseSaveStudent(TreeNode<Student>* const node);
            void traverseSaveFaculty(TreeNode<Faculty>* const node);
            string formatStudent(Student* s);
            string formatFaculty(Faculty *f);

            void transaction(string action, string type, Person p);
            void rollback();

            // Student methods
            Student* addStudent(int id, string name, string level, string major, double gpa, int advisor_id);
            Student* findStudent(int id);
            Student* promptFindStudent(string prompt="Enter Student ID\n> ");
            void printAllStudents(); 
            void promptAddStudent();
            void parseAddStudent(string line);
            void promptPrintStudent();
            void promptPrintStudentAdvisor();
            void promptDeleteStudent();
            void changeStudentsAdvisor();
            void deleteStudent(int id);

            // Faculty methods
            Faculty* addFaculty(int id, string name, string level, string department);
            Faculty* findFaculty(int id);
            Faculty* promptFindFaculty(string prompt="Enter Faculty ID\n> ");
            void printAllFaculty();
            void promptAddFaculty();
            void parseAddFaculty(string line);
            void promptPrintFacultysAdvisees();
            void promptPrintFaculty();
            void promptDeleteFaculty();
            void removeAdviseeFromFaculty();
            void deleteFaculty(int id);
    };

#endif