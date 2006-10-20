#!/bin/sh

# TODO: Make sure that the results are actually correct, too!

for i in `seq 1 12`; do
	./example script$i.sv messagea.mbox > /dev/null
	if [ "$?" -ne "0" ]; then
		echo script$i.sv failed!
	fi
	./example script$i.sv messageb.mbox > /dev/null
	if [ "$?" -ne "0" ]; then
		echo script$i.sv failed!
	fi
done
