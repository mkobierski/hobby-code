#include <cstdio>

namespace Q9 {

int isPyTrip (int a, int b, int c) {
    return a*a + b*b == c*c ? 1 : 0;
}

int solve(int target) {
    int a = 3;
    int b = 4;
    int c = 5;

    for (a = 3; a < target; a++) {
        for(b = a+1; b < target; b++) {
            for(c = b+1; c < target; c++) {
                if(isPyTrip(a,b,c) && (a + b + c == target)) {
                    return a*b*c;
                }
            }
        }
    }
    return 0;
}

int solveAndPrint() {
    const int input = 1000;
    int answer = solve(input);
    printf("Q9: The answer using %d is %d",
           input, answer);
    return answer;
}

} // namespace Q9
