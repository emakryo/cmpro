#!/bin/bash

run_test() {
	cmd="./a.out"
	data=""
	echo Run $cmd
	cat sample.txt | while read line
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
