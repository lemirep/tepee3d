#!/usr/bin/env python

import subprocess
import shutil
import sys
import os

def browse_source_dir(entry):
    print "Entry " + entry
    if os.path.isfile(entry):
        gcov_source_file(entry);
    elif os.path.isdir(entry):
        for file_entry in os.listdir(entry):
            gcov_source_file(file_entry)


def gcov_source_file(file_entry):
    if file_entry.endswith(".cpp"):
        try:
            return_value = subprocess.call("gcov " + file_entry, shell=True)
            print "Returned {" + str(return_value) + "}"
        except OSError as ex:
            print ex
        
def main(args):
    if len(args) == 0:
        print "Not Enough Args"
    else:
        for arg in args:
            browse_source_dir(arg)
        try:
            return_value = subprocess.call("lcov --base-directory . --directory . -c -o coverage.info", shell=True)
            print "Returned {" + str(return_value) + "}"
            if return_value != 0 :
                exit(return_value)
            return_value = subprocess.call("genhtml -o ./coverage -t Coverage coverage.info", shell=True)
            print "Returned {" + str(return_value) + "}"
            if return_value != 0 :
                exit(return_value)
            subprocess.call("rm *.gcda *.gcno coverage.info && make clean", shell=True)
        except OSError as ex:
            print ex;


if __name__ == '__main__':
    main(sys.argv[1:]);


