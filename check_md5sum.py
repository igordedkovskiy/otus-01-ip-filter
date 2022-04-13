# Python program to find MD5 hash value of a file
import hashlib
import subprocess
import sys
import os
from pathlib import Path
#from argparse import ArgumentParser

#parser = ArgumentParser()
#parser.add_argument("-f", "--file", dest="filename", help="file to count md5", metavar="FILE")

def count(filename):
    md5_hash = hashlib.md5()
    with open(filename,"rb") as f:
        # Read and update hash in chunks of 4K
        for byte_block in iter(lambda: f.read(4096),b""):
            md5_hash.update(byte_block)
    return md5_hash

def main():    
    curdir = Path(os.getcwd()).resolve()
    filename = "res.txt"
    executable = "ip_filter"
    inputfile = "ip_filter.tsv"
    builddir = "Release"
    
    if sys.platform == "win32":
    #    if curdir == Path(sys.path[0]).resolve():
    #        filename = "./" + builddir + "/" + filename + ".exe"
    #        executable = "./" + builddir + "/" + executable
    #        inputfile = "./" + inputfile
    #    else:
    #        filename = "./" + filename
    #        executable = "./" + executable
    #        inputfile = "../" + inputfile
    #    command_line = "%s < %s > %s" % (Path(executable).resolve(), Path(inputfile).resolve(), Path(filename).resolve())
    #    md5 = "36b72c25de983078b68625b7610e7673" # win
    #elif sys.platform == "linux":
        if curdir == Path(sys.path[0]).resolve():
            filename = "./" + builddir + "/" + filename
            executable = "./" + builddir + "/" + executable + ".exe"
            inputfile = "./" + inputfile
        else:
            filename = "./" + filename
            executable = "./" + executable + ".exe"
            inputfile = "../" + inputfile
        print(filename)
        print(executable)
        print(inputfile)
        print(Path(inputfile).resolve())
        print(Path(executable).resolve())
        print(Path(filename).resolve())
        #command_line = "cat %s | %s > %s" % (Path(inputfile).resolve(), Path(executable).resolve(), Path(filename).resolve())
        command_line = "cat %s | %s > %s" % (inputfile, executable, filename)
        md5 = "24e7a7b2270daee89c64d3ca5fb3da1a" # nix
        md5 = "36b72c25de983078b68625b7610e7673" # win
    else:
        return -1
        
    result = subprocess.run(command_line, shell=True)
    #answer = count(Path(filename).resolve())
    answer = count(filename)
    #os.remove(Path(filename).resolve())
    print(answer.hexdigest())
    if md5 != answer.hexdigest():
        return -1
    return 0

if __name__ == "__main__":
    if main() != 0:
        print("Wrong hash sum!")
        sys.exit(-1)
    print("Ok!")
    sys.exit(0)
