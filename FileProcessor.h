#ifndef FILEPROCESSOR_H
    #define FILEPROCESSOR_H
    #include <iostream>
    #include <fstream>
    using namespace std;

// FileProcessor Class definition
class FileProcessor {
    // Public members
    public:
        FileProcessor();
        FileProcessor(string inPath, string outPath);
        ~FileProcessor();
        // virtual void processFile();
        string promptFilepath(string type);

        bool openRead(string inputPath);
        bool openWrite(string outputPath);
        void closeRead();
        void closeWrite();
        bool isOpenRead();
        bool isOpenWrite();
        istream& getLine(string& line);
        ostream& write(string line);

    private:
        ifstream* inStream;
        ofstream* outStream;
};


#endif