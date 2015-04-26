"""ProjectGenerator/generate.py: A script for generating a workspace for
project euler problems.

usage:
    generate.py [source_root]

- source_root defaults to "../"

"""

import os
import sys

from projgen.builder import ProjectBuilder
import projgen.content
import projgen.utils as utils

class Projects(object):
    def __init__(self):
        self.needs_common = False

class StandaloneProjects(Projects):
    ITEMS = [
        1,
        2,
        3,
        6,
        7,
        9,
    ]
    def __init__(self):
        super(StandaloneProjects, self).__init__()

class DependentProjects(Projects):
    ITEMS = [
        4,
        5,
        8,
    ]
    def __init__(self):
        super(DependentProjects, self).__init__()
        self.needs_common = True

class AllProjects(object):
    def __init__(self):
        self.groups = [
            StandaloneProjects(),
            DependentProjects()
        ]

def create_files(proj_builder):
    proj_builder.create_cmakelists()
    proj_builder.create_csource()

def build_project(proj_builder):
    print "{}...".format(proj_builder.name),
    if proj_builder.dir_is_clean():
        try:
            create_files(proj_builder)
        except Exception as e:
            print "FAIL"
        else:
            print "OK"
    else:
        print "Dirty"

def build_projects(projects):
    print "Building projects..."
    for group in projects.groups:
        for project in group.ITEMS:
            name = utils.namify(project)
            build_project(
                ProjectBuilder(name, proj_dir=project, 
                    needs_common=group.needs_common))
    print "Done"

def main():
    if len(sys.argv) > 2:
        print __doc__
        return 1
    src_root = sys.argv[1] if len(sys.argv) == 2 else "../"
    old_cwd = os.getcwd()
    try:
        os.chdir(src_root)
        build_projects(AllProjects())
    finally:
        os.chdir(old_cwd)
    return 0

# active_project_nums = ["1",]

if __name__ == "__main__":
    sys.exit(main())