#include <stdio.h>
typedef struct person{
	int id;
	int age;
}person;

void exch(person a[],int i,int j)
{
	person temp;
	temp=a[i];
	a[i]=a[j];
	a[j]=temp;
}

int int_compare(person *x, person *y)
{
	int m = x->age;
	int n = y->age;
    if ( m == n ) return 0;
	return m < n ? 1 : -1;
}

void sort(person a[], int l, int r, int (*compare)(person *, person *)) {
	if (r <= l) return;
	int i = l-1, j = r;
	int p = l-1, q = r;
	while(1)    {
		while (compare(&a[r] ,&a[++i] )==1);
		while (compare(&a[--j] , &a[r])==1) if (j == 1) break;
		if (i >= j) break;
		exch(a, i, j);
		if (compare(&a[i],&a[r])==0) exch(a, ++p, i);
		if (compare(&a[j],&a[r])==0) exch(a, --q, j);
	}
	exch(a, i, r);
	j = i - 1;
	i = i + 1;
	for (int k = l ; k <= p; k++) exch(a, k, j--);
	for (int k = r-1; k >= q; k--) exch(a, k, i++);
	sort(a, l, j,compare);
	sort(a, i, r,compare);
}
int main()
{
	person a[8];
	for(int i=0; i<8; i++)
	{
		printf("Id nguoi thu %d: ",i);
		scanf("%d",&a[i].id);
		printf("Tuoi nguoi thu %d: ",i);
		scanf("%d",&a[i].age);
	}
	sort(a,0,7,int_compare);
	printf("Sap xep theo so tuoi giam dan:\n");
	for(int i=0; i<8; i++)
	{
		printf("Tuoi va id : %d %d\n",a[i].age,a[i].id);
    }
	return 0;
}
