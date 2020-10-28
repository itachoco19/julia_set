import matplotlib.pyplot as plt
import numpy as np
import sys
import struct

def main():
    fd = open("result.dat", "br")
    endian = '<'
    if sys.byteorder == "big":
        endian = '>'
    size = struct.unpack_from(endian + "ii", fd.read(), 0)
    fd.seek(0)
    data = struct.unpack_from(endian + ("d" * (size[0] * size[1])), fd.read(), 8)
    for i in range(size[1]):
        for j in range(size[0]):
            x = float(j * 2 - size[0]) / float(min(size[0], size[1]))
            y = float(i * 2 - size[1]) / float(min(size[0], size[1]))
            print(j + i * size[0])
            plt.scatter(x, y, norm=data)
    plt.show()

if __name__ == "__main__":
    main()