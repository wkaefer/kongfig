#include "k5f2.h"
#include "libkongfig.h"

void showkong(char *a,char *k)
{
	char *v;
	if ( ! a ) a="";
	v=get_kongfig(a,k);
	verbose("%s%s%s='%s'\n",a,strlen(a)?".":"",k,v?v:"");
	printf("%s\n",v?v:"");
}

void setkong(char *a,char *k,char *v)
{
	char *x;
	if ( ! a ) a="";
	x=set_kongfig(a,k,v);
	//printf("%s%s%s='%s' [%s]\n",a,strlen(a)?".":"",k,v,x?x:"");
	showkong(a,k);
}

int main(int argc, char *argv[])
{
	int o;
	char *n=NULL,*k=NULL,*v=NULL;
	while (( o=getopt(argc,argv,"dn:k:v:")) > 0 ) {
		switch (o) {
			case 'n': n=optarg;break;
			case 'k': k=optarg;break;
			case 'v': v=optarg;break;
			case 'd': set_verbose();break;
			default: 
				printf("kongfig -k <key>                      # Display Key Value\n");
				printf("kongfig -k <key> -v <value>           #     Set Key Value\n");
				printf("kongfig -n <name> -k <key>            # Display Name.Key Value\n");
				printf("kongfig -n <name> -k <key> -v <value> #     Set Name.Key Value\n");
				printf("kongfig -n <name>                     # Display All Name Key/Values\n");
				printf("kongfig                               # Display All Key/Values\n");
				printf("Use -d to increase verbosity\n");
				exit(0);
				break;
		}
	}

	if ( k && v ) setkong(n,k,v);
	else
	if ( k ) showkong(n,k);
	else
	if ( n ) printf("Show all for %s\n",n);
	else
	printf("Show all\n");
	return(0);
}
