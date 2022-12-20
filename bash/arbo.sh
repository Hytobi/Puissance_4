#!/bin/bash

# print la structure de l'arborescence
tree --version &> /dev/null 
if [ `cut -d' ' -f1 <<< $?` -eq 0 ] 
then
    tree
else
    echo "gcc is not installed"
    read -p 'Do you want to install tree? (y/n): ' treedl
    [ $treedl == "y" ] && sudo apt install tree && tree
fi

exit 0