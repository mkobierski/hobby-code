import os
import sys

def cmakelists_file():
    return "CMakeLists.txt"
def cmake_project_str():
    return """project({proj_name})

set(SRC_COMMON {proj_name}.cpp {proj_name}.hpp)
set(SRC_MAIN main.cpp)
set(SRC_TEST {proj_name}-test.cpp)

{add_exec}

install(TARGETS ${{PROJECT_NAME}} ${{PROJECT_NAME}}-test
        DESTINATION ${{INSTALL_BIN}})

add_test(NAME ${{PROJECT_NAME}}TestOK
         COMMAND ${{PROJECT_NAME}}-test)
"""

def cmake_add_exec():
    return """add_executable(${{PROJECT_NAME}} ${{SRC_MAIN}} ${{SRC_COMMON}})
add_executable(${{PROJECT_NAME}}-test ${{SRC_TEST}} ${{SRC_COMMON}})
"""

def cmake_add_exec_using_common():
    return """add_executable(${{PROJECT_NAME}} ${{SRC_MAIN}} ${{SRC_COMMON}})
target_link_libraries (${{PROJECT_NAME}} Common)

add_executable(${{PROJECT_NAME}}-test ${{SRC_TEST}} ${{SRC_COMMON}})
target_link_libraries (${{PROJECT_NAME}}-test Common)
"""


def create_cmakelists(project_num, project_dir, using_common=False):
    proj_name = "Q{}".format(project_num)
    add_exec = cmake_add_exec()
    if using_common:
        add_exec = cmake_add_exec_using_common()

    lines = cmake_project_str().format(
        proj_name = proj_name,
        add_exec = add_exec)
    project_dir = str(project_dir)
    if not os.path.isdir(project_dir):
        os.makedirs(project_dir)
    fname = os.path.join(project_dir, cmakelists_file())
    if os.path.isfile(fname):
        print "{} exists, aborting..."
        return 1
    with open(fname, "w") as f:rs
        f.writelines(lines)
    return 0

def test_create_cmakelists():
    create_cmakelists(100, 100)
    create_cmakelists(101, "tests/101", using_common=True)

def main():
    test_create_cmakelists()

# active_project_nums = ["1",]

if __name__ == "__main__":
    sys.exit(main())