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
    fig, ax = plt.subplots(1, 1, figsize=(1, 1))
    shape_data = list()
    for i in range(size[1]):
        c_data = [data[j + i * size[0]] for j in range(size[0])]
        shape_data.append(c_data)
        print(str(i) + " line is finished.")
    ax.imshow(shape_data, cmap=plt.cm.hot,interpolation='bilinear')
    #plt.scatter(x, y, norm=data)
    plt.show()

if __name__ == "__main__":
    main()
