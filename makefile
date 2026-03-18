MAKEFLAGS=--no-print-directory
CFLAGS:= -g -I.
CC=cc
AR=ar
EC=echo $@
ARFLAGS=rU
LDFLAGS:= -g -L. -lkongfig
PREFIX:= ${HOME}/bin
.SUFFIXES: .gch .h.gch
.h.h.gch:
	$(CC) $(CFLAGS) -c $< -o $@

all:	k5f2.h.gch
	+make libkongfig.a
	+make kongfig

libkongfig.a: libkongfig.a(libkongfig.o)
kongfig: kongfig.c
	$(CC) $(CFLAGS) kongfig.c $(LDFLAGS) -o $@
clean:; rm -f libkongfig.a kongfig *.o tags *.gch

ctags:
	ctags *.c

install:
	cp kongfig ${PREFIX}/
	

test:
	rm -rf tmp
	mkdir -p tmp
	KONGFIG=tmp ./kongfig 
	KONGFIG=tmp ./kongfig -k name -v 'Fred'
	KONGFIG=tmp ./kongfig -k name 
	KONGFIG=tmp ./kongfig -k name -v 'Sam'
	KONGFIG=tmp ./kongfig -k name 
	@find tmp/ -ls
	@rm -rf tmp

flintstones:
	kongfig -k name -v 'Fred Flintstone'
	kongfig -k wife -v 'Wilma'
	kongfig -k children -v 1
	kongfig -n child1 -k name -v Pebbles
	kongfig -k city -v Bedrock
	find ~/.kongfig -ls


#/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/**--__
#      ____ ___ _____      __   ____ ___ _____ _   _ _   _ ____  
#     / ___|_ _|_   _|    / /  / ___|_ _|_   _| | | | | | | __ ) 
#    | |  _ | |  | |     / /  | |  _ | |  | | | |_| | | | |  _ \ 
#    | |_| || |  | |    / /   | |_| || |  | | |  _  | |_| | |_) |
#     \____|___| |_|   /_/     \____|___| |_| |_| |_|\___/|____/ 
#                                                                

github:
	git push github main
	
__reset::
	rm -rf .git
	git init
	git remote add origin git@shazam:/srv/git/kongfig
	git remote add github https://www.github.com/${GITHUB_NAME}/kongfig.git 
	git remote set-url github git@github.com:${GITHUB_NAME}/kongfig.git

reset: __reset
	git fetch 
	git checkout origin/main -ft
	git config pull.rebase false
	git status

__reset_git_repo__: __reset
	ssh git@localhost rm -rf /srv/git/kongfig.git
	ssh git@localhost mkdir /srv/git/kongfig.git
	ssh git@localhost git -C /srv/git/kongfig.git init --bare --initial-branch=main
	git add .
	git commit -m "Initial commit"
	git push -u origin main

# vim: set ft=make ts=8 sw=8 noet :
