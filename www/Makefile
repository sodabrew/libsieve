# Makefile for use with C Preprocessor as a HTML Template Engine

.PHONY: all common

ENGINE = gcc -E -x c -P -C 

all: functions.php structures.php

common: template.txt code.css

functions.php: functions.txt common
structures.php: structures.txt common

%.php: %.txt
	$(ENGINE) $< > $@

