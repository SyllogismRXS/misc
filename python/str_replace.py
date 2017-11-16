#!/usr/bin/env python

import os
import glob
import fileinput

root_dir = os.path.expanduser('~/scrimmage/gtri-tactics')
src_dir = root_dir + '/src'
include_dir = root_dir + '/include'

for root, dirs, files in os.walk(src_dir):
    for file in files:
        if file.endswith(".cpp"):
            #print(os.path.join(root, file))
            file_path = os.path.join(root, file)
            stem = os.path.splitext(file)[0]

            dirs = os.path.dirname(file_path).split('/')
            prefix = dirs[len(dirs)-2] + '/' + dirs[len(dirs)-1]

            old_str = '#include "' + stem + '.h"'
            old_str_2 = '#include <gtri-tactics/utilities/stem.h>'
            old_str_3 = '#include <gtri-tactics/utilities/' + stem + '.h>'
            new_str = '#include <gtri-tactics/plugins/' + prefix + '/' + stem  + '.h>'

            print('=======================')
            print(old_str)
            print(old_str_2)
            print(old_str_3)
            print('----')
            print(new_str)

            # Read in the file
            with open(file_path, 'r') as file :
                filedata = file.read()

            # Replace the target string
            filedata = filedata.replace(old_str, new_str)

            filedata = filedata.replace(old_str, new_str)
            filedata = filedata.replace(old_str_2, new_str)
            filedata = filedata.replace(old_str_3, new_str)

            # Write the file out again
            with open(file_path, 'w') as file:
                file.write(filedata)
