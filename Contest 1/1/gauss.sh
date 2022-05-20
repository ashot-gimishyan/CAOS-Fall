
'''Реализуйте программу для командного интерпретатора bash, которая вычисляет вещественные корни системы линейных алгебраических уравнений методом Гаусса.

Единственным аргументом скрипта является csv-файл c матрицей (N,N+1) вида:

2,1,-1,8
-3,-1,2,-11
-2,1,2,-3
Скрипт должен вычислить значения и вывести их в тектовом виде на экран в виде строк со значениями:

2.00000000000000000000
3.00000000000000000000
-1.00000000000000000000
В скрипте допускается использовать только команды ввода-вывода и утилиту bc (для вещественнозначных вычислений).

Использовать вызов интерпретаторов высокоуровневых языков (Perl, Python и пр.) запрещено.'''

#! /bin/bash

read -r line < $1
N=$(echo $line | sed  's/[^,]//g')
N=${#N}

declare -A matrix
declare -a res

read_matrix() {
    local i=0
    local line
    local j
    while read -r line; do
        j=0
        IFS=,
        for v in $(echo "$line")
        do
            matrix[$i,$j]="$v"
            j=$((j+1))
        done
        i=$((i+1))
    done
}

read_matrix < $1

for ((j=0;j<N-1;j++)) do
    for ((i=j+1;i<N;i++)) do
        temp=`bc <<< "scale=20; ${matrix[$i,$j]}/${matrix[$j,$j]}"`
        for ((k=0;k<N+1;k++)) do
          mult=`bc <<< "scale=20; ${matrix[$j,$k]}*$temp"`
          matrix[$i,$k]=`bc <<< "scale=20; ${matrix[$i,$k]} - $mult"`
        done
    done
done

for ((i=N-1;i>=0;i--)) do
  s=0
  for ((j=i+1;j<N;j++)) do
    s=`bc <<< "scale=20; $s + ${matrix[$i,$j]}*${res[$j]}"`
  done
   diff=`bc <<< "scale=20; ${matrix[$i,$N]} - $s"`
   res[$i]=`bc <<< "scale=20; $diff/${matrix[$i,$i]}"`
done

for ((i=0;i<N;i++)) do
  echo ${res[$i]}
done
