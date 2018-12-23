#!/bin/bash
if test $# -eq 2
then
	wd="$(pwd)"
	gcc -o myGrepCommand.exe ./regularExpressions.c
	if test $? -eq 0 
	then
		${wd}/myGrepCommand.exe $1 $wd $2
	else 
		echo " There was an error in the C program."
	fi
else 
	echo -e " Invalid Usage"
	echo -e " Usage: [programName] [pattern] [fileName]"
	echo -e " As of now this program can only search for one pattern at a time and the file must be present in the same directory as that of the the program."
fi
