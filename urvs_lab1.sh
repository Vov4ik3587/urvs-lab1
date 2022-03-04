#!/bin/bash

if [ "$#" -ne 1 ]
    then
    echo "Введите один каталог"
fi

if [ ! -d "$1" ]
    then
    echo "Аргумент не каталог"
fi

if [ "$#" -eq 1 ]
    then
    find "$1" -maxdepth 1 -type d | sed '1d' | while read x; do
    
    FDIR=$(find "$x" -type d | sed '1d' | wc -l)
    if [ $FDIR -ne 0 ]
        then
        echo "В каталоге $x есть каталоги"
    fi
    if [ $FDIR -eq 0 ]
        then
        echo "В каталоге $x нет каталогов"
    fi

    done
fi
