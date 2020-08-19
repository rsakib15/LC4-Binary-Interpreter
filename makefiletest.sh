#!/bin/bash

remove_compiled () {
    rm -f autograder*
    rm -f lc4
    rm -f *.o
}

cd submit

required_files=( "lc4.c" "lc4_disassembler.c" "lc4_disassembler.h" \
                 "lc4_loader.c" "lc4_loader.h" "lc4_memory.c" "lc4_memory.h" "Makefile")

for file in "${required_files[@]}"
do
    if [ ! -f $file ]; then
        echo "Required file ${file} does not exist!"
        exit 1
    fi
done

if [ $1 == "lc4" ]; then
    make lc4

    if [ $? -ne 0 ]; then
        echo "LC4 Makefile failed!"
        remove_compiled
        exit
    fi

    echo "LC4 Makefile successful!"
    remove_compiled
elif [ $1 == "integration" ]; then
    cp ../autograder_test/* .
    make lc4
    make -f autograder_makefile autograder

    if [ $? -ne 0 ]; then
        echo "Integration compilation failed!"
        remove_compiled
        exit
    fi

    echo "Integration successfully compiled!"
    remove_compiled
else
    echo "Invalid or missing argument!"
    echo "Usage:"
    echo "    ./makefiletest.sh <lc4|integration>"
    exit 1
fi
