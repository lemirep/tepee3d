#!/usr/bin/env python

import subprocess
import shutil
import sys
import os

def browse_source_dir(entry):
#    print "Entry " + entry
    if os.path.isdir(entry):
        gcov_source_file(entry)

def gcov_source_file(folder_entry):
    try:
        print "gcov -o " + folder_entry + " *.cpp"
        return_value = subprocess.call("gcov -o " + folder_entry + " *.cpp", shell=True)
        print "Returned {" + str(return_value) + "}"
    except OSError as ex:
        print ex
        
def main(args):
    if len(args) <= 1:
        print "./gcov_files source_dir source_dir ..."
    else:
        try:
            arg = args[0]
            for path in args:
                return_value = subprocess.call("lcov --base-directory " + path + " --directory " + path + " -c -o " + path + "/coverage.info", shell=True)
                print "Returned {" + str(return_value) + "}"
                if not path is arg:
                    subprocess.call("cat " + path + "/coverage.info >> " + arg + "/coverage.info", shell=True)

            print "genhtml -o " + arg + "/coverage -t Coverage " + arg + "/coverage.info"
            return_value = subprocess.call("genhtml -o " + arg + "/coverage -t Coverage " + arg + "/coverage.info", shell=True)
            print "Returned {" + str(return_value) + "}"
            if return_value != 0 :
                exit(return_value)
            for path in args:
                subprocess.call("cd " + path + " && rm *.gcda *.gcno coverage.info && make clean", shell=True)
        except OSError as ex:
            print ex;


if __name__ == '__main__':
    main(sys.argv[1:]);


