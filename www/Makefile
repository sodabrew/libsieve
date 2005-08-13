# Makefile for use with C Preprocessor as a HTML Template Engine

.PHONY: all common

ENGINE = gcc -E -x c -P -C 

all: functions.php structures.php

common: template.txt code.css

functions.php: functions.txt common
structures.php: structures.txt common

%.php: %.txt
	$(ENGINE) $< > $@

upload: Makefile code.css common.php example.php functions.php index.php license.php \
	script1.php script2.php script3.php structures.php tweedy.tpl
	scp $^ sodabrew@groups.sf.net:/home/groups/l/li/libsieve/htdocs/

