#include <stdio.h>
#include <stdlib.h>

typedef union {
    int i;
    long l;
    float f;
    double d;
    void *v;
    char *s;
    char c;
} Jval;

Jval new_jval_i(int i){
    Jval a;
    a.i=i;
    return a;    
}

int jval_i(Jval ai){
    return ai.i;
}

int compare_i(Jval *a, Jval *b)
{
	if (jval_i(*a)==jval_i(*b))return 0;
	else if(jval_i(*a)<jval_i(*b))return -1;
	else return 1;
}

Jval* create_array_i(int n)
{
	Jval *array = (Jval*)malloc(sizeof(Jval)*n);
	for(int i=0;i<n;i++)array[i]=new_jval_i(rand());
	return array;
}

void exch(Jval buf[], int i, int j,int size)
{

	int n;
	char *tg;
	tg = (char*)malloc(sizeof(char)*size);
	
	char *pi = (char*)buf;
	pi = pi + (size*i);
	
	char *pj = (char*)buf;
	pj = pj + (size*j);
	
	for(n=0;n<size;n++)
	{
		*(tg+n) = *(pi+n);
		*(pi+n) = *(pj+n);
		*(pj+n) = *(tg+n);
	}
	
	free(tg);
}

void sort_gen(Jval *a, int l, int r,int (*compare)(Jval*, Jval*),int size)
{	
    if (r <= l) return;
    int i = l-1, j = r;
    int p = l-1, q = r;
    
    while(1) 
	{
		
        while (compare(&a[++i] ,&a[r])<0);
        while (compare(&a[r], &a[--j]) < 0 )
        if (j == l) break;
        if (i >= j) break;
        exch(a, i, j,size);
        
        if (compare(&a[i], &a[r])==0)
        exch(a, ++p, i,size);
        if (compare(&a[j], &a[r])==0)
        exch(a, --q, j,size);
    }
exch(a, i, r,size);
j = i - 1;
i = i + 1;
for (int k = l ; k <= p; k++) exch(a, k, j--,size);
for (int k = r-1; k >= q; k--) exch(a, k, i++,size);
sort_gen(a, l, j, compare,size);
sort_gen(a, i, r, compare,size);
}

int search_gen(Jval buf[], int l, int r, Jval *item, int (*compare)(Jval *, Jval *))
{
	if (r<l)return -1;
	int i;
	i=(l+r)/2;
	int res;
	res = compare(item,buf+i) ;
	if(res==0)return i;
	else if(res<0)
	return search_gen(buf,l,i-1,item,compare);
	else return search_gen(buf, i+1, r, item, compare);
}

void sort_i(Jval a[], int l, int r, int size)
{
	return sort_gen(a,l,r,compare_i,size);
}

int search_i(Jval a[],Jval *item, int l, int r)
{
	return search_gen(a,l,r,item,compare_i);
}
int main()
{
    Jval *a = create_array_i(6);
    int i;
    sort_i(a,0,5,sizeof(Jval));
    for (i=0;i<6;i++)printf("%d ",a[i].i);
    printf("\n");
    Jval x;
    x=new_jval_i(18467);
    printf("Phan tu xuat hien o vi tri: %d",search_i(a,&x,0,5));
    
    return 1;
}
