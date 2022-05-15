#include "DBTrx.h"

DBTrx::DBTrx(string thatAction, string thatType, Person p) {
    personCopy = p;
    type = thatType;
    if (thatAction == "insert") {
        // To revert, remove inserted entry
        action = "insert";
        revertAction = "remove";
    } else if (thatAction == "remove") {
        // To revert, insert removed entry
        action = "remove";
        revertAction = "insert";
    } else if (thatAction == "mod") {
        // To revert set entry to old values
        action = "mod";
        revertAction = "mod";
    }
}

// void DBTrx::revert(Database &db) {
//     if (type == "student") {
//         if (revertAction == "remove") {
            
//         }
//     } else if (type == "faculty") {

//     } else {
//         cout << "Bad Transaction type!" << endl;
//     }
// }
