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

void Person::print(ostream& os) const {
    os << "ID: " << id << " | Name: " << name << endl;
}

// Equality Operator Overload
bool operator== (const Person& argPerson, const Person& thisPerson) {
    return argPerson.id == thisPerson.id;
}

// Inequality Operator Overload
bool operator!= (const Person& argPerson, const Person& thisPerson) {
    return argPerson.id != thisPerson.id;
}

// Less than Operator Overload
bool operator< (const Person& argPerson, const Person& thisPerson) {
    return argPerson.id < thisPerson.id;
}

// Greater than Operator Overload
bool operator> (const Person& argPerson, const Person& thisPerson) {
    return argPerson.id > thisPerson.id;
}

ostream& operator<<(ostream& os, const Person& thisPerson) {
    thisPerson.print(os);
    return os;
}