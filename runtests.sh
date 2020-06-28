#!/bin/bash
# runs all the tests

make

for D in Tests/*; do
    if [ -d "${D}" ]; then
        for s in $D/*; do
            echo $s
            ./emu -E $D.s < $s > out
        done
    fi
done
