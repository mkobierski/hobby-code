#include "File.hpp"

#include <cctype>
#include <cstdio>
#include <string>

char const * const File::Mode::str[] = {
    "r",
    "w",
    "a",
    "r+",
    "w+",
    "a+"
};

File::File(std::string const & fname, File::Mode::Permission mode) 
: mode_(Mode::Read) {
    pFile_ = fopen(fname.c_str(), Mode::str[mode]);
    if(pFile_ != 0) {
        fname_ = fname;
        mode_ = mode;
    }
}

File::~File() {
    if(pFile_) {
        fclose(pFile_);
    }
}

bool File::getChar(char * out) const {
    if(!isOk()) {
        return false;
    }
    int c = fgetc(pFile_);
    if(c == EOF) {
        return false;
    }
    *out = static_cast<char>(c);
    return true;
}

bool File::getSingleInt(int * out) const {
    if(!isOk()) {
        return false;
    }
    int c = fgetc(pFile_);
    if(!isdigit(c)) {
        return false;
    }
    *out = c - '0';
    return true;
}