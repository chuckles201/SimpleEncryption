#!/bin/bash

echo "Enter File Name:"
read name
clang $name -o file_run
if [ $? -eq 0 ]; then
    echo "run.sh --> Compiled, running program"
    ./file_run $1 $2 $3 $4 $5 $6
    
else
    echo "run.sh --> Compile failed"

fi
rm file_run