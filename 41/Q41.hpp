#ifndef PE41__INCLUDED
#define PE41__INCLUDED

class LimitedNum
{
public:
    LimitedNum( unsigned long long );
    bool const num( unsigned long long );
    unsigned const num() const { return _num; }
    
    static unsigned const MAX_;
private:
    unsigned _num;
};

struct Bit
{
    enum 
    {
        ONE   = 1,
        TWO   = 1 << 1,
        THREE = 1 << 2,
        FOUR  = 1 << 3,
        FIVE  = 1 << 4,
        SIX   = 1 << 5,
        SEVEN = 1 << 6,
        EIGHT = 1 << 7,
        NINE  = 1 << 8
    };
};

class PandigitalTracker
{
    static unsigned const FULL_PANDIGITAL;
    
public:
    explicit PandigitalTracker( LimitedNum n );
    bool const isPandigital() const;
    static unsigned const MAX_DIGITS;
    
private:
    void init();

    unsigned _num;
    unsigned flags;
};

unsigned const numDigits( unsigned long long );
bool isPrime(unsigned);

#endif // PE41__INCLUDED

