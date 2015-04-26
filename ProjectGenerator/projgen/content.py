"""Contains string literals of boilerplate code for project creation.
The strings are intended to be used with string.format(), and thus
contain replacable tokens in {braces}.

"""

import os

class ContentObj(object):
    def __init__(self, proj_info):
        self._proj_info = proj_info

    def _make_path(self, text, named=False):
        if named:
            text = text.format(self._proj_info.name)
        return os.path.join(self._proj_info.dir, text)


class CMakeLists(ContentObj):
    FNAME = "CMakeLists.txt"
    SKELETON = """project({proj_name})

set(SRC_COMMON {proj_name}.cpp {proj_name}.hpp)
set(SRC_MAIN main.cpp)
set(SRC_TEST {proj_name}-test.cpp)
{add_exec}
install(TARGETS ${{PROJECT_NAME}} ${{PROJECT_NAME}}-test
        DESTINATION ${{INSTALL_BIN}})

add_test(NAME ${{PROJECT_NAME}}TestOK
            COMMAND ${{PROJECT_NAME}}-test)
"""

    ADD_EXEC = """
add_executable(${PROJECT_NAME} ${SRC_MAIN} ${SRC_COMMON})
add_executable(${PROJECT_NAME}-test ${SRC_TEST} ${SRC_COMMON})
"""
    ADD_EXEC_WITH_COMMON = """
add_executable(${PROJECT_NAME} ${SRC_MAIN} ${SRC_COMMON})
target_link_libraries (${PROJECT_NAME} Common)

add_executable(${PROJECT_NAME}-test ${SRC_TEST} ${SRC_COMMON})
target_link_libraries (${PROJECT_NAME}-test Common)
"""

    def __init__(self, proj_info):
        super(CMakeLists, self).__init__(proj_info)

        self._fname = self._make_path(self.FNAME)

    @property
    def fname(self):
        return self._fname

    def project_str(self):
        return self.SKELETON.format(proj_name=self._proj_info.name,
            add_exec=self._add_exec())

    def _add_exec(self):
        if self._proj_info.needs_common:
            return self.ADD_EXEC_WITH_COMMON
        return self.ADD_EXEC

class CSource(ContentObj):
    MAIN_FNAME = "main.cpp"
    CPP_FNAME = "{}.cpp"
    HPP_FNAME = "{}.hpp"
    CPP_TEST_FNAME = "{}-test.cpp"
    CPP = """#include <cstdio>

namespace {proj_name} {{

int solve(int input) {{
    /*
     * Process input here
     */
    return 0;
}}

int solveAndPrint() {{
    const int input = 20;
    int answer = solve(input);
    printf("{proj_name}: The answer using %d is %d",
           input, answer);
    return answer;
}}

}} // namespace {proj_name}
"""
    HPP = """#ifndef PROJECTEULER_{proj_name}_H_
#define PROJECTEULER_{proj_name}_H_

namespace {proj_name} {{
    int solve(int);
    int solveAndPrint();
}}

#endif // PROJECTEULER_{proj_name}_H_
"""
    CPP_TEST = """#include "Verify.hpp"

#include "{proj_name}.hpp"

int main() {{
    check( /* {proj_name}::solve() == */ 1 );
    return 0;
}}
"""
    MAIN = """#include "{proj_name}.hpp"

#include <stdio.h>

int main () {{
    {proj_name}::solveAndPrint();
    getchar();
    return 0;
}}
"""

    def __init__(self, proj_info):
        super(CSource, self).__init__(proj_info)

        self._main_fname = self._make_path(self.MAIN_FNAME)
        self._cpp_fname = self._make_path(self.CPP_FNAME, named=True)
        self._hpp_fname = self._make_path(self.HPP_FNAME, named=True)
        self._cpp_test_fname = self._make_path(self.CPP_TEST_FNAME, named=True)

    def fnames(self):
        return (self.main_fname,
            self.cpp_fname,
            self.hpp_fname,
            self.cpp_test_fname)

    def files(self):
        for pair in [(self.main_fname, self.main),
                (self.cpp_fname, self.cpp),
                (self.hpp_fname, self.hpp),
                (self.cpp_test_fname, self.cpp_test)]:
            yield pair

    @property
    def proj_name(self):
        return self._proj_info.name

    @property
    def main(self):
        return self.MAIN.format(proj_name=self.proj_name)

    @property
    def cpp(self):
        return self.CPP.format(proj_name=self.proj_name)

    @property
    def hpp(self):
        return self.HPP.format(proj_name=self.proj_name)

    @property
    def cpp_test(self):
        return self.CPP_TEST.format(proj_name=self.proj_name)

    @property
    def main_fname(self):
        return self._main_fname

    @property
    def cpp_fname(self):
        return self._cpp_fname

    @property
    def hpp_fname(self):
        return self._hpp_fname

    @property
    def cpp_test_fname(self):
        return self._cpp_test_fname