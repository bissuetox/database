#ifndef SIMULATION_H
    #define SIMULATION_H
    #define STUDENT_PATH "./db/student.csv"
    #define FACULTY_PATH "./db/faculty.csv"
    #include "Faculty.h"
    #include "Student.h"
    #include "Person.h"
    #include "BST.h"
    #include "GenStack.h"
    using namespace std;

    class Simulation {
        private:
            BST<Faculty*> masterFaculty;
            BST<Student*> masterStudent;
        public:
            Simulation();
            void run();
    };

#endif