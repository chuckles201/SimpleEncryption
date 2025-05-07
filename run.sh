#!/bin/bash

clang tests.c -o tests_run
if [ $? -eq 0 ]; then
    echo "run.sh --> Compiled, running program"
    ./tests_run
else
    echo "run.sh --> Compile failed"

fi
