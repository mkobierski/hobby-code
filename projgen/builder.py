"""This module contains classes for encapsulating information needed
to build individual projects.

"""

import os
import projgen.content

class ProjectBuilder(object):
    """Stores information, such as name, directory, and dependencies
    for individual projects.

    """
    def __init__(self, proj_name, needs_common=False, proj_dir=None):
        if not proj_dir:
            proj_dir = proj_name
        self._proj_name = str(proj_name)
        self._proj_dir = str(proj_dir)
        self._needs_common = bool(needs_common)

    def create_cmakelists(self):
        """Creates and writes the content of CMakeLists.txt for the
        project.

        """
        if not os.path.isdir(self._proj_dir):
            os.makedirs(self._proj_dir)

        fname = os.path.join(self._proj_dir, projgen.content.cmakelists_fname())
        if os.path.isfile(fname):
            print "{} exists, aborting...".format(fname)
            return 1

        lines = projgen.content.cmake_project_str(
                  self._proj_name
                , self._needs_common)
        with open(fname, "w") as f:
            f.writelines(lines)
        return 0