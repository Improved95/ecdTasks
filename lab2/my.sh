#!/bin/bash

opta=("" "-O0")
for ((opti = 0; opti < 2; opti++)) do
    echo -e "\n${opta[opti]}" >> res.txt
    g++ ${opta[opti]} main.cpp -o a.out
    for n in 150000 165000 180000 190000; do 
        echo ${n} >> res.txt
        for ((j = 0; j < 3; j++)) do
            (time ./a.out ${n}) &>> res.txt
        done
    done
done
