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
            Student* promptFindStudent(string prompt="Enter Student ID\n> ");
            void printAllStudents(); 
            void promptAddStudent();
            void parseAddStudent(string line);
            void promptPrintStudent();
            void promptPrintStudentAdvisor();
            void promptDeleteStudent();
            void changeStudentsAdvisor();

            // Faculty methods
            Faculty* addFaculty(int id, string name, string level, string department);
            Faculty* promptFindFaculty(string prompt="Enter Faculty ID\n> ");
            void printAllFaculty();
            void promptAddFaculty();
            void parseAddFaculty(string line);
            void promptPrintFacultysAdvisees();
            void promptPrintFaculty();
            void promptDeleteFaculty();
            void promptRemoveAdviseeFromFaculty();
            void promptChangeStudentsAdvisor();

            // Internal Use Methods
            Student* findStudent(int id);
            Faculty* findFaculty(int id);
            void deleteStudent(int id);
            void deleteFaculty(int id);
            void removeAdviseeFromFaculty(int id, int advisee_id);
            void changeStudentsAdvisor(int id, int advisor_id);
    };

#endif