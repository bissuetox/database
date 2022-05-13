#include "FileProcessor.h"
#include <fstream>
using namespace std;

// Constructor
FileProcessor::FileProcessor() {
    // Open null streams - can be opened with openRead or openWrite
    inStream = new ifstream(NULL);
    outStream = new ofstream(NULL);
}

FileProcessor::FileProcessor(string inPath="", string outPath="") {
    // Open null streams - can be opened with openRead or openWrite later on
    inStream = new ifstream(inPath);
    outStream = new ofstream(outPath);
}

// Destructor
FileProcessor::~FileProcessor() {
    if(inStream->is_open()) {
        inStream->close();
    }
    if (outStream->is_open()) {
        outStream->close();
    }

    delete inStream;
    delete outStream;
}

// Open file for reading - return true if successful
bool FileProcessor::openRead(string inputPath) {
    inStream->open(inputPath, ios::in);
    return inStream->fail() ? false : true;
}

// Open file for writing - return true if successful
bool FileProcessor::openWrite(string outputPath) {
    outStream->open(outputPath, ios::out);
    return inStream->fail() ? false : true;
}

// Close inStream if its open (for reopening)
void FileProcessor::closeRead() {
    if(inStream->is_open()) {
        inStream->close();
    }
}

// Close inStream if its open (for reopening)
void FileProcessor::closeWrite() {
    if(outStream->is_open()) {
        outStream->close();
    }
}

// Returns bool if inStream is open
bool FileProcessor::isOpenRead() {
    return inStream->is_open() ? true : false;
}

// Returns bool if outStream is open
bool FileProcessor::isOpenWrite() {
    return outStream->is_open() ? true : false;
}

// Calls getline from inStream and sets the line reference variable
istream& FileProcessor::getLine(string& line) {
    return std::getline(*inStream, line);
}
// Prompts for filepath and returns it. "input" or "output" type changes prompt message
string FileProcessor::promptFilepath(string type) {
    string path = "";
    if (type == "input") {
        cout << "Enter input filepath: ";
    } else if (type == "output") {
        cout << "Enter output filepath: ";
    }
    cin.ignore(); // Ignore any newlines if there are any
    getline(cin, path);
    return path;
}