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
