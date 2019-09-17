#!/bin/bash

# Simple testing function
# format of "sample.txt"
: '
test case 1

===
test case 2

===
test case 3

===
'
# When line matches "===", the previous lines are fed to program

run_test() {
	cmd="./a.out"
	sample="sample.txt"
	data=""
	echo Run $cmd
	cat $sample | while read line
	do
		if [[ ${line:0:3} = "===" ]]; then
			echo IN
			echo -ne $data
			echo OUT
			echo -ne $data | $cmd
			echo ===
			data=""
		else
			data+="$line\n"
		fi
	done
}
