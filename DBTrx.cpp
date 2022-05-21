#include "DBTrx.h"

DBTrx::DBTrx() {

}

DBTrx::DBTrx(string thatAction, string thatType, Student p) {
    type = thatType;
    studentCopy = p;
    if (thatAction == "add") {
        // To revert, remove added entry
        action = "add";
        revertAction = "remove";
    } else if (thatAction == "remove") {
        // To revert, add removed entry
        action = "remove";
        revertAction = "add";
    } else if (thatAction == "mod") {
        // To revert set entry to old values
        action = "mod";
        revertAction = "mod";
    }
}

DBTrx::DBTrx(string thatAction, string thatType, Faculty p) {
    type = thatType;
    facultyCopy = p;
    if (thatAction == "add") {
        // To revert, remove added entry
        action = "add";
        revertAction = "remove";
    } else if (thatAction == "remove") {
        // To revert, add removed entry
        action = "remove";
        revertAction = "add";
    } else if (thatAction == "mod") {
        // To revert set entry to old values
        action = "mod";
        revertAction = "mod";
    }
}