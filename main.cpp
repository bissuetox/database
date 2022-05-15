#include "Database.h"

int main(int argc, char **argv) {
    Database db;
    db.setup();
    db.interfaceLoop();
    db.save();
}