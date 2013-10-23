/*Patulea Ionut
313CA*/


#include "list.h"
#include "stdio.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>



template<typename Tkey, typename Tvalue> struct elem_info {
    Tkey key;
    LinkedList<Tvalue> value;
	int size;
};

template<typename Tkey, typename Tvalue> class Hashtable {
	private:
        LinkedList<struct elem_info<Tkey, Tvalue> > *H;
        int HMAX;
		int number;
        int (*hash) (Tkey);

    public:
        Hashtable( int (*h) (Tkey)) {
			HMAX = 10;
            hash = h;
			number = 0;
			H = new LinkedList<struct elem_info<Tkey, Tvalue> > [HMAX]; 
        }        

		~Hashtable() {
			struct Node<struct elem_info<Tkey, Tvalue> > *p;
			struct Node<char *> *paux,*px;
			for (int i = 0; i < HMAX; i++) {
                while (!H[i].isEmpty())
				{
					H[i].removeFirst();
				}
			}
            delete H;
        }
            
        void put(Tkey key, Tvalue value) {
		
            struct Node<struct elem_info<Tkey, Tvalue> > *p;
            struct elem_info<Tkey, Tvalue> info;
			unsigned int sem,hkey;
			struct Node<char *> *po,*px;
			hkey = hash(key);
			hkey%=HMAX;
            p = H[hkey].pfirst;

            while (p != NULL) {

                if ( strcmp(p->info.key, key) == 0 )
                    break;
                    p = p->next;
                }

                if (p != NULL)
				{
					p->info.size++;
					px=p->info.value.pfirst;
					sem=0;
					while(px)
					{
						if(strcmp(px->info,value)>0)
						{
							if (px==p->info.value.pfirst)
							{
								p->info.value.addFirst(strdup(value));
								sem=1;
								break;
							}
							po=new struct Node<char *>;
							po->info=strdup(value);
							po->prev=px->prev;
							po->next=px;
							po->prev->next=po;
							px->prev=po;
							sem=1;
							break;
						}
						if(strcmp(px->info,value)==0)
						{
							sem=1;
							break;
						}
						px=px->next;
					}
					if(sem==0)
						p->info.value.addLast(strdup(value));
				}
                else {
					char* aux;
					number++;
                    info.key = strdup(key);
					info.size = 1;
					aux=strdup(value);
                    info.value.addFirst(aux);
                    H[hkey].addLast(info);
                }
		}
           
        void get(Tkey key) {
            struct Node<struct elem_info<Tkey, Tvalue> > *p;
			struct Node<char *> *po,*px,*py;
			char *cuv,sep[]=" \n";
			LinkedList<char *> P;
			cuv=strtok(key,sep);
			int sem;
            unsigned int hkey = hash(cuv);
			hkey%=HMAX;
            p = H[hkey].pfirst;
			
            while (p != NULL) {
                if (strcmp(p->info.key,cuv)==0) break;
                p = p->next;
            }
			if (p==NULL){
				fprintf(stdout,"SITE_NOT_FOUND\n");
				return;
			}
			px=p->info.value.pfirst;
			while(px)
			{
				P.addLast(strdup(px->info));
				px=px->next;
			}
			for(cuv=strtok(NULL,sep);cuv && P.pfirst;cuv=strtok(NULL,sep))
			{
				
				hkey = hash(cuv);
				hkey%=HMAX;
				p = H[hkey].pfirst;
				if (p==NULL){
					fprintf(stdout,"SITE_NOT_FOUND\n");
					return;
				}
				while (p != NULL) {
					if (strcmp(p->info.key,cuv)==0) break;
					p = p->next;
				}
				if (p==NULL){
					fprintf(stdout,"SITE_NOT_FOUND\n");
					return;
				}
				po=P.pfirst;
				py=p->info.value.pfirst;
				int i=0;
				while(po){
					sem=1;
					if(py==NULL)
					{
						while(po)
						{
							px=po;
							po=po->next;
							if (sem==0)
								continue;
							if (px->prev != NULL)
								px->prev->next = px->next;
							if (px->next != NULL)
								px->next->prev = px->prev;
							if (px->prev == NULL) // px == pfirst
								P.pfirst = px->next;
							if (px->next == NULL) // px == plast
								P.plast = px->prev;
							delete px;
							if (P.pfirst==NULL)
							{
								fprintf(stdout,"SITE_NOT_FOUND\n");
								return;
							}
						}
						break;
					}
					while(py)
					{
						if(strcmp(po->info,py->info)==0)
						{
							sem=0;
							py=py->next;
							i++;
							break;
						}
						if(strcmp(po->info,py->info)<0)
						{
							break;
						}
						py=py->next;
					}
					px=po;
					po=po->next;
					if (sem==0)
						continue;
					if (px->prev != NULL)
						px->prev->next = px->next;
					if (px->next != NULL)
						px->next->prev = px->prev;
					if (px->prev == NULL) // px == pfirst
						P.pfirst = px->next;
					if (px->next == NULL) // px == plast
						P.plast = px->prev;
					delete px;
					if (P.pfirst==NULL)
					{
						fprintf(stdout,"SITE_NOT_FOUND\n");
						return;
					}
				}
			}
			if (P.pfirst==NULL)
			{
				fprintf(stdout,"SITE_NOT_FOUND\n");
				return;
			}
			po=P.pfirst;
			while(po)
			{
				fprintf(stdout,"%s ",po->info);
				po=po->next;
			}
			fprintf(stdout,"\n");
        }
       
        void site(Tkey key,Tvalue value) {
            struct Node<struct elem_info<Tkey, Tvalue> > *p;
			int sem;
			struct Node<char *> *px;
			char *cuv,sep[]=" \n";
			for(cuv=strtok(key,sep);cuv;cuv=strtok(NULL,sep))
			{
				unsigned int hkey = hash(cuv);
				hkey%=HMAX;
				p = H[hkey].pfirst;
				
				while (p != NULL) {
					if (strcmp(p->info.key,cuv)==0) break;
					p = p->next;
				}
				sem=0;
				if(p==NULL)
				{
					fprintf(stdout,"WORD_NOT_FOUND\n");
					return;
				}
				px=p->info.value.pfirst;
				while(px)
				{
					if(strcmp(value,px->info)<0)
						break;
					if (strcmp(value,px->info)==0)
					{
						sem=1;
						break;
					}
					px=px->next;
				}
				if (sem==0)
				{
					fprintf(stdout,"WORD_NOT_FOUND\n");
					return;
				}
			}
			fprintf(stdout,"WORD_FOUND\n");	
		}
};
