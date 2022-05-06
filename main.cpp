#include "Faculty.h"
#include "Student.h"

int main(int argc, char **argv) {
	Faculty f(1, "bob", "professor", "CS");
    f.print();

    Student s(1, "jimmy", "freshman", "CS", 4.0, 1);
    s.print();

}