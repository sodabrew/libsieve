#!/bin/sh

# TODO: Make sure that the results are actually correct, too!

for i in `seq 1 12`; do
        echo "Testing script$i.sv messagea.mbox"
	./example script$i.sv messagea.mbox > /dev/null
	if [ "$?" -ne "0" ]; then
		echo script$i.sv failed!
	fi
        echo "Testing script$i.sv messageb.mbox"
	./example script$i.sv messageb.mbox > /dev/null
	if [ "$?" -ne "0" ]; then
		echo script$i.sv failed!
	fi
done
