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

libkongfig.a: libkongfig.a(libkongfig.o) libkongfig.a(k5f2_impl.o)
kongfigtest: kongfigtest.c
	$(CC) $(CFLAGS) kongfigtest.c $(LDFLAGS) -o $@
clean:; rm -f libkongfig.a kongfigtest *.o tags *.gch

ctags:
	ctags *.c

install: install-man
	@mkdir -p "${PREFIX}/bin"
	@cp -v kongfig "${PREFIX}/bin/"

install-man:
	@mkdir -p "${MANPREFIX}/man1"
	@cp -v kongfig.1 "${MANPREFIX}/man1/"

test:
	rm -rf tmp
	mkdir -p tmp
	KONGFIG=tmp make flintstones
	KONGFIG=tmp ./kongfigtest
	KONGFIG=tmp ./kongfigtest -k name -v 'Fredrick'
	KONGFIG=tmp ./kongfigtest -k name 
	KONGFIG=tmp ./kongfigtest -k name -v 'Fred'
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


# 🐳 ── Docker ──────────────────────────────────────────────

#
# docker-build - Build the kongfig Docker image
# ----------------------------------------------
docker-build:
	docker build -t kongfig .

#
# docker-run - Start kongfig container in the background
# ------------------------------------------------------
docker-run: docker-build
	docker run -d --name kongfig \
		-v "$$HOME/.kongfig:/root/.kongfig" \
		kongfig tail -f /dev/null
	@echo "🐳 Container 'kongfig' is running"

#
# docker-exec - Open a shell in the running container
# ----------------------------------------------------
docker-exec:
	docker exec -it kongfig bash

#
# docker-stop - Stop and remove the kongfig container
# ----------------------------------------------------
docker-stop:
	docker stop kongfig
	docker rm kongfig
	docker rmi kongfig
	@echo "🐳 Container and image removed"

#
# docker-demo - Round-trip demo: persist config across containers
# ----------------------------------------------------------------
docker-demo: docker-build
	rm -fv ~/.kongfig/bestfriend
	-docker stop kongfig 2>/dev/null
	-docker rm kongfig 2>/dev/null
	docker run -d --name kongfig \
		-v "$$HOME/.kongfig:/root/.kongfig" \
		kongfig tail -f /dev/null
	docker exec kongfig kongfig bestfriend Barney
	docker stop kongfig
	docker rm kongfig
	docker rmi kongfig
	@echo "🐳 Container and image removed. Config survives:"
	@ls -l ~/.kongfig/bestfriend


# 🌵🌵🌵🌵🌵🌵🌵🌵🌵🌵🌵🌵🌵🌵🌵🌵 jwk 🌵🌵🌵🌵🌵🌵🌵🌵🌵🌵🌵🌵🌵🌵🌵🌵
# Configure git remotes after fresh clone

#
# jwk - Add github remote for snapshot pushes
# -------------------------------------------
jwk:
	git remote add github git@github.com:wkaefer/kongfig.git

#
# github-push - Force-push a flat snapshot to github:main
# -------------------------------------------------------
github-push:
	-git branch -D github-staging 2>/dev/null
	git checkout --orphan github-staging
	git commit -m "Snapshot: $$(date +%Y-%m-%d)"
	git push --force github github-staging:main
	git checkout main
	git branch -D github-staging

# vim: set ft=make ts=8 sw=8 noet :
