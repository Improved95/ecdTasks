#!/bin/bash

file=("naive" "vect" "blas")
for ((i = 0; i < 3; i++)) do
    g++ ${file[i]}.cpp -O2 -Wall -Werror -Wextra -march=native -I /home/evm112/ecd/openBLAS_lib -lopenblas
    echo -e "\n${file[i]}" >> time.txt
    for ((j = 0; j < 3; j++)) do
        (time ./a.out) 2>> time.txt 1> garbage.txt
    done
done