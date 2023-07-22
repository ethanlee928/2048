#!/bin/bash

if [[ $# -eq 0 || "$1" != "--docker" ]]; then
    echo Starting 2048 locally ...
    gcc -o 2048 2048.c && ./2048
else
    echo Starting 2048 using gcc docker image ...
    docker run --rm -it -v "$(pwd)/2048.c":/usr/src/2048.c \
        -w /usr/src/ gcc:latest \
        sh -c "gcc -o /bin/2048 2048.c && /bin/2048"
fi
