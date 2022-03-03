#!/bin/bash
if [ "$#" -ne 1 ]
then
echo "Invalid input data: enter the name of only one file"
else
find "$1" -maxdepth 1 -type d | sed '1d' | while read x; do
FDIR=$(find "$x" -type d | sed '1d' | wc -l)
if [ $FDIR -ne 0 ]; then
echo "$x" | cut -d '/' -f2
fi
done
fi
