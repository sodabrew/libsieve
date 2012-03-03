#!/bin/bash

set -e

PACKAGE="libsieve"
VERSION=$(sed -ne '/AC_INIT/s/^AC_INIT(.*\[\(.*\)\])/\1/p' configure.ac)
DIRS="src m4"
FILES="AUTHORS COPYING NEWS README Makefile.am configure.ac libsieve.pc.in"

echo
echo "->Making release for version: " ${VERSION}
mkdir ${PACKAGE}-${VERSION}
echo
echo "->Copying all files to directory: " ${PACKAGE}-${VERSION}
cp -pr ${DIRS} ${FILES} ${PACKAGE}-${VERSION}
echo
echo "->Changing to directory: " ${PACKAGE}-${VERSION}
cd ${PACKAGE}-${VERSION}/ 
echo
echo "->Bootstrapping autotools: "
autoreconf -f -i
echo
echo "->Removing autotools cache: "
rm -fr autom4te.cache
echo
echo "->Generating flex and bison: "
cd src/sv_parser
for i in $(ls *.l); do flex $i; done
for i in $(ls *.y); do bison -d $i; done
echo
echo "->Returning from directory: " ${PACKAGE}-${VERSION}
cd ../../..
echo
echo "->Making compressed tar file " ${PACKAGE}-${VERSION}.tar.gz
tar cf - ${PACKAGE}-${VERSION} | gzip > ${PACKAGE}-${VERSION}.tar.gz
echo
echo "->Removing temporary directory: " ${PACKAGE}-${VERSION}
rm -rf ${PACKAGE}-${VERSION}
echo
