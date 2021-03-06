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

export cmd="./a.out"
export sample="sample.txt"
run_test() {
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
