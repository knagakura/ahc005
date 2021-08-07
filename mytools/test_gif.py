import subprocess
import os
import sys
import time
import datetime
import glob
from PIL import Image
from svglib.svglib import svg2rlg
from reportlab.graphics import renderPDF, renderPM
import cairosvg

def runShell(s):
    print(s)
    subprocess.run(s, shell=True)


# cppFile = input()
print(sys.argv)
cppFile = "src/a.cpp"
inFile = "./tools/example.in"
outFile = "out.txt"

if len(sys.argv) >= 2:
    cppFile = sys.argv[1]
if len(sys.argv) >= 3:
    inFile = sys.argv[2]
if len(sys.argv) >= 4:
    outFile = sys.argv[3]

compile = "g++-9 -O2 -std=gnu++17 -Wall -Wextra -Wshadow -DDEBUG -DFIG {}".format(cppFile)

print(runShell("pwd"))

jikkou = "./a.out < {} > {}".format(inFile, outFile)

runShell(compile)

if(os.path.exists(outFile)):
    runShell("rm {}".format(outFile))

runShell(jikkou)
# root directoryからの相対パスで書く


dt_now = datetime.datetime.now()
outtxtdir = "tools/outs/{}/txt".format(dt_now.strftime('%Y%m%d_%H%M%S'))
outsvgdir = "tools/outs/{}/svg".format(dt_now.strftime('%Y%m%d_%H%M%S'))
os.makedirs(outtxtdir, exist_ok=True)
os.makedirs(outsvgdir, exist_ok=True)

def readlines_file(file_name):
    with open(file_name, 'r') as file:
        return file.readlines()

def save_file(file_name, text):
    with open(file_name, 'w') as file:
        file.write(text)

lines = readlines_file("{}".format(outFile))
for i in range(len(lines)):
    tmpoutfile = "{}/{:04d}.txt".format(outtxtdir,i)
    tmpsvgfile = "{}/{:04d}.svg".format(outsvgdir, i)
    tmppngfile = "{}/{:04d}.png".format(outsvgdir, i)
    save_file(tmpoutfile, lines[i])
    runTest = "cd tools && cargo run --release --bin vis ../{} ../{} && cd ..".format(inFile, tmpoutfile)
    runShell(runTest)
    # drawing  = svg2rlg("tools/out.svg")
    # renderPM.drawToFile(drawing, "tools/out.png")
    cairosvg.svg2png("tools/out.svg", "tools/out.png")
    runShell("mv tools/out.png {}".format(tmppngfile))
frames = []
images = sorted(glob.glob("{}/*.png".format(outsvgdir)))

for image in images:
    new_frame = Image.open(image)
    frames.append(new_frame)

frames[0].save('{}/jpg_to_gif.gif'.format(outsvgdir),
               format='GIF',
               append_images=frames[1:],
               save_all=True,
               duration=500,
               loop=0)