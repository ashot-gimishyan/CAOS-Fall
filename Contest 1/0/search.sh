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
