#!/bin/bash
i1=4
j1=4
st=150000
add=15000

n=${st}
echo -e "without" >> res.txt
g++ main.cpp
for ((i = 0; i < ${i1}; i++))
do
    echo "n = ${n}" >> res.txt;
    for ((j = 0; j < ${j1}; j++)) 
    do
        (time ./a.out ${n}) &>> res.txt
    done
    n=$(( $n + $add ))
    echo "---" >> res.txt;
done

n=${st}
echo -e "\nO0" >> res.txt
g++ -O0 main.cpp 
for ((i = 0; i < ${i1}; i++))
do
    echo "n = ${n}" >> res.txt;
    for ((j = 0; j < ${j1}; j++)) 
    do
        (time ./a.out ${n}) &>> res.txt
    done
    n=$(( $n + $add ))
    echo "---" >> res.txt;
done

st=2000000
add=400000
n=${st}
echo -e "\nO1" >> res.txt
g++ -O1 main.cpp 
for ((i = 0; i < ${i1}; i++))
do
    echo "n = ${n}" >> res.txt;
    for ((j = 0; j < ${j1}; j++)) 
    do
        (time ./a.out ${n}) &>> res.txt
    done
    n=$(( $n + $add ))
    echo "---" >> res.txt;
done

n=${st}
echo -e "\nO2" >> res.txt
g++ -O2 main.cpp 
for ((i = 0; i < ${i1}; i++))
do
    echo "n = ${n}" >> res.txt;
    for ((j = 0; j < ${j1}; j++)) 
    do
        (time ./a.out ${n}) &>> res.txt
    done
    n=$(( $n + $add ))
    echo "---" >> res.txt;
done

n=${st}
echo -e "\nO3" >> res.txt
g++ -O4 main.cpp 
for ((i = 0; i < ${i1}; i++))
do
    echo "n = ${n}" >> res.txt;
    for ((j = 0; j < ${j1}; j++)) 
    do
        (time ./a.out ${n}) &>> res.txt
    done
    n=$(( $n + $add ))
    echo "---" >> res.txt;
done

n=${st}
echo -e "\nOs" >> res.txt
g++ -Os main.cpp 
for ((i = 0; i < ${i1}; i++))
do
    echo "n = ${n}" >> res.txt;
    for ((j = 0; j < ${j1}; j++)) 
    do
        (time ./a.out ${n}) &>> res.txt
    done
    n=$(( $n + $add ))
    echo "---" >> res.txt;
done

st=1844674407370955161
add=1000000000000000
n=${st}
echo -e "\nOfast" >> res.txt
g++ -Ofast main.cpp 
for ((i = 0; i < ${i1}; i++))
do
    echo "n = ${n}" >> res.txt;
    for ((j = 0; j < ${j1}; j++)) 
    do
        (time ./a.out ${n}) &>> res.txt
    done
    n=$(( $n + $add ))
    echo "---" >> res.txt;
done

st=2000000
add=400000
n=${st}
echo -e "\nOg" >> res.txt
g++ -Og main.cpp 
for ((i = 0; i < ${i1}; i++))
do
    echo "n = ${n}" >> res.txt;
    for ((j = 0; j < ${j1}; j++)) 
    do
        (time ./a.out ${n}) &>> res.txt
    done
    n=$(( $n + $add ))
    echo "---" >> res.txt;
done
