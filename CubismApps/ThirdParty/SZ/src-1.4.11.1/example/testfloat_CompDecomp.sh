#!/bin/bash

if [[ $# < 1 ]]
then
	echo Usage: $0 [error bound]
	echo Example: $0 1E-4
	exit
fi

dataDir="/home/fti/SZ_C_version/CESM-testdata/1800x3600"
absErrBound=$1

targetDir="$dataDir"
fileList=`cd "$targetDir";ls *.dat`
dimSizes="3600 1800" 
for file in $fileList
do
        echo testfloat_CompDecomp sz.config zc.config "sz($absErrBound)" "$file" $absErrBound "$targetDir/$file" $dimSizes
        ./testfloat_CompDecomp sz.config zc.config "sz($absErrBound)" "$file" $absErrBound "$targetDir/$file" $dimSizes
done

echo "complete"

