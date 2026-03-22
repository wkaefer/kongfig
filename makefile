MAKEFLAGS=--no-print-directory
CFLAGS:= -g -I.
CC=cc
AR=ar
EC=echo $@
ARFLAGS=rU
LDFLAGS:= -g -L. -lkongfig
PREFIX:= ${HOME}/.local
MANPREFIX:= ${PREFIX}/share/man
.SUFFIXES: .gch .h.gch
.h.h.gch:
	$(CC) $(CFLAGS) -c $< -o $@

all:	k5f2.h.gch
	+make libkongfig.a
	+make kongfigtest

libkongfig.a: libkongfig.a(libkongfig.o)
kongfigtest: kongfigtest.c
	$(CC) $(CFLAGS) kongfigtest.c $(LDFLAGS) -o $@
clean:; rm -f libkongfig.a kongfigtest *.o tags *.gch

ctags:
	ctags *.c

install: install-man
	@mkdir -p ${PREFIX}/bin
	@cp kongfig ${PREFIX}/bin/
	@printf "\033[36;1m%42.42s\033[0m\n" ${PREFIX}/bin/kongfig

install-man:
	@mkdir -p ${MANPREFIX}/man1
	@cp kongfig.1 ${MANPREFIX}/man1/
	@printf "\033[36;1m%42.42s\033[0m\n" ${MANPREFIX}/man1/kongfig.1

test:
	rm -rf tmp
	mkdir -p tmp
	KONGFIG=tmp make flintstones
	KONGFIG=tmp ./kongfigtest
	KONGFIG=tmp ./kongfigtest -k name -v 'Fred'
	KONGFIG=tmp ./kongfigtest -k name 
	KONGFIG=tmp ./kongfigtest -k name -v 'Sam'
	KONGFIG=tmp ./kongfigtest -k name 
	KONGFIG=tmp kongfig
	KONGFIG=tmp kongfig league
	@rm -rf tmp

flintstones:
	kongfigtest -k name -v 'Fred Flintstone'
	kongfigtest -k wife -v 'Wilma'
	kongfigtest -k children -v 1
	kongfigtest -n child1 -k name -v Pebbles
	kongfigtest -k city -v Bedrock
	kongfig lodge "Loyal Order of Water Buffaloes"
	kongfig league "Bedrock Bowling League 🎳"


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
