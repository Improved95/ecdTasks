#!/bin/bash

opta=("" "-O0" "-O1" "-O2" "-O3" "-Os" "-Ofast" "-Og")
for ((opti = 0; opti < 8; opti++)) do
    echo -e "\n${opta[opti]}" >> time.txt
    g++ ${opta[opti]} main.cpp
    for n in 70000 84500 90000; do 
        echo ${n} >> time.txt
        for ((j = 0; j < 3; j++)) do
            (time ./a.out ${n}) 2>> time.txt 1> garbage.txt
        done
    done
done
