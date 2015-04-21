#pragma once

#include <cassert>
#include <limits>

#include "Memory.hpp"

namespace Common {

template<typename T, unsigned int sz>
class CircularBuffer {
    CircularBuffer(); // not defined
};

template<unsigned int sz>
class CircularBuffer<int, sz> {
public:
    typedef int const * CIter;

    CircularBuffer()
    : pos(0) {
        Memory::zeroRange(buffer, sizeof(int) * sz);
    }

    // Inserts a number into buffer, overwriting the oldest entry
    void insert(int num) {
        if(pos < sz) {
            buffer[pos++] = num;
        }
        if(pos == sz) {
            pos = 0;
        }
    }

    void reset() {
        Memory::zeroRange(buffer, sizeof(int) * sz);
        pos = 0;
    }

    CIter first() const {
        return buffer;
    }

    CIter end() const {
        return buffer + sz;
    }

private:
    int buffer[sz];
    unsigned int pos;
};

template<typename T>
long long multiplyElementsOf(T const & buffer) {
    long long product = 1;
    for(T::CIter it = buffer.first(); it != buffer.end(); ++it) {
        assert(product 
                 ? *it < (std::numeric_limits<long long>::max() / product)
                 : true);
        product *= *it;
    }
    return product;
}

}