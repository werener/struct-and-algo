#!/bin/bash

FOUND_FILE=$(find $(dirname "$0") -maxdepth 2 -type f -name "main.cpp" -print -quit)

if [[ -n "$FOUND_FILE" ]]
then
    g++ -o build/main "$FOUND_FILE" 
    chmod u+x $FOUND_FILE
    ./build/main
else
    echo "No main.cpp" 
    exit 1
fi
