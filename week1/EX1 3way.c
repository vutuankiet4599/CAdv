#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void swap(int a[], int i, int j)
{
	int temp;
	temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void qsort3way(int a[], int left, int right)
{
	if(right <= left)return;
	int i = left-1, j = right;
	int m = left-1, n = right;
	while(1)
	{
		while(a[++i]<a[right]);
		while(a[right]<a[--j]) if(j==1)break;
		if (i>=j)break;
		swap(a,i,j);
		if(a[i]==a[right])swap(a,++m,i);
		if(a[j]==a[right])swap(a,--n,j);
	}
	swap(a, i, right);
	j=i-1;
	i=i+1;
	for(int k = left; k<=m; k++)swap(a,k,j--);
	for(int k = right-1; k>=n; k--)swap(a,k,i++);
	qsort3way(a,left,j);
	qsort3way(a,i,right);
}

int main()
{
	int a[100000];
	int i;
	
	srand(time(NULL));
	
	for(i=0; i<100000; i++)
	{
		a[i]=1+rand()%10;
		
	}
	
	struct timeval start, stop;
	double secs = 0;
	gettimeofday(&start, NULL);
	
	qsort3way(a,0,99999);
	
	gettimeofday(&stop, NULL);
	secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
	
    printf("Thoi gian sap xep: %f",secs);
	return 0;
}
