#define LIBK5F2
#include "k5f2.h"

#define KONGFIG_MAX_KEYSIZE  512
#define KONGFIG_MAX_VALSIZE  512
#define KONGFIG_POOL_SIZE      8
#define ABSOLUTE_MAX_KEYSIZE 512+KONGFIG_MAX_KEYSIZE

static char pool[KONGFIG_POOL_SIZE][KONGFIG_MAX_VALSIZE+2];
static int pool_index=0;

static char kongfigpath[ABSOLUTE_MAX_KEYSIZE+2];
static char kongfigbase[ABSOLUTE_MAX_KEYSIZE+2];
static char *kongpath(char *a,char *k)
{
	int cc;
	char *h,*base,d[ABSOLUTE_MAX_KEYSIZE+2],*s;
	if ( !a ) a="";
	h=getenv("KONGFIG");
	verbose("KONGFIG=%s",h?h:"");
	if ( h ) {
		base=h;
	} else {
	    h=getenv("HOME");
	    if ( ! h ) h="./";
	    snprintf(kongfigbase,ABSOLUTE_MAX_KEYSIZE,"%s/.kongfig",h);
	    base=kongfigbase;
	}
	if ( ! a ) {
		error("invalid null app");
		return(NULL);
	}
	if ( ! k ) {
		error("invalid key");
		return(NULL);
	}
	if ( strlen(k)>= KONGFIG_MAX_KEYSIZE ) {
		error("invalid key size %60.60s...",k);
		return(NULL);
	}
	verbose("directory %s",base);
	mkdir(base,0755);
	/////////////////////////////////////////////////////////
	s="/";
	if ( strlen(a)==0 ) s="";
	cc=snprintf(d,ABSOLUTE_MAX_KEYSIZE,"%s%s%s",base,s,a);
	verbose("directory %s",d);
	if ( cc < ABSOLUTE_MAX_KEYSIZE ) mkdir(d,0755);
	/////////////////////////////////////////////////////////
	cc=snprintf(kongfigpath,ABSOLUTE_MAX_KEYSIZE,"%s%s%s/%s",base,s,a,k);
	if ( cc >= ABSOLUTE_MAX_KEYSIZE ) {
		error("overrun in %s for %60.60s...",__FUNCTION__,k);
		return(NULL);
	}
	if ( cc < 0 ) {
		error("Unknown Error in %s",__FUNCTION__);
		return(NULL);
	}
	verbose("kongfig path = %s",kongfigpath);
	return(kongfigpath);
}

char *get_kongfig(char *app,char *key)
{
	int cc;
	char *k, *v; // v[ABSOLUTE_MAX_KEYSIZE+2];

	k = kongpath(app,key);
	verbose("k=%s",k?k:"null");
	if ( !k ) return(NULL);
	
	v=&pool[pool_index++][0];
	pool_index%=KONGFIG_POOL_SIZE;
	bzero(v,KONGFIG_MAX_VALSIZE+2);
	cc = readlink(k,v,KONGFIG_MAX_VALSIZE);
	verbose("readlink(%s)->%d errno=%d %s",k,cc,errno,strerror(errno));
	if ( cc < 0 ) {
		return(NULL);
	}
	if ( cc >= KONGFIG_MAX_VALSIZE ) {
		error("Value is too large for %s",k);
		return(NULL);
	}
	return(v);
}

char *set_kongfig(char *app,char *key,char *value)
{
	int cc;
	char *h;
	h = kongpath(app,key);
	if ( ! h ) return(NULL);
	if ( ! value ) {
		error("Invalid value for %s.%s",app,key);
		return(NULL);
	}
	cc = symlink(value,h);
	if ( cc == 0 ) {
		verbose("kongfig: %s = %s",key,value);
		return( get_kongfig(app,key) );
	}
    
	if ( errno == EEXIST || errno == ELOOP ) {
		remove(h);
	        cc = symlink(value,h);
	        if ( cc == 0 ) {
		        verbose("kongfig: %s = %s",key,value);
		        return( get_kongfig(app,key) );
		}
	}
    
	syserror("Cannot link %s --> %s",h,value);
	return(NULL);
}



