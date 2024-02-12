#!/bin/bash

targets="(all|run_benchmark|run_tests|generate|tdoku|grid_lib|generate_simple)"
if [[ "${1}" =~ ${targets} ]]; then
    target=${1}
    shift
fi

mkdir -p build
(
    cd build
    rm -f CMakeCache.txt
    rm -rf CMakeFiles
    cmake .. $*
    make ${target}
)
