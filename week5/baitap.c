#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jrb.h"
#include "fields.h"

typedef struct {
	char *name;
	int phone;
}PhoneEntry;

int compare(Jval j1, Jval j2)
{
  PhoneEntry *p1, *p2;

  p1 = (PhoneEntry *) j1.v;
  p2 = (PhoneEntry *) j2.v;

  if (p1->phone > p2->phone) return 1;
  if (p1->phone < p2->phone) return -1;
  return strcmp(p1->name, p2->name);
}


void modified_phone_numbers(JRB t, int key)
{
	PhoneEntry * p;
	JRB tmp;
	int x = 123456789;
	
	jrb_traverse(tmp, t)
	{
		    p = tmp->key.v;
		    if(p->phone == key){
				
		        jrb_delete_node(tmp);
			    p->phone = x;
			    jrb_insert_gen(t, new_jval_v((void *) p), new_jval_v(NULL), compare);
			    return;
		}

		}
	
}

int main()
{
	IS is;
	PhoneEntry *p;
	JRB t, tmp;
	int i, nsize;
	
	is = new_inputstruct(NULL);
	t = make_jrb();
	
	while (get_line(is)>=0)
	{
		if(is->NF > 1)
		{
			p = malloc(sizeof(PhoneEntry));
			p->phone = atoi(is->fields[is->NF-1]);
			
			nsize = strlen(is->fields[0]);
            for (i = 1; i < is->NF-1; i++) nsize += (strlen(is->fields[i])+1);
            
            p->name = (char *) malloc(sizeof(char)*(nsize+1));
            strcpy(p->name, is->fields[0]);
            
            nsize = strlen(is->fields[0]);
            for (i = 1; i < is->NF-1; i++) 
            {
				
                p->name[nsize] = ' ';
                strcpy(p->name+nsize+1, is->fields[i]);
                nsize += strlen(p->name+nsize);
            }
            
            jrb_insert_gen(t, new_jval_v((void *) p), new_jval_v(NULL), compare);
		}
			
	}
	int key = 298711232;
	modified_phone_numbers(t, key);

	
	jrb_traverse(tmp, t) {
    p = (PhoneEntry *) tmp->key.v;
    printf("%-40s 0%d\n", p->name, p->phone);
    }
    return 0;
}
