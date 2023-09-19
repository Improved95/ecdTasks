#!/bin/bash
iter=5

echo -e "without" >> res.txt
g++ main.cpp
for ((i = 0; i < ${iter}; i++))
do
    (time ./a.out) &>> res.txt 
done

echo -e "\nO0" >> res.txt
g++ -O0 main.cpp
for ((i = 0; i < ${iter}; i++))
do
    (time ./a.out) &>> res.txt
done

echo -e "\nO1" >> res.txt
g++ -O1 main.cpp
for ((i = 0; i < ${iter}; i++))
do
    (time ./a.out) &>> res.txt
done

echo -e "\nO2" >> res.txt
g++ -O2 main.cpp
for ((i = 0; i < ${iter}; i++))
do
    (time ./a.out) &>> res.txt
done

echo -e "\nO3" >> res.txt
g++ -O3 main.cpp
for ((i = 0; i < ${iter}; i++))
do
    (time ./a.out) &>> res.txt
done

echo -e "\nOs" >> res.txt
g++ -Os main.cpp
for ((i = 0; i < ${iter}; i++))
do
    (time ./a.out) &>> res.txt
done

echo -e "\nOfast" >> res.txt
g++ -Ofast main.cpp
for ((i = 0; i < ${iter}; i++))
do
    (time ./a.out) &>> res.txt
done

echo -e "\nOg" >> res.txt
g++ -Og main.cpp
for ((i = 0; i < ${iter}; i++))
do
    (time ./a.out) &>> res.txt
done