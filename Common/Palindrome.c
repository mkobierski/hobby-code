#include "Palindrome.h"

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

char isPalindrome (int num) {
    char text[15] = {0};
    int  left     = 0;
    int  right    = 0;
    int  len      = -1;
    if(num < 0) {
        num *= -1;
    }

    len = sprintf(text, "%d", num);
    if(len <= 0) {
        return 0;
    }

    left = 0;
    right = len - 1;
    while(left < right) {
        if(text[left] != text[right]) {
            return 0;
        }
        ++left;
        --right;
    }
    return 1;
}

#ifdef __cplusplus
}  /* extern "C" */
#endif // __cplusplus