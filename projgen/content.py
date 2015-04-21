"""Contains string literals of boilerplate code for project creation.
The strings are intended to be used with string.format(), and thus
contain replacable tokens in {braces}.

"""

def cmakelists_fname():
    return "CMakeLists.txt"

def cmake_project_str(proj_name, using_common=False):
    add_exec = (
            cmake_add_exec_using_common() if using_common
            else cmake_add_exec())
    return """project({proj_name})

set(SRC_COMMON {proj_name}.cpp {proj_name}.hpp)
set(SRC_MAIN main.cpp)
set(SRC_TEST {proj_name}-test.cpp)
{add_exec}
install(TARGETS ${{PROJECT_NAME}} ${{PROJECT_NAME}}-test
        DESTINATION ${{INSTALL_BIN}})

add_test(NAME ${{PROJECT_NAME}}TestOK
         COMMAND ${{PROJECT_NAME}}-test)
""".format(proj_name=proj_name, add_exec=add_exec)

def cmake_add_exec():
    return """
add_executable(${{PROJECT_NAME}} ${{SRC_MAIN}} ${{SRC_COMMON}})
add_executable(${{PROJECT_NAME}}-test ${{SRC_TEST}} ${{SRC_COMMON}})
"""

def cmake_add_exec_using_common():
    return """
add_executable(${{PROJECT_NAME}} ${{SRC_MAIN}} ${{SRC_COMMON}})
target_link_libraries (${{PROJECT_NAME}} Common)

add_executable(${{PROJECT_NAME}}-test ${{SRC_TEST}} ${{SRC_COMMON}})
target_link_libraries (${{PROJECT_NAME}}-test Common)
"""

def cpp_proj_str(proj_name):
    return """namespace {proj_name} {

int solve(int input) {
    /*
     * Process input here
     */
    return 0;
}

int solveAndPrint() {
    const int input = 20;
    int answer = solve(factor);
    printf("{proj_name}: The answer using %d is %d",
           input, answer);
    return answer;
}

} // namespace {proj_name}
""".format(proj_name=proj_name)

def hpp_proj_str(proj_name):
    return """#ifndef PROJECTEULER_{proj_name}_H
#define PROJECTEULER_{proj_name}_H

namespace {proj_name} {
    int solve();
    int solveAndPrint();
}

#endif // PROJECTEULER_{proj_name}_H
""".format(proj_name=proj_name)

def cpp_proj_test_str(proj_name):
    return """#include "Verify.hpp"

#include "{proj_name}.hpp"

int main() {
    check( /* {proj_name}::solve() == 0 */ );
    return 0;
}
""".format(proj_name=proj_name)