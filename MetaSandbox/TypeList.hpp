#ifndef META_TYPELIST_HPP
#define META_TYPELIST_HPP

#include "Conversion.hpp"
#include "NullEmpty.hpp"
#include "Select.hpp"

/*
 * Basic TypeList type.  T must be an atomic type, U must be either a 
 * TypeList or NullType (marks end of the list).
 */
template< typename T, typename U >
struct TypeList {
    typedef T Head;
    typedef U Tail;
};

/*
 * Returns the number of items in TList
 */
template< typename TList > struct Length;
template<> struct Length<NullType> { enum { value = 0 }; };
template< typename Atomic, typename U> struct Length< TypeList< Atomic, U > > {
    enum { value = 1 + Length< U >::value };
};

/*
 * Returns the type found at index i.  TypeLists indices begin at 0.
 */
template< typename TList, unsigned int i > struct TypeAt;
template< typename Head, typename Tail > 
struct TypeAt< TypeList< Head, Tail >, 0 >{ 
    typedef Head Result;
};
template< typename Head, typename Tail, unsigned int i > 
struct TypeAt< TypeList< Head, Tail >, i > {
    typedef typename TypeAt< Tail, i - 1 >::Result Result;
};

/*
 * Returns the index of type T in TList, or -1 if not found.
 */
template< typename TList, typename T > struct IndexOf;
template< typename T > struct IndexOf< NullType, T > { enum { value = -1 }; };
template< typename T, typename U > struct IndexOf< TypeList< T, U >, T > {
    enum { value = 0 };
};
template< typename Head, typename Tail, typename T > 
struct IndexOf< TypeList< Head, Tail >, T > {
    private: enum { temp = IndexOf< Tail, T >::value };
    public: enum { value = temp == -1 ? -1 : 1 + temp };
};

/*
 * Appends T to TList.  T may be an atomic type or a TypeList
 */
template< typename TList, typename T > struct Append;
template<> struct Append< NullType, NullType > { typedef NullType Result; };
template< typename T > struct Append< NullType, T > {
    typedef TypeList< T, NullType > Result; 
};
template< typename Head, typename Tail > 
struct Append< NullType, TypeList< Head, Tail > > {
    typedef TypeList< Head, Tail > Result; 
};
template< typename Head, typename Tail, typename T > 
struct Append< TypeList< Head, Tail >, T > {
    typedef TypeList< Head, typename Append< Tail, T >::Result > Result;
};

/*
 * Erases the first instance of T in TList
 */
template< typename TList, typename T > struct Erase;
template< typename T > struct Erase< NullType, T > { typedef NullType Result; };
template< typename Tail, typename T > struct Erase< TypeList< T, Tail >, T > {
    typedef Tail Result;
};
template< typename Head, typename Tail, typename T >
struct Erase< TypeList< Head, Tail >, T > {
    typedef TypeList< Head, typename Erase< Tail, T >::Result > Result;
};

/*
 * Erases all found instances of T in TList
 */
template< typename TList, typename T > struct EraseAll;
template< typename T > struct EraseAll< NullType, T > { 
    typedef NullType Result; 
};
template< typename Tail, typename T > 
struct EraseAll< TypeList< T, Tail >, T > {
    typedef typename EraseAll< Tail, T >::Result Result;
};
template< typename Head, typename Tail, typename T > 
struct EraseAll< TypeList< Head, Tail >, T > {
    typedef TypeList< Head, typename EraseAll< Tail, T >::Result > Result;
};

/*
 * Removes all duplicates from TList
 */
template< typename TList > struct NoDuplicates;
template<> struct NoDuplicates< NullType > { typedef NullType Result; };
template< typename Head, typename Tail > 
struct NoDuplicates< TypeList< Head, Tail > > {
private:
    typedef typename NoDuplicates< Tail >::Result L1;
    typedef typename Erase< L1, Head >::Result L2;
public:
    typedef TypeList< Head, L2 > Result;
};

/*
 * Replaces the first instance of T in TList by U.
 */
