#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INITIAL_SIZE 100
#define INCREMENTAL_SIZE 10

typedef struct {
	void *key;
	void *value;
}Entry;

typedef struct {
	Entry *entries;
	int size, total;
	Entry (*makeNode)(void *, void *);
	int (*compare)(void *, void *);
}SymbolTable;

void* memcpy(void* region1,const void* region2,size_t n)
{
	
    const char* first = (const char*) region2;
    const char* last = ((const char*) region2) + n;
    char* result = (char*) region1;
    while (first != last) *result++ = *first++;
    return result;
}

int comparePhone(void * in1, void* in2) {
	Entry *entry1=(Entry*)in1;
	Entry *entry2=(Entry*)in2;
	int num1 = *( (int*) entry1->key );
	int num2 = *( (int*) entry2->key );

	if (num1==num2) return 0;
	else if (num1 > num2) return 1;
	else return -1;
}

int compare(void *in1, void *in2)
{
	int num1 = *(int*)in1;
	int num2 = *(int*)in2;
	if (num1==num2) return 0;
	else if (num1 > num2) return 1;
	else return -1;
}

Entry makePhoneBook(void *phone, void *name)
{
	Entry res;
	res.key = malloc(sizeof(int));
	memcpy(res.key, phone, sizeof(int));
	res.value = strdup((char*)name);
	return res;
}

SymbolTable createSymbolTable(Entry (*makeNode)(void*, void*),int (*compare)(void*, void*))
{
    SymbolTable s_table;
    s_table.entries = (Entry*)malloc(INITIAL_SIZE*sizeof(Entry));
    if(s_table.entries==NULL) {
        printf("Error!\n");
        exit(1);
    }
    s_table.total = 0;
    s_table.size = INITIAL_SIZE;
    s_table.makeNode = makeNode;
    s_table.compare = compare;
    return s_table;
}

void dropSymbolTable(SymbolTable* tab){
    if(tab!=NULL){
        if(tab->entries!=NULL){
            int i;
            Entry *e=tab->entries;

            for(i=0;i<tab->total;i++)
            {
                if((e+i)->value!=NULL)
                    free((e+i)->value);
                if((e+i)->key !=NULL)
                    free((e+i)->key);
            }

            free(tab->entries);
        }
    }
}

void entrySwap(void *a, void *b, size_t size){
    char *tmp = (char *) malloc(size);

    int k;
    
    for(k=0;k<size;k++){
        *(tmp+k)=*((char*)a+k);
        *((char*)a+k)=*((char*)b+k);
        *((char*)b+k)=*((char*)tmp+k);
    }
    
    free(tmp);
}


int partition_2_way(void *arr,int left , int right, size_t size,int (*compare)(void* ,void*),void (*swap)(void*, void*,size_t)){
    void *pivot = arr+size*left;
    int i = left , j = right + 1;
    while(i<j){
        i = i + 1;
        while((i<=right)  && (compare(pivot, (arr+size*i)) == 1)) i = i + 1;
        j = j - 1;
        while((j >=left)  && (compare(pivot , (arr+size*j)) == -1)) j = j - 1;
        swap((arr+size*i),(arr+size*j),size);
    }
    swap((arr+size*i),(arr+size*j),size);
    swap((arr+size*j),(arr+size*left),size);
    return j;
}

void quick_sort_2_way(void *arr,int left ,int right,size_t size,int (*compare)(void* ,void*),void (*swap)(void*, void*,size_t)){
    if(left<right){
        int pivot_pos = partition_2_way(arr,left,right,size,compare,swap);
        quick_sort_2_way(arr,left,pivot_pos-1,size,compare,swap);
        quick_sort_2_way(arr,pivot_pos +1 , right,size,compare,swap);
    }
}

int addEntry(void* key, void* value, SymbolTable* book){
    if(book->total<book->size){
        Entry e=makePhoneBook(key,value);
        //book->entries[book->total]=e;
        memcpy(book->entries+book->total,&e,sizeof(Entry));
        
        book->total++;
    }
    else{
        book->size+=INCREMENTAL_SIZE;
        book->entries = (Entry*)realloc(book->entries, book->size*sizeof(Entry));
        if(book->entries==NULL){
			printf("error");
			return 0;
		}
		Entry e=makePhoneBook(key,value);
        memcpy(book->entries+book->total,&e,sizeof(Entry));
        book->total++;
    }

    quick_sort_2_way(book->entries,0,book->total-1,sizeof(Entry),comparePhone,entrySwap);
    
    return 1;
}

void *getEntryValue(void* key, const SymbolTable *book,int left, int right)
{
	int i = (left + right)/2;
	if(compare(key,book->entries[i].key)>0)return getEntryValue(key, book, i+1, right);
	if(compare(key,book->entries[i].key)==0)return book->entries[i].value;
	if(compare(key,book->entries[i].key)<0)return getEntryValue(key, book, left, i-1);
}

int main()
{
	SymbolTable  book=createSymbolTable(makePhoneBook,comparePhone);
    
    int i1=12;
    char c1[]="hello1";
    
    addEntry(&i1,c1,&book);
    
    int i2=1;
    char c2[]="hello2";
    addEntry(&i2,c2,&book);

    int i3=7;
    char c3[]="hello3";
    addEntry(&i3,c3,&book);
    
    int i4=6;
    char c4[]="hello4";
    addEntry(&i4,c4,&book);
    
    
    printf("add ok\n");
   
    int i;
    for(i=0;i<4;i++){
		printf("%d\n",*(int*)(book.entries+i)->key);
		printf("%s\n",(char*)(book.entries+i)->value);
	}
	
	char *value1;
	int key1 = 6;
	value1 = (char*)getEntryValue(&key1,&book,0,3);
	printf("value tim duoc: %s",value1);
	
    dropSymbolTable(&book);
    
    return 1;

}
