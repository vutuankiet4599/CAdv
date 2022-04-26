#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void swap(int a[], int i, int j)
{
	int temp;
	temp = a[i];
	a[i]=a[j];
	a[j]=temp;
}

int partition(int a[], int left, int right)
{
	int i = left;
	int j = right+1;
	int pivot = a[left];
	while(i<j)
	{
		i = i+1;
		while(i<=right && a[i]<=pivot)i++;
		j=j-1;
		while(j>=left && a[j]>pivot)j--;
		swap(a, i, j);
	}
	swap(a, i, j);
	swap(a,j,left);
	return j;
}

int qsort2way(int a[], int left, int right)
{
	int pivot;
	if(left<right)
	{
		pivot = partition(a, left, right);
		qsort2way(a, left, pivot-1);
		qsort2way(a, pivot+1, right);
	}
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
	
	qsort2way(a,0,99999);
	
	gettimeofday(&stop, NULL);
	secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
	
    printf("Thoi gian sap xep: %f",secs);
	return 0;
}
