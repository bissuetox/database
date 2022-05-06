#include "Person.h"

// Default Constructor
Person::Person() {
    id = -1;
    name = "";   
}

// Overloaded Constructor
Person::Person(int new_id, string new_name) {
    id = new_id;
    name = new_name;
}

void Person::print() {
    cout << "ID: " << id << " | Name: " << name << endl;
}

// Equality Operator Overload
bool operator== (const Person& argPerson, const Person& thisPerson) {
    return argPerson.id == thisPerson.id;
}

// Less than Operator Overload
bool operator< (const Person& argPerson, const Person& thisPerson) {
    return argPerson.id < thisPerson.id;
}

// Greater than Operator Overload
bool operator> (const Person& argPerson, const Person& thisPerson) {
    return argPerson.id > thisPerson.id;
}
