#pragma once

namespace Q1 {
    namespace Method1 {}
    namespace Method2 {}
    using namespace Method2;

    namespace Method1 {
        int solve(int limit);
        int solveAndPrint();
    }

    namespace Method2 {
        template<unsigned multiplier, unsigned limit, unsigned val = limit>
            struct Accumulate {
                enum {
                    LimitedVal = val < limit
                                 ? val
                                 : limit - 1,
                    NormalizedVal = LimitedVal - (LimitedVal % multiplier),
                    NextVal = NormalizedVal >= multiplier
                              ? NormalizedVal - multiplier
                              : 0,
                    Result = NormalizedVal + Accumulate<multiplier, limit, NextVal>::Result
                };
            };
        template<unsigned multiplier, unsigned limit>
            struct Accumulate<multiplier, limit, 0> {
                enum {
                    Result = 0
                };
            };

        template<unsigned limit>
            struct Solve {
                enum {
                    Result = Accumulate<3, limit>::Result 
                             + Accumulate<5, limit>::Result
                             - Accumulate<15, limit>::Result
                };
            };

        int solveAndPrint();
    }
}