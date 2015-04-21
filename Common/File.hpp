#pragma once

#include <cstdio>
#include <string>

#include "Uncopyable.hpp"

class File : private Uncopyable {
public:

    class Mode {
    public:
        enum Permission {
            Read = 0,
            Write,
            Append,
            ReadUpdate,
            WriteUpdate,
            AppendUpdate
        };

    private:
        static char const * const str[];

        friend class File; // for access to str[]
    };

    explicit File(std::string const &, Mode::Permission = Mode::Read);
    ~File();

    bool isOk() const { return !!pFile_ && !feof(pFile_) && !ferror(pFile_); }
    bool getChar(char * out) const;
    bool getSingleInt(int * out) const;

private:
    Mode::Permission mode_;
    FILE * pFile_;
    std::string fname_;
};