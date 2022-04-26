#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int int_compare(void *x, void *y)
{
	int a = *((int*)x);
	int b = *((int*)y);
	
	if(a==b)return 0;
	else if(a<b)return -1;
	else return 1;
}

void swap(void *buf, int i, int j, int size)
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

int partition(void *a, int l, int r, int size, int (*compare)(void *,void *))
{
	int i=l;
	int j=r+1;
	void *pivot=a+size*l;
	
	while(i<j)
	{
		i=i+1;
		while(compare(&i,&r)!=1 && compare((char*)a+size*i,(char*)pivot)!=1)i=i+1;
		j=j-1;
		while(compare(&j,&l)!=-1 && compare((char*)a+size*j,(char*)pivot)==1)j=j-1;
		swap(a,i,j,size);
	}
	swap(a,i,j,size);
	swap(a,j,l,size);
	return j;
}

void qsort2(void *a, int l, int r, int (*compare)(void *,void *),int size)
{
	int pivot;
	if(l<r)
	{
		pivot = partition(a,l,r,size,compare);
		qsort2(a,l,pivot-1,compare,size);
		qsort2(a,pivot+1,r,compare,size);
	}
}

int search(void *buf, int size, int l, int r, void *item, int (*compare)(void *, void *))
{
	if (r<l)return -1;
	int i;
	i=(l+r)/2;
	int res;
	res = compare(item, (char*)buf + (size*i) );
	if(res==0)return i;
	else if(res<0)
	return search(buf,size,l,i-1,item,compare);
	else return search(buf, size, i+1, r, item, compare);
}

int main()
{
	int a[5]={1,6,3,5,2};
	int item = 3;
	qsort2(a,0,4,int_compare,sizeof(int));
	for(int i=0;i<5;i++)printf("%d ",a[i]);
	printf("\n");
	int res = search(a,sizeof(int),0,4,&item,int_compare);
	printf("Vi tri xuat hien %d\n",res);
    return 1;
}
