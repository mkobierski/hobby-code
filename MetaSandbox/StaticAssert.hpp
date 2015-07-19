#ifndef META_STATICASSERT_HPP
#define META_STATICASSERT_HPP

template<bool>
struct StaticAssert {
    StaticAssert(...);
};

template<>
struct StaticAssert<false> { };

#define STATIC_ASSERT(x, reason) {  \
    struct Error_##reason {}; \
    sizeof( (StaticAssert<(x)>( (Error_##reason()) ) ) );    \
}

#endif // META_STATICASSERT_HPP