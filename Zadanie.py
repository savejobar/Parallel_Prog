import os

filename = "random_1GB.bin"
size = 1 * 1024 * 1024 * 1024
chunk_size = 100 * 1024  * 1024

with open(filename, "wb") as f:
    for i in range(size // chunk_size):
        f.write(os.urandom(chunk_size))
    remaining = size % chunk_size
    if remaining:
        f.write(os.urandom(remaining))