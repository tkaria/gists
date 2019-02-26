from __future__ import print_function
from itertools import islice
import time
import csv
def gen_csv1(input_file, chunk_size=50):
    try:
        with open(input_file) as in_file:
            csv_reader = csv.reader(in_file)
            while True:
                yield islice(csv_reader, chunk_size)
    except StopIteration:
        pass

# gen1 = gen_csv1('./test100.csv')

# for chunk in gen1:
#     print(list(chunk))
#     x = list(chunk)
#     print(len(x))
#     time.sleep(1)

def gen_csv3(input_file, num_lines=50):
    try:
        with open(input_file) as in_file:
            csv_reader = csv.reader(in_file)
            while True:
                yield islice(next(csv_reader), num_lines)
    except StopIteration:
        pass

gen3 = gen_csv3('./test100.csv')
for chunk in gen3:
    rows = list(chunk)
    print(rows)
    time.sleep(1)



def gen_csv2(input_file, num_lines=50):
    """
    This is the good one
    """
    try:
        with open(input_file) as in_file:
            csv_reader = csv.reader(in_file)
            block = list(islice(csv_reader, num_lines))
            while block:
                yield block
                block = list(islice(csv_reader, num_lines))
    except StopIteration:
        pass

# gen2 = gen_csv2('./test100.csv')
# for chunk in gen2:
#     rows = list(chunk)
#     for cols in rows:
#         print(cols[0], cols[1])
#     time.sleep(1)

def gen_csv(input_file):
    try: 
        with open(input_file) as in_file:
            csv_reader = csv.reader(in_file)
            while True:
                yield next(csv_reader)
    except StopIteration:
        pass


# gen = gen_csv('./test100.csv')
# for chunk in gen:
#     rows = islice(gen, 50)
#     print(list(rows))
#     time.sleep(1)
