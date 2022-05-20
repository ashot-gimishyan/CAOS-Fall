
'''Problem inf-I-01-0: shell_automation/sh/find_c_includes
Реализуйте скрипт для командного интерпретатора bash, который выполняет поиск имен #include-файлов для заданных имен Си-функций, используя в качестве источника данных третий раздел man-страниц Linux.

Исходные данные располагаются в одном из каталогов, перечисленных в переменной окружения MANPATH, внутри которых располагается каталог man3.

Файлы могут быть как сжатыми утилитой gz, так и распакованными.

Список функций задается на стандартном потоке ввода:

fopen
malloc
unknown_function
strcmp
Если описание функции не найдено, то записывается прочерк из трех дефисов: ---.

Результат необходимо записать в стандартный поток вывода:

stdio.h
stdlib.h
---
string.h
В скрипте допускается использовать только команды ввода-вывода и утилиты sed и gunzip.

Использовать вызов интерпретаторов высокоуровневых языков (Perl, Python и пр.) запрещено.'''

#! /bin/bash
t=$(echo $MANPATH | sed 's/:/ /g') # or `manpath`
dir=$(find $t -type d -name "man3")
while read func
do
  temp=$(find $dir -name "$func.*")
  temp1=$(echo $temp | grep -o gz)
  if [[ $temp1 = "gz" ]]
  then
      x=`gunzip -c "$temp"`
      x=${x#*#include <}
      x=${x%%>*}
      echo $x
  else
    echo ---
fi
done

#by Ashot Gimishyan
