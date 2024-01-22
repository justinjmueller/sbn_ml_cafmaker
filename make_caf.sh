#!/bin/bash

if [ ! "$#" -ge 1 ]; then
    echo "Usage: ./make_caf.sh [input_files]"
fi

offset=0
for i in "$@"
do
    output=`sed 's/.\{3\}$//' <<< "${i}"`.caf.root
    #echo $output
    ./ReadHDF5 $output $offset $i
    ((offset+=1000))
done