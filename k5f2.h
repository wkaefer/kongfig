#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

void error(char *s,...);
void syserror(char *s,...);
void verbose(char *s,...);
int set_verbose();
int endswith(char *s,char c);

#ifdef LIBK5F2 

int endswith(char *p,char c)
{
	if ( ! p ) return(0);
	if ( *p ) {
		while ( *p ) p++;
		p--;
		if ( *p == c ) return(1);
	}
	return(0);
}

static int isverbose=0;

void error(char *s,...)
{
	va_list v;
	va_start(v,s);
	vfprintf(stderr,s,v);
	fprintf(stderr,"\n");
}

void syserror(char *s,...)
{
	va_list v;
	va_start(v,s);
	vfprintf(stderr,s,v);
	fprintf(stderr,", %s\n",strerror(errno));
}

int set_verbose()
{
	isverbose++;
	return(isverbose);
}

void verbose(char *s,...)
{
	va_list v;
	if ( isverbose ) {
		va_start(v,s);
		fprintf(stderr,"#🟩" );
		vfprintf(stderr,s,v);
		fprintf(stderr,"\n");
	}
}
#endif