template< typename TList, typename T, typename U > struct Replace;
template< typename T, typename U > struct Replace< NullType, T, U > { 
    typedef NullType Result; 
};
template< typename Tail, typename T, typename U > 
struct Replace< TypeList< T, Tail >, T, U > {
    typedef TypeList< U, Tail > Result;
};
template< typename Head, typename Tail, typename T, typename U >
struct Replace< TypeList< Head, Tail >, T, U > {
    typedef TypeList< Head, typename Replace< Tail, T, U >::Result > Result;
};

/*
 * Replaces all T in TList by type U.
 */
template< typename TList, typename T, typename U > struct ReplaceAll;
template< typename T, typename U > struct ReplaceAll< NullType, T, U > { 
    typedef NullType Result; 
};
template< typename Tail, typename T, typename U > 
struct ReplaceAll< TypeList< T, Tail >, T, U > {
    typedef TypeList< U, typename ReplaceAll< Tail, T, U >::Result > Result;
};
template< typename Head, typename Tail, typename T, typename U >
struct ReplaceAll< TypeList< Head, Tail >, T, U > {
    typedef TypeList< Head, typename ReplaceAll< Tail, T, U >::Result> Result;
};

/*
 * Returns the type in TList which is the most derived from T.  If T is 
 * already the most derived, it is returned.
 */
template< typename TList, typename T > struct MostDerived;
template< typename T > struct MostDerived< NullType, T > { typedef T Result; };
template< typename Head, typename Tail, typename T >
struct MostDerived< TypeList< Head, Tail >, T > {
private:
    typedef typename MostDerived< Tail, T >::Result Candidate;
public:
    typedef typename Select< SUPERSUBCLASS(Candidate, Head), Head, Candidate 
        >::Result Result;
};

/*
 * Inserts type T one index before the first instance of type U.  If no 
 * U is found, T is appended.
 */
template< typename TList, typename T, typename U > struct InsertBefore;
template< typename T, typename U > struct InsertBefore< NullType, T, U > {
    typedef TypeList< T, NullType > Result;
};
template< typename Tail, typename T, typename U > 
struct InsertBefore< TypeList< U, Tail>, T, U > {
    typedef TypeList< T, TypeList< U, Tail > > Result;
};
template< typename Head, typename Tail, typename T, typename U >
struct InsertBefore< TypeList< Head, Tail >, T, U > {
    typedef TypeList< Head, typename InsertBefore< Tail, T, U >::Result 
        > Result;
};

/*
 * Moves the items in a TypeList such that the deepest child of an 
 * inheritance chain is guaranteed to be before its parents.
 * Independent inhericance hierarchies will remain in the order of 
 * their original typelist.
 *
 * Ex.
 *     TL_5(Widget, ScrollBar, Button, GraphicButton, SmoothScrollbar)
 *    
 *   is transformed to
 *     TL_5(SmoothScrollBar, ScrollBar, GraphicButton, Button, Widget)
 */
template< typename TList > struct DerivedToFront;
template<> struct DerivedToFront< NullType > {
    typedef NullType Result;
};
template< typename Head, typename Tail > 
struct DerivedToFront< TypeList< Head, Tail > > {
private:
    typedef typename MostDerived< Tail, Head >::Result TheMostDerived;
    typedef typename Replace< Tail, TheMostDerived, Head >::Result L1;
public:
    typedef TypeList< TheMostDerived, typename DerivedToFront< L1 >::Result 
        > Result;
};

#define TL_1(T1) TypeList<T1, NullType>
#define TL_2(T1, T2) TypeList<T1, TL_1(T2)>
#define TL_3(T1, T2, T3) TypeList<T1, TL_2(T2, T3)>
#define TL_4(T1, T2, T3, T4) TypeList<T1, TL_3(T2, T3, T4)>
#define TL_5(T1, T2, T3, T4, T5) TypeList<T1, TL_4(T2, T3, T4, T5)>
#define TL_6(T1, T2, T3, T4, T5, T6) TypeList< T1, TL_5(T2, T3, T4, T5, T6)>

#endif // META_TYPELIST_HPP