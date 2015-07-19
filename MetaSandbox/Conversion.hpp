#ifndef META_CONVERSION_HPP
#define META_CONVERSION_HPP

/*
 * Checks whether type T can be converted to type U
 */
template< typename T, typename U >
class Conversion {
    typedef char Small;
    class Big { Small s[2]; };
    static T makeT(); // not defined
    static Small test(U); // not defined (T is convertible to U)
    static Big test(...); // not defined (T is not convertible to U)
public:
    enum { exists = sizeof(test(makeT())) == sizeof(Small) ? true : false };
    enum { exists2way = exists && Conversion< U, T >::exists };
    enum { sameType = false };
};

template< typename T > class Conversion< T, T > {
public:
    enum { exists = true, exists2way = true, sameType = true };
};

/*
 * Boolean which says whether U inherits from T
 */
#define SUPERSUBCLASS(T, U) \
    (  Conversion< const U *, const T * >::exists \
    && !Conversion< const T *, const void * >::sameType )

#endif // META_CONVERSION_HPP