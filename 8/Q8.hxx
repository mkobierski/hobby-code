#include "Common.hpp"

#include <string>

namespace Q8 {

    template<unsigned int len>
    long long solve(std::string const & fname) {
        File file(fname);
        if(!file.isOk()) {
            return 0;
        }

        Common::CircularBuffer<int, len> buffer;

        // fill buffer
        int c = -1;
        for(unsigned int i = 0; i < len; ++i) {
            if(file.getSingleInt(&c)) {
                buffer.insert(c);
            }
        }

        long long maxProduct = Common::multiplyElementsOf(buffer);
        long long product = 0;
        while(file.isOk()) {
            if(file.getSingleInt(&c)) {
                buffer.insert(c);
            }
            product = Common::multiplyElementsOf(buffer);
            if(product > maxProduct) {
                maxProduct = product;
            }
        }
        return maxProduct;
    }

}