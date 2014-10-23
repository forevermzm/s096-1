import glob
import subprocess

passed = 1

def test():
    infiles = glob.glob("tests/*.in")
    for file in infiles:
        outputs = subprocess.check_output(("./Floating " + file).split())
        outputs = outputs.split("\n")
        check_output(file, outputs)

def check_output(filename, outputs):
    global passed;
    li = filename.split(".")
    li[len(li) - 1] = "out";
    out_filename = ".".join(li);
    lines = open(out_filename, "r").readlines();
    for i in range(len(outputs) - 1):
        if outputs[i] != lines[i].replace("\n", ""):
            passed = 0;
            print out_filename + str(i);
            print outputs[i];
            print lines[i];


def main():
    test()

if __name__ == "__main__":
    main()