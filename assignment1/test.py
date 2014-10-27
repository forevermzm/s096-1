import sys
import glob
import subprocess
from os import listdir
from os.path import isfile, join

passed = 1

def test(cmd, path):
    infiles = [ f for f in listdir(path) if isfile(join(path,f)) ]
    infiles = [ f for f in infiles if f.rfind("out") != len(f) -3]
    print infiles
    for file in infiles:
        outputs = subprocess.check_output((cmd + " " + path + file).split())
        outputs = outputs.split("\n")
        check_output(path, file, outputs)
        print "File: %s is passed: %s" %(file, str(passed == 1))

def check_output(path, filename, outputs):
    global passed;
    li = filename.split(".")
    li[len(li) - 1] = "out";
    out_filename = path + ".".join(li);
    lines = open(out_filename, "r").readlines();
    lines = [ line.replace("\r", "") for line in lines]
    for i in range(len(outputs) - 1):
        if outputs[i] != lines[i].replace("\n", ""):
            passed = 0;
            print out_filename + ": " + str(i);
            print outputs[i];
            print lines[i];


def main(argv):
    test(argv[0], argv[1])

    print "The whole test is passed: " + str(passed == 1)

if __name__ == "__main__":
    if len(sys.argv) == 2:
        print "Usage: test.py [cmd] [tests_dir]"
    else :
        main(sys.argv[1:])