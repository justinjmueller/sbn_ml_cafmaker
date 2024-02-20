#!/bin/bash

if [ ! "$#" -le 3 ]; then
    echo "Usage: ./match_files.sh [caf_input_dir] [hdf5_input_dir] [output_file_base]"
fi

count=0
shopt -s nullglob
ALLFILES=($2/*.h5)
LENGTH=${#ALLFILES[@]}
for ((j=0; j<$LENGTH; j++))
do
    i=${ALLFILES[$j]}
    IFS='_' read -r -a array <<< ${i}
    CLUSTERID=${array[-5]}
    JOBID=${array[-4]}
    echo "Processing file with JobID ${JOBID} (${count} / $LENGTH)."
    CAF=${1}/*_${JOBID}/*Var.caf.root
    echo ${CAF} ${i}
    ./merge_sources_simulation ${3}_${JOBID}.caf.root ${CAF} ${i}
    let count+=1
done
