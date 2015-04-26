"""This module contains a collection of utilities."""

import os
import sys

def namify(proj_num):
    assert isinstance(proj_num, (int, long)) \
        , "proj_num must be an integral type"
    return "Q{}".format(proj_num)

def verify_nonexistant(fname):
    if os.path.isfile(fname):
        print "{} exists.  Aborting...".format(fname)
        quit(1)

def quit(ret_code=0):
    raw_input("Press [Enter] to continue")

    sys.exit(ret_code)
    