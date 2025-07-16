#!/bin/bash

set -exu

rm -f headeronly/*

LIBS=$(find src -type f -name "*.h" -printf "%f\n"| sed "s/\.h//")

for files in ${LIBS[@]};
do
    cat "src/$files.h" > "headeronly/$files.h"
    if [ -e src/$files.c ]; then
        echo -e "\n" >> "headeronly/$files.h"
        echo "#ifdef ${files^^}_IMPLEMENTATION" >> "headeronly/$files.h"
        cat "src/$files.c" >> "headeronly/$files.h"
        echo "#endif  // ${files^^}_IMPLEMENTATION" >> "headeronly/$files.h"
    fi
done

