#pragma once

class Uncopyable {
public:
    Uncopyable() {}
    ~Uncopyable() {}
private:
    Uncopyable(Uncopyable const & other); // not defined
    Uncopyable & operator=(Uncopyable const & other); // not defined
};