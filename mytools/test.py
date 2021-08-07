import subprocess
import os
import sys
def runShell(s):
    print(s)
    subprocess.run(s, shell=True)


# cppFile = input()
print(sys.argv)
cppFile = "src/a.cpp"
inFile = "./tools/in/0000.txt"
outFile = "out.txt"

if len(sys.argv) >= 2:
    cppFile = sys.argv[1]
if len(sys.argv) >= 3:
    inFile = sys.argv[2]
if len(sys.argv) >= 4:
    outFile = sys.argv[3]

compile = "g++-9 -O2 -std=gnu++17 -Wall -Wextra -Wshadow -DDEBUG {}".format(cppFile)

print(runShell("pwd"))

jikkou = "./a.out < {} > {}".format(inFile, outFile)

runShell(compile)

if(os.path.exists(outFile)):
    runShell("rum {}".format(outFile))

runShell(jikkou)
# root directoryからの相対パスで書く

runTest = "cd tools && cargo run --release --bin vis ../{} ../{} && open vis.html && cd ..".format(inFile, outFile)
runShell(runTest)