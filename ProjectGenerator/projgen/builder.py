"""This module contains classes for encapsulating information needed
to build individual projects.

"""

import os

import projgen.utils as utils
import projgen.content as ctnt

class ProjectInfo(object):
    def __init__(self, proj_name, proj_dir, needs_common):
        self._name = proj_name
        self._dir = proj_dir
        self._needs_common = needs_common

    @property
    def name(self):
        return self._name

    @property
    def dir(self):
        return self._dir

    @property
    def needs_common(self):
        return self._needs_common

class ProjectBuilder(object):
    """Stores information, such as name, directory, and dependencies
    for individual projects.

    """
    def __init__(self, proj_name, proj_dir=None, needs_common=False):
        if not proj_dir:
            proj_dir = proj_name
        self._info = ProjectInfo(str(proj_name), str(proj_dir),
            bool(needs_common))

        self._cmakelists = ctnt.CMakeLists(self._info)
        self._csource = ctnt.CSource(self._info)

    def dir_is_clean(self):
        for fname in (self._cmakelists.fname, ) + self._csource.fnames():
            if os.path.isfile(fname):
                return False
        return True

    def create_cmakelists(self):
        """Creates and writes the content of CMakeLists.txt for the
        project.

        """
        self._create_proj_dir()
        utils.verify_nonexistant(self._cmakelists.fname)

        lines = self._cmakelists.project_str()
        with open(self._cmakelists.fname, "w") as f:
            f.writelines(lines)

    def create_csource(self):
        self._create_proj_dir()
        for fname, content in self._csource.files():
            utils.verify_nonexistant(fname)
            with open(fname, "w") as f:
                f.writelines(content)

    def _create_proj_dir(self):
        if not os.path.isdir(self._info.dir):
            os.makedirs(self._info.dir)