import sys

## Takes in one argument, a string, and reads in <arg>.bmp to write out <arg>.bin
## For example, `python bmp_to_bin.py five` reads in five.bmp and outputs five.bin

## Read in .bmp file and skip past BMP header
infile = open(sys.argv[1] + ".bmp", "rb")
infile.seek(54) ## Header is 54 bits long

## Write appropriate header (25 1) to binary file
index = 0
outfile = open(sys.argv[1] + ".bin", "wb+")
# header_arr = [16, 3, 0, 0, 1, 0, 0, 0]
# byte_header = bytearray(header_arr)
# outfile.write(byte_header)

## Read in BMP file, differentiating between white pixels (r = g = b = 0xff) and non-white pixels
ff_byte = '0xFF'
ff_ba = bytearray([int(ff_byte, 16)])
toprint = ""
line = []
all_lines = []

t = 0
# test = infile.read()
# print("# pixels", len(test))
# print("full input ", test)

ofile = [0 for _ in range(625)]

count = 0
while index < 625:
    if(count != 0):
        if(count%75 == 0):
            infile.read(1)
    count += 3
    r = infile.read(1)
    b = infile.read(1)
    g = infile.read(1)

    print(ord(r))
    
    r = max(0, min(255, ord(r)))

    ofile[625-index-1] = bytearray([r, 0, 0, 0])

    # outfile.write(bytearray([r, 0, 0, 0]))
    
    # if (r == ff_ba and b == ff_ba and g == ff_ba):
    #     line.append(" ")
    #     print("RGB",r,b,g)
    # else: 
    #     line.append("*")
    #     print("RGB",r,b,g)
    index = index + 1
    # if (index % 25 == 0):
    #     all_lines.append(line)
    #     line = []

for of in ofile:
    outfile.write(of)

## Close input and output files
infile.close()
outfile.close()    
