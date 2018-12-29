#!/bin/bash
wd="$(pwd)"
gcc -o myGrepCommand.exe ./regularExpressions.c 
if test $? -eq 0
then
	if test $# -eq 2
	then
		${wd}/myGrepCommand.exe $1 $wd $2
	elif test $# -eq 3
	then
		${wd}/myGrepCommand.exe $1 $2 $wd $3
	else
		echo -e " Invalid Usage"
		echo -e " Usage: [programName] [pattern] [fileName]"
		echo -e " As of now this program can only search for one pattern at a time and the file must be present in the same directory as that of the the program."
	fi
fi
