#!/bin/sh

for i in `seq 1 12`; do
	./example script$i.sv > /dev/null
	if [ "$?" -ne "0" ]; then
		echo script$i.sv failed!
	fi
done
