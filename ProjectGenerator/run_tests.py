import sys

from projgen.builder import ProjectBuilder
import projgen.content
import projgen.utils as utils

class Test(object):
    PASS = -1
    FAIL = -2
    class InvalidResult(Exception):
        def __str__(self):    
            return "An invalid test result was received"

def test_create_cmakelists():
    pb = ProjectBuilder(utils.namify(100), proj_dir=100)
    pb.create_cmakelists()

    pb = ProjectBuilder(utils.namify(101), needs_common=True, proj_dir="tests/101")
    pb.create_cmakelists()
    return Test.PASS

def show_results(num_pass, num_fail):
    total = num_pass + num_fail
    print "Total of {} test{} completed.".format(total,
        '' if total == 1 else 's')
    print "Passed: {}".format(num_pass)
    print "Failed: {}".format(num_fail)

def run_test(test_fn, test_params):
    try:
        return test_fn(*test_params)
    except Exception as e:
        return Test.FAIL


def run_tests(tests):
    passed = 0
    failed = 0
    for name, test_info in tests.iteritems():
        print "Test - {}... ".format(name)
        assert len(test_info) == 2, "test_info must contain 2 elements"
        res = run_test(*test_info)
        if res == Test.PASS:
            passed += 1
            print "Pass"
        elif res == Test.FAIL:
            failed += 1
            print "Fail"
        else:
            raise Test.InvalidResult()
    return (passed, failed)

def test_main():
    tests = {
        "CreateCMakeLists": (
            test_create_cmakelists,
            (),
        )
    }
    results = run_tests(tests)
    show_results(*results)
    raw_input("[Enter] to close")
    return 0

if __name__ == "__main__":
    sys.exit(test_main())