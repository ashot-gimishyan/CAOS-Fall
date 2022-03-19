#! /bin/bash

# Substitute everything that matches the regular expression : with a space, globally (on the whole input line).
# Символ «|» — это конвейер (pipe). Посредством конвейера вывод одной команды подается на вход другой.
t=$(echo `manpath` | sed 's/:/ /g')

# Find where? what? Поиск папки (-type d) man3
dir=$(find $t -type d -name "man3")
# dir = /usr/share/man/man3

while read func
do
  temp=$(find $dir -name "$func.*")
  # example: for puts temp = /usr/share/man/man3/puts.3.gz

  temp1=$(echo $temp | grep -o gz)
  # example: for puts temp1 = gz

  if [[ $temp1 = "gz" ]]
  then
      # gunzip может распаковывать архивы
      # -c keep original files unchanged.
      x=`gunzip -c "$temp"`

      # delete all before first #include < included
      x=${x#*#include <}

      # delete all after first > included
      x=${x%%>*}
      echo $x
  else
    echo ---
fi
done
