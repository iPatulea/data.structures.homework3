/*Patulea Ionut
313CA*/


#include "hash.h"
#include<iostream>
#include<string.h>

int hash_fct(char *str)
{
        unsigned int hash = 5381;
        int c;
 
        while ( (c = *str ++) != 0 ) {
                hash = ((hash << 5) + hash) + c;
        }
 
        return hash;
}


int main() {

Hashtable<char*,char*> hci(hash_fct);
char sir[10000],*p,sep[]=" \n",*site,sep2[]="\n";
int sem=0,sem2=0,sem3=0;
//fprintf(stdout,"^-^\n");
fgets(sir,10000,stdin);
while(1)
{
	if(strlen(sir)<=4)
		break;
	p=strtok(sir,sep);
	if (strcmp(p,"PUT")==0){
		site=strtok(NULL,sep);
		for(p=strtok(NULL,sep);p;p=strtok(NULL,sep))
			hci.put(p,site);
		fgets(sir,10000,stdin);
		continue;
	}
	if (strcmp(p,"GET")==0){
		p=strtok(NULL,sep2);
 		hci.get(p);
		fgets(sir,10000,stdin);
		continue;
	}
	if (strcmp(p,"SITE")==0){
		site=strtok(NULL,sep);
		p=strtok(NULL,sep2);
		hci.site(p,site);
		fgets(sir,10000,stdin);
		continue;
	}
}
return 0;
}
