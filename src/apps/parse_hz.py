#!/usr/bin/env python

import sys
import os

path = sys.argv[1]
folder = path + 'processed'
os.mkdir(folder)
onetime = 0

for _file in os.listdir(path):


    if _file.endswith(".txt"):

        infile = path + _file
#        if onetime == 0:
 #           outline = _file[3:-4] + '\naverage_rate min max std_dev\n'
  #      else:
        outline = ' '

    #    onetime += 1

        outfile = path + 'processed/' + 'values_' + _file[:-3] + 'ods'
        out_txt = path + 'processed/' + 'backup_values_' + _file

    f = file(outfile, 'w')
    f_txt = file(out_txt, 'w')

    count = 0

    with open(infile) as inf:
        for line in inf:

            #AVERAGE RATE:
            result = line.find("average rate: ")
            if result != -1:
                outline += line[result + 14: result + 14 + 5]

            #MIN
            result = line.find("min: ")
            if result != -1:
                outline += ' ' + line[result + 5: result + 10]

            #MAX
            result = line.find("max: ")
            if result != -1:
                outline += ' ' + line[result + 5: result + 10]

            #STD DEV
            result = line.find("std dev: ")
            if result != -1:
                outline += ' ' + line[result + 5 + 4: result + 12 + 4] + '\n'

            if count == 2:
                #print outline
                f_txt.write(outline)
                f.write(outline)
                count = 0

            count += 1

onetime = 0

