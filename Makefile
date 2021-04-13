
CC=gcc
CFLAGS=-lz -g -Wall -Wextra
MAKEFLAGS += --silent

.PHONY : install
install : genpass
	touch vault.txt
	mv ./genpass /usr/bin
	mv ./vault /usr/bin
	echo " *** Success: genpass installed"

.PHONY : genpass
genpass :
	rm genpass
	chmod +x helper
	ln helper genpass
	chmod +x genpass
	echo " *** Success: genpass built"

.PHONY : remove 
remove : 	
	echo "Forcefully removing vault.txt"
	echo "This action is irreversible"
	echo "Would you like to continue [y / n]: "
	read userChoice
	if [[ userChoice -eq "n" ]]; then
		echo "Exiting..."
	fi 
	echo "Deleting vault.txt"
	rm -rf vault.txt
	touch vault.txt

.PHONY : debug 
debug :
	echo "testing"

		