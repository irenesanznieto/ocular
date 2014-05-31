#!/usr/bin/env python

import sys
import os

path = sys.argv[1]
folder=path+'processed'
os.mkdir(folder)

for _file in os.listdir(path):
    if _file.endswith(".txt"):

        infile = path+_file

        outline = _file[3:-4]+'\naverage mean min max\n'
        outfile = path+'processed/'+'values_'+_file[:-3]+'ods'
        out_txt = path+'processed/'+'values_'+_file

        f = file(outfile , 'w')
        f_txt = file(out_txt , 'w')

        count = 0

        with open(infile) as inf:
            for line in inf:

                #AVERAGE RATE:
                result = line.find("average: ")
                if result != -1:
                    outline += line[result + 9: result + 9+4]


                 #MEAN
                result = line.find("mean: ")
                if result != -1:
                    outline += ' ' + line[result + 6: result + 6 + 4]

                #MIN
                result = line.find("min: ")
                if result != -1:
                    outline += ' ' + line[result + 5: result + 5+4]

                #MAX
                result = line.find("max: ")
                if result != -1:
                    outline += ' ' + line[result + 5: result + 5+4]+'\n'



                if count ==2:
                    #print outline
                    f_txt.write(outline)
                    f.write(outline)
                    count=0

                count+=1
