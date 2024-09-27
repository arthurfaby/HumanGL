#!/bin/sh

# Run the different commands necessary to build the project

# -S : Provide the location of the SMakeLists.txt file
# -B : Provide the location of the directory in which the build will be done
cmake -S . -B build/;
cd build/;
make;