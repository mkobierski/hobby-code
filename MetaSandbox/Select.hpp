#ifndef META_SELECT_HPP
#define META_SELECT_HPP

template< bool, typename T, typename U > struct Select {
    typedef T Result;
};
template< typename T, typename U > struct Select< false, T, U > {
    typedef U Result;
};

#endif // META_SELECT_HPP

