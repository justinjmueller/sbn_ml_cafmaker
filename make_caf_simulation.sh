#!/bin/bash

if [ ! "$#" -ge 1 ]; then
    echo "Usage: ./make_caf.sh [input_files]"
fi

offset=0
for i in "$@"
do
    output=`sed 's/.\{3\}$//' <<< "${i}"`.caf.root
    ./make_standalone_simulation $output $offset $i
    ((offset+=1000))
done