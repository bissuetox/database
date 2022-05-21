#include "DBTrx.h"

DBTrx::DBTrx() {

}

DBTrx::DBTrx(string thatAction, string thatType, Person p) {
    personCopy = p;
    type = thatType;
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