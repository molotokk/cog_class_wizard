#!/usr/bin/env python

import glob
import os
from cogapp import Cog

input_files = glob.glob('./*.yml')
# print(input_files)
if len(input_files) > 0:
    cog_gen = Cog()

    for file in input_files:
        print ("Reading configuration from %s" % file)
        # Retrieve the file name without extension
        config_string = 'CONFIG_FILE=' + os.path.basename(file)
        fname_wo_ext = os.path.splitext(os.path.basename(file))[0]
        cpp_file = fname_wo_ext + '.cpp'
        h_file = fname_wo_ext + '.h'

        print ('  Generating ' + cpp_file)
        args = ['', '-o', cpp_file, '-D', config_string, '-d', '-z', '../templates/CppFile.cog']
        #print args
        cog_gen.callableMain(args)

        print ('  Generating ' + h_file)
        args = ['', '-o', h_file, '-D', config_string, '-d', '-z', '../templates/HFile.cog']
        #print args
        cog_gen.callableMain(args)

    print('done.')


