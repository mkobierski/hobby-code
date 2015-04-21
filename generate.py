import sys

import projgen.content
from projgen.builder import ProjectBuilder

def namify(proj_num):
    return "Q{}".format(proj_num)

def test_create_cmakelists():
    pb = ProjectBuilder(namify(100), proj_dir=100)
    pb.create_cmakelists()
    pb = ProjectBuilder(namify(101), needs_common=True, proj_dir="tests/101")
    pb.create_cmakelists()

def main():
    test_create_cmakelists()

# active_project_nums = ["1",]

if __name__ == "__main__":
    sys.exit(main())