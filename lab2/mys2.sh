#!/bin/bash

opta=("O1" "O2" "O3" "Os" "Ofast" "Og")
for ((opti = 0; opti < 7; opti++)) do
    echo -e "\n${opta[opti]}" >> res.txt
    g++ -${opta[opti]} main.cpp
    for n in 2000000 2400000 2800000 3200000; do 
        echo ${n} >> res.txt
        for ((j = 0; j < 4; j++)) do
            (time ./a.out ${n}) &>> res.txt
        done
    done
done