# this is the version number :-)
PACKAGE = libsieve
VERSION = 2.2.0pre1
SOURCES = src
DOCS = html
OTHERS = AUTHORS COPYING NEWS README Makefile

all:
	@echo "This is the top level Makefile, which does two things:"
	@echo
	@echo "1. Makes releases, with the command 'make snapshot'"
	@echo "2. Explains that to actually compile something, do this:"
	@echo "   cd src && ./configure && make"
	@echo
	@echo
	@echo "Please read over the documentation in the top level, too!"
	@echo

# a rule to make snapshots
snapshot: $(SOURCES) $(DOCS) $(OTHERS)
	@echo
	@echo "->Note: The version for now is hacked into Makefile as: " $(VERSION)
	@echo
	@echo "->Copying all release files to the directory: " $(PACKAGE)-$(VERSION)
	@echo
	-mkdir $(PACKAGE)-$(VERSION)
	-cp -pr $(SOURCES) $(DOCS) $(OTHERS) $(PACKAGE)-$(VERSION)
	@echo
	@echo "->Making the compressed tar file " $(PACKAGE)-$(VERSION).tar.gz
	@echo
	-tar cf - $(PACKAGE)-$(VERSION) | gzip > $(PACKAGE)-$(VERSION).tar.gz
	@echo
	@echo "->Removing the temporary directory: " $(PACKAGE)-$(VERSION)
	@echo
	-rm -rf $(PACKAGE)-$(VERSION)
	@echo

