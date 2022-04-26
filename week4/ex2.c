#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct en{
	void *key;
	void *value;
	struct en *left;
	struct en *right;
}Entry;

typedef struct {
	Entry *entries;
	Entry* (*makeNode)(void *, void *);
	int (*compare)(void *, void *);
}SymbolTable;

int comparePhone(void * in1, void* in2) {
	Entry *entry1=(Entry*)in1;
	Entry *entry2=(Entry*)in2;
	int num1 = *( (int*) entry1->key );
	int num2 = *( (int*) entry2->key );

	if (num1==num2) return 0;
	else if (num1 > num2) return 1;
	else return -1;
}

int comparekey(void *in1, void *in2)
{
	int a = *(int*)in1;
	int b = *(int*)in2;
	
	if(a==b)return 0;
	else if(a<b) return -1;
	else return 1;
}
Entry *makePhoneBook(void *phone, void *name)
{
	Entry *res = (Entry*)malloc(sizeof(Entry));
	res->key = malloc(sizeof(int));
	memcpy(res->key, phone, sizeof(int));
	res->value = strdup((char*)name);
	res->left = NULL;
	res->right = NULL;
	return res;
}

SymbolTable createSymbolTable(Entry* (*makeNode)(void*, void*),int (*compare)(void*, void*))
{
    SymbolTable s_table;
    s_table.entries = (Entry*)malloc(sizeof(Entry));
    s_table.entries = NULL;
    s_table.makeNode = makeNode;
    s_table.compare = compare;
    return s_table;
}


Entry *addEntry(Entry *a, Entry *curr,int (*compare)(void *, void *))
{
	if(NULL==curr)
	{
		curr = a;
		return curr;
	}else
	{
		if (compare(a,curr)<=0)
	    curr->left = addEntry(a,curr->left,compare);
		else curr->right = addEntry(a,curr->right,compare);
	}
	return curr;
}

void addBST(void *key, void *value, SymbolTable *book)
{
	Entry *a = makePhoneBook(key, value);
	book->entries = addEntry(a,book->entries,book->compare);
}

void InOrder(Entry *root)
{
	if(root != NULL)
    {
        InOrder(root->left);
        printf("%d %s\n", *((int*)root->key),(char*)root->value);
        InOrder(root->right);
    }
	
}

void search(Entry *root, void *key, int (*compare)(void *, void *))
{
	if (NULL == root)
	{
		printf("Khong tim thay phan tu\n");
		return;
	}else
	{
		if(compare(key,root->key)<0)return search(root->left,key,compare);
		else if(compare(key,root->key)==0)
		{
			printf("Phan tu tim duoc la: %d %s",*((int*)root->key), (char*)root->value);
			return;
		}
		else return search(root->right,key,compare);
	}
	printf("Khong tim thay phan tu\n");
	return;
}

void droptree(Entry *root)
{
	if(root!=NULL)
	{
		droptree(root->left);
		if(root->key!=NULL)
		{
			free(root->key);
			free(root);
		}
		droptree(root->right);
	}
}

int main()
{
	SymbolTable book=createSymbolTable(&makePhoneBook,comparePhone);
	
    int i1=12;
    char c1[]="hello1";

    addBST(&i1,c1,&book);

    int i2=1;
    char c2[]="hello2";
    addBST(&i2,c2,&book);

    int i3=7;
    char c3[]="hello3";
    addBST(&i3,c3,&book);
    
    int i4=6;
    char c4[]="hello4";
    addBST(&i4,c4,&book);
    
    int i5 = 44;
    InOrder(book.entries);
    search(book.entries,&i5,comparekey);
    droptree(book.entries);
    return 1;
}
